/*************************************************************************/
/* Copyright (C) 2007-2009 sujith <m.sujith@gmail.com>			 */
/* Copyright (C) 2009-2013 matias <mati86dl@gmail.com>			 */
/* 									 */
/* This program is free software: you can redistribute it and/or modify	 */
/* it under the terms of the GNU General Public License as published by	 */
/* the Free Software Foundation, either version 3 of the License, or	 */
/* (at your option) any later version.					 */
/* 									 */
/* This program is distributed in the hope that it will be useful,	 */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of	 */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	 */
/* GNU General Public License for more details.				 */
/* 									 */
/* You should have received a copy of the GNU General Public License	 */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#ifndef PRAGHA_H
#define PRAGHA_H

#ifndef HAVE_PARANOIA_NEW_INCLUDES
#include "cdda.h" // Should be before config.h, libcdio 0.83 issue
#endif

#if HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_LIBKEYBINDER
#include <keybinder.h>
#endif

#ifdef HAVE_LIBCLASTFM
#include <clastfm.h>
#endif

#ifdef HAVE_LIBGLYR
#include <glyr/glyr.h>
#include <glyr/cache.h>
#endif

#ifdef HAVE_LIBXFCE4UI
#include <libxfce4ui/libxfce4ui.h>
#endif

#ifdef HAVE_PLPARSER
#include <totem-pl-parser.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <gio/gio.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <libnotify/notify.h>
#include <gtk/gtk.h>
#include <sqlite3.h>
#include <gdk/gdkkeysyms.h>
#include <tag_c.h>
#include <taglib_config.h>
#include <cddb/cddb.h>
#include <gst/gst.h>

#if defined(GETTEXT_PACKAGE)
#include <glib/gi18n-lib.h>
#else
#include <glib/gi18n.h>
#endif

/* Some definitions to solve different versions of the libraries. */

#if GLIB_CHECK_VERSION (2, 32, 0)
#define PRAGHA_MUTEX(mtx) GMutex mtx
#define pragha_mutex_free(mtx) g_mutex_clear (&(mtx))
#define pragha_mutex_lock(mtx) g_mutex_lock (&(mtx))
#define pragha_mutex_unlock(mtx) g_mutex_unlock (&(mtx))
#define pragha_mutex_create(mtx) g_mutex_init (&(mtx))
#else
#define PRAGHA_MUTEX(mtx) GMutex *mtx
#define pragha_mutex_free(mtx) g_mutex_free (mtx)
#define pragha_mutex_lock(mtx) g_mutex_lock (mtx)
#define pragha_mutex_unlock(mtx) g_mutex_unlock (mtx)
#define pragha_mutex_create(mtx) (mtx) = g_mutex_new ()
#endif

#ifndef NOTIFY_CHECK_VERSION
#define NOTIFY_CHECK_VERSION(x,y,z) 0
#endif

#include "pragha-album-art.h"
#include "pragha-backend.h"
#include "pragha-database.h"
#include "pragha-musicobject.h"
#include "pragha-preferences.h"
#include "pragha-scanner.h"
#include "pragha-statusbar.h"
#include "gtkcellrendererbubble.h"

#include "xml_helper.h"

/* With libcio 0.83 should be before config.h. libcdio issue */
#ifdef HAVE_PARANOIA_NEW_INCLUDES
#include "cdda.h"
#endif

/* Some default preferences. */

#define MIN_WINDOW_WIDTH           (gdk_screen_width() * 3 / 4)
#define MIN_WINDOW_HEIGHT          (gdk_screen_height() * 3 / 4)
#define DEFAULT_SIDEBAR_SIZE       200
#define ALBUM_ART_SIZE             36
#define PROGRESS_BAR_WIDTH         300
#define COL_WIDTH_THRESH           30
#define DEFAULT_PLAYLIST_COL_WIDTH ((MIN_WINDOW_WIDTH - DEFAULT_SIDEBAR_SIZE) / 4)
#define OSD_TIMEOUT                5000
#define ALBUM_ART_PATTERN_LEN      1024
#define ALBUM_ART_NO_PATTERNS      6
#define LASTFM_UNAME_LEN           256
#define LASTFM_PASS_LEN            512
#define TAG_MAX_LEN                256
#define AUDIO_CD_DEVICE_ENTRY_LEN  32

#define P_TRACK_NO_STR      "#"
#define P_TNO_FULL_STR      N_("Track No")
#define P_TITLE_STR         N_("Title")
#define P_ARTIST_STR        N_("Artist")
#define P_ALBUM_STR         N_("Album")
#define P_GENRE_STR         N_("Genre")
#define P_BITRATE_STR       N_("Bitrate")
#define P_YEAR_STR          N_("Year")
#define P_COMMENT_STR       N_("Comment")
#define P_LENGTH_STR        N_("Length")
#define P_FILENAME_STR      N_("Filename")

/* These are not seen in the playlist columns */
/* Used for library view and preferences */

#define P_FOLDER_STR        "Folder"	/* Containing folder */
#define P_BASENAME_STR      "Basename"	/* Base name of the file */

#define NORMAL_STATE		"normal"
#define FULLSCREEN_STATE	"fullscreen"
#define ICONIFIED_STATE		"iconified"

#define PANE_LIBRARY		"library"
#define PANE_PLAYLISTS		"playlists"
#define PANE_NONE		"none"

#define MIN_DATABASE_VERSION	"0.8.0"

#define DEFAULT_SINK "default"
#define ALSA_SINK    "alsa"
#define OSS4_SINK    "oss4"
#define OSS_SINK     "oss"
#define PULSE_SINK   "pulse"

#define ALSA_DEFAULT_DEVICE "default"
#define OSS_DEFAULT_DEVICE  "/dev/dsp"

#define SAVE_PLAYLIST_STATE         "con_playlist"

#define LASTFM_API_KEY             "ecdc2d21dbfe1139b1f0da35daca9309"
#define LASTFM_SECRET              "f3498ce387f30eeae8ea1b1023afb32b"

#define WAIT_UPDATE 5

#define DBUS_PATH      "/org/pragha/DBus"
#define DBUS_NAME      "org.pragha.DBus"
#define DBUS_INTERFACE "org.pragha.DBus"

#define DBUS_SIG_PLAY     "play"
#define DBUS_SIG_STOP     "stop"
#define DBUS_SIG_PAUSE    "pause"
#define DBUS_SIG_NEXT     "next"
#define DBUS_SIG_PREV     "prev"
#define DBUS_SIG_SHUFFLE  "shuffle"
#define DBUS_SIG_REPEAT   "repeat"
#define DBUS_SIG_INC_VOL  "inc_vol"
#define DBUS_SIG_DEC_VOL  "dec_vol"
#define DBUS_SIG_TOGGLE_VIEW      "toggle_view"
#define DBUS_SIG_SHOW_OSD "show_osd"
#define DBUS_SIG_ADD_FILE "add_files"

#define DBUS_METHOD_CURRENT_STATE "curent_state"
#define DBUS_EVENT_UPDATE_STATE   "update_state"

#define MPRIS_NAME "org.mpris.MediaPlayer2.pragha"
#define MPRIS_PATH "/org/mpris/MediaPlayer2"

#if !GLIB_CHECK_VERSION(2,32,0)
/* Defines to get network manager status. */

#define NM_DBUS_SERVICE		"org.freedesktop.NetworkManager"
#define NM_DBUS_PATH		"/org/freedesktop/NetworkManager"
#define NM_DBUS_INTERFACE	"org.freedesktop.NetworkManager"

typedef enum {
        NM_STATE_UNKNOWN          = 0,
        NM_STATE_ASLEEP           = 10,
        NM_STATE_DISCONNECTED     = 20,
        NM_STATE_DISCONNECTING    = 30,
        NM_STATE_CONNECTING       = 40,
        NM_STATE_CONNECTED_LOCAL  = 50,
        NM_STATE_CONNECTED_SITE   = 60,
        NM_STATE_CONNECTED_GLOBAL = 70
} NMState;
#endif

/* Defines to key preferences. */

#define GROUP_GENERAL  "General"
#define KEY_INSTALLED_VERSION      "installed_version"
#define KEY_LAST_FOLDER            "last_folder"
#define KEY_ADD_RECURSIVELY_FILES  "add_recursively_files"
#define KEY_ALBUM_ART_PATTERN      "album_art_pattern"
#define KEY_TIMER_REMAINING_MODE   "timer_remaining_mode"
#define KEY_SHOW_ICON_TRAY	   "show_icon_tray"
#define KEY_CLOSE_TO_TRAY	   "close_to_tray"
#define KEY_SHOW_OSD               "show_osd"
#define KEY_OSD_IN_TRAY            "osd_in_tray"
#define KEY_SHOW_ALBUM_ART_OSD     "show_albumart_osd"
#define KEY_SHOW_ACTIONS_OSD       "show_action_osd"
#define KEY_INSTANT_SEARCH         "instant_filter"
#define KEY_APPROXIMATE_SEARCH     "aproximate_search"
#define KEY_USE_HINT               "use_hint"

#define GROUP_PLAYLIST "Playlist"
#define KEY_SAVE_PLAYLIST          "save_playlist"
#define KEY_CURRENT_REF		   "current_ref"
#define KEY_SHUFFLE                "shuffle"
#define KEY_REPEAT                 "repeat"
#define KEY_PLAYLIST_COLUMNS       "playlist_columns"
#define KEY_PLAYLIST_COLUMN_WIDTHS "playlist_column_widths"

#define GROUP_LIBRARY  "Library"
#define KEY_LIBRARY_DIR            "library_dir"
#define KEY_LIBRARY_SCANNED        "library_scanned"
#define KEY_LIBRARY_TREE_NODES     "library_tree_nodes"
#define KEY_LIBRARY_VIEW_ORDER     "library_view_order"
#define KEY_LIBRARY_LAST_SCANNED   "library_last_scanned"
#define KEY_FUSE_FOLDERS	   "library_fuse_folders"
#define KEY_SORT_BY_YEAR	   "library_sort_by_year"

#define GROUP_AUDIO    "Audio"
#define KEY_AUDIO_SINK             "audio_sink"
#define KEY_AUDIO_DEVICE           "audio_device"
#define KEY_SOFTWARE_MIXER         "software_mixer"
#define KEY_SOFTWARE_VOLUME	   "software_volume"
#define KEY_AUDIO_CD_DEVICE        "audio_cd_device"
#define KEY_EQ_10_BANDS            "equealizer_10_bands"
#define KEY_EQ_PRESET              "equalizer_preset"

#define GROUP_WINDOW   "Window"
#define KEY_REMEMBER_STATE	   "remember_window_state"
#define KEY_START_MODE		   "start_mode"
#define KEY_WINDOW_SIZE            "window_size"
#define KEY_WINDOW_POSITION        "window_position"
#define KEY_SIDEBAR_SIZE           "sidebar_size"
#define KEY_SIDEBAR                "sidebar"
#define KEY_SHOW_ALBUM_ART         "show_album_art"
#define KEY_ALBUM_ART_SIZE         "album_art_size"
#define KEY_STATUS_BAR             "status_bar"
#define KEY_CONTROLS_BELOW         "controls_below"

#define GROUP_SERVICES   "services"
#define KEY_LASTFM                 "lastfm"
#define KEY_LASTFM_USER            "lastfm_user"
#define KEY_LASTFM_PASS            "lastfm_pass"
#define KEY_GET_ALBUM_ART          "get_album_art"
#define KEY_USE_CDDB               "use_cddb"
#define KEY_ALLOW_MPRIS2           "allow_mpris2"

#define TAG_TNO_CHANGED		1<<0
#define TAG_TITLE_CHANGED	1<<1
#define TAG_ARTIST_CHANGED	1<<2
#define TAG_ALBUM_CHANGED	1<<3
#define TAG_GENRE_CHANGED	1<<4
#define TAG_YEAR_CHANGED	1<<5
#define TAG_COMMENT_CHANGED	1<<6

#define PRAGHA_BUTTON_SKIP       _("_Skip")
#define PRAGHA_BUTTON_SKIP_ALL   _("S_kip All")
#define PRAGHA_BUTTON_DELETE_ALL _("Delete _All")

typedef enum {
	PRAGHA_RESPONSE_SKIP,
	PRAGHA_RESPONSE_SKIP_ALL,
	PRAGHA_RESPONSE_DELETE_ALL
} PraghaDeleteResponseType;

enum debug_level {
	DBG_BACKEND = 1,
	DBG_INFO,
	DBG_LASTFM,
	DBG_MPRIS,
	DBG_MOBJ,
	DBG_DB,
	DBG_VERBOSE,
};

/* Current playlist movement */

enum playlist_action {
	PLAYLIST_NONE,
	PLAYLIST_CURR,
	PLAYLIST_NEXT,
	PLAYLIST_PREV
};

/* Node types in library view */

enum node_type {
	NODE_CATEGORY,
	NODE_FOLDER,
	NODE_GENRE,
	NODE_ARTIST,
	NODE_ALBUM,
	NODE_TRACK,
	NODE_BASENAME,
	NODE_PLAYLIST,
	NODE_RADIO
};

/* Columns in Library view */

enum library_columns {
	L_PIXBUF,
	L_NODE_DATA,
	L_NODE_TYPE,
	L_LOCATION_ID,
	L_MACH,
	L_VISIBILE,
	N_L_COLUMNS
};

/* Columns in current playlist view */

enum curplaylist_columns {
	P_MOBJ_PTR,
	P_QUEUE,
	P_BUBBLE,
	P_STATUS_PIXBUF,
	P_TRACK_NO,
	P_TITLE,
	P_ARTIST,
	P_ALBUM,
	P_GENRE,
	P_BITRATE,
	P_YEAR,
	P_COMMENT,
	P_LENGTH,
	P_FILENAME,
	P_PLAYED,
	N_P_COLUMNS
};

/* DnD */

gboolean tree_selection_func_true(GtkTreeSelection *selection,
					       GtkTreeModel *model,
					       GtkTreePath *path,
					       gboolean path_currently_selected,
					       gpointer data);

gboolean tree_selection_func_false(GtkTreeSelection *selection,
					       GtkTreeModel *model,
					       GtkTreePath *path,
					       gboolean path_currently_selected,
					       gpointer data);

enum dnd_target {
	TARGET_REF_LIBRARY,
	TARGET_URI_LIST,
	TARGET_PLAIN_TEXT
};

/* Library Views */

enum library_view {
	FOLDERS,
	ARTIST,
	ALBUM,
	GENRE,
	ARTIST_ALBUM,
	GENRE_ARTIST,
	GENRE_ALBUM,
	GENRE_ARTIST_ALBUM
};

/* Playlist management */

enum playlist_mgmt {
	NEW_PLAYLIST,
	APPEND_PLAYLIST,
	EXPORT_PLAYLIST,
	SAVE_COMPLETE,
	SAVE_SELECTED
};

/* File Type */

enum file_type {
	FILE_WAV,
	FILE_MP3,
	FILE_FLAC,
	FILE_OGGVORBIS,
#if defined(TAGLIB_WITH_ASF) && (TAGLIB_WITH_ASF==1)
	FILE_ASF,
#endif
#if defined(TAGLIB_WITH_MP4) && (TAGLIB_WITH_MP4==1)
	FILE_MP4,
#endif
#ifdef HAVE_TAGLIB_1_7
	FILE_APE,
#endif
	FILE_CDDA,
	FILE_HTTP,
	LAST_FILE_TYPE
};

/* Playlist type formats */

enum playlist_type {
	PL_FORMAT_UNKNOWN,
	PL_FORMAT_M3U,
	PL_FORMAT_PLS,
	PL_FORMAT_ASX,
	PL_FORMAT_XSPF
};

/* Track sources for last.fm submission */

enum track_source {
	USER_SOURCE,
	BROADCAST_SOURCE,
	RECO_SOURCE,
	LASTFM_SOURCE,
	UNKNOWN_SOURCE
};

struct pixbuf {
	GdkPixbuf *pixbuf_app;
	GdkPixbuf *pixbuf_artist;
	GdkPixbuf *pixbuf_album;
	GdkPixbuf *pixbuf_track;
	GdkPixbuf *pixbuf_genre;
	GdkPixbuf *pixbuf_dir;
};

typedef struct {
	GtkWidget *audio_device_w;
	GtkWidget *audio_cd_device_w;
	GtkWidget *audio_sink_combo_w;
	GtkWidget *soft_mixer_w;

	GtkWidget *use_hint_w;
	GtkWidget *album_art_w;
	GtkWidget *album_art_size_w;
	GtkWidget *album_art_pattern_w;

	GtkWidget *library_view_w;
	GtkWidget *fuse_folders_w;
	GtkWidget *sort_by_year_w;

	GtkWidget *instant_filter_w;
	GtkWidget *aproximate_search_w;
	GtkWidget *window_state_combo_w;
	GtkWidget *restore_playlist_w;
	GtkWidget *show_icon_tray_w;
	GtkWidget *close_to_tray_w;
	GtkWidget *add_recursively_w;

	GtkWidget *show_osd_w;
#if !NOTIFY_CHECK_VERSION (0, 7, 0)
	GtkWidget *osd_in_systray_w;
#endif
	GtkWidget *albumart_in_osd_w;
	GtkWidget *actions_in_osd_w;

#ifdef HAVE_LIBCLASTFM
	GtkWidget *lastfm_w;
	GtkWidget *lastfm_uname_w;
	GtkWidget *lastfm_pass_w;
#endif
#ifdef HAVE_LIBGLYR
	GtkWidget *get_album_art_w;
#endif
	GtkWidget *use_cddb_w;
	GtkWidget *use_mpris2_w;
}PreferencesWidgets;

struct con_pref {
	enum library_view cur_library_view;
	gchar *installed_version;
	gchar *album_art_pattern;
	gchar *start_mode;
	gint window_width;
	gint window_height;
	gint window_x;
	gint window_y;
	gint sidebar_size;
	GKeyFile *configrc_keyfile;
#ifdef HAVE_LIBGLYR
	gchar *cache_folder;
#endif
	gboolean show_osd;
	gboolean osd_in_systray;
	gboolean albumart_in_osd;
	gboolean actions_in_osd;
#ifdef HAVE_LIBGLYR
	gboolean get_album_art;
#endif
	gboolean use_cddb;
	gboolean use_mpris2;
	gboolean show_icon_tray;
	gboolean close_to_tray;
	gboolean remember_window_state;
	gboolean status_bar;
	gboolean controls_below;
	gboolean fuse_folders;
	gboolean sort_by_year;
	GSList *library_tree_nodes;
#ifdef HAVE_LIBCLASTFM
	gboolean lastfm_support;
	gchar *lastfm_user;
	gchar *lastfm_pass;
#endif
};


/**
 * struct con_state - Pertains to the current state of the player
 *
 * @unique_instance: If current invocation of app is unique
 * @view_change: If library view change is in progress
 * @last_folder: Last polder used in file chooser
 * @filter_entry: Search entry for filtering library
 * @cdda_drive: Global handle for the audio cd
 * @cddb_conn: libcddb connection
 * @curr_mobj: musicobject of currently playing track
 */

struct con_state {
	gboolean dragging;
	gboolean unique_instance;
	gboolean view_change;
	gboolean first_run;
	guint timeout_id;
	gchar *last_folder;
	gchar *filter_entry;
	cdrom_drive_t *cdda_drive;
	cddb_conn_t *cddb_conn;
	cddb_disc_t *cddb_disc;
	PraghaMusicobject *curr_mobj;
	PRAGHA_MUTEX (curr_mobj_mutex);
};

#ifdef HAVE_LIBCLASTFM
struct con_lastfm {
	LASTFM_SESSION *session_id;
	enum LASTFM_STATUS_CODES status;
	time_t playback_started;
	PraghaMusicobject *nmobj;
	PRAGHA_MUTEX (nmobj_mutex);
};
#endif

struct con_mpris2 {
	struct con_win *cwin;
	guint owner_id;
	GDBusNodeInfo *introspection_data;
	GDBusConnection *dbus_connection;
	GQuark interface_quarks[4];
	gboolean saved_playbackstatus;
	gboolean saved_shuffle;
	gchar *saved_title;
	gdouble volume;
	enum player_state state;
};

struct con_gnome_media_keys;

/**
 * PraghaPlaylist - Pertains to the current state of the playlist
 * @view - The playlist tree view widget
 * @widget - The parent widget containing the view
 * @changing: If current platlist change is in progress
 * @no_tracks: Total no. of tracks in the current playlist
 * @unplayed_tracks: Total no. of tracks that haven't been played
 * @rand: To generate random numbers
 * @rand_track_refs: List of references maintained in Shuffle mode
 * @queue_track_refs: List of references of queued songs
 * @curr_rand_ref: Currently playing track in Shuffle mode
 * @curr_seq_ref: Currently playing track in non-Shuffle mode
 */

typedef struct {
	GtkWidget *view;
	GtkTreeModel *model;
	GtkWidget *widget;
	GtkWidget *header_context_menu;
	GtkUIManager *cp_context_menu;
	GtkUIManager *cp_null_context_menu;
	GSList *columns;
	GSList *column_widths;
	gboolean changing;
	gboolean dragging;
	gint no_tracks;
	gint unplayed_tracks;
	GRand *rand;
	enum playlist_action current_update_action;
	GList *rand_track_refs;
	GSList *queue_track_refs;
	GtkTreeRowReference *curr_rand_ref;
	GtkTreeRowReference *curr_seq_ref;
	GdkPixbuf *paused_pixbuf;
	GdkPixbuf *playing_pixbuf;
	PraghaPreferences *preferences;
	PraghaDatabase *cdbase;
} PraghaPlaylist;

struct con_win {
	struct pixbuf *pixbuf;
	struct con_pref *cpref;
	struct con_state *cstate;
	PraghaPlaylist *cplaylist;
	PraghaBackend *backend;
	PraghaDatabase *cdbase;
	PraghaScanner  *scanner;
	PraghaPreferences *preferences;
	PreferencesWidgets *preferences_w;
	#ifdef HAVE_LIBCLASTFM
	struct con_lastfm *clastfm;
	#endif
	struct con_mpris2 *cmpris2;
	struct con_gnome_media_keys *cgnome_media_keys;
	GtkWidget *mainwindow;
	GtkWidget *toolbar;
	GtkWidget *info_box;
	PraghaAlbumArt *albumart;
	GtkWidget *track_progress_bar;
	GtkToolItem *prev_button;
	GtkToolItem *play_button;
	GtkToolItem *stop_button;
	GtkToolItem *next_button;
	GtkToolItem *unfull_button;
	GtkWidget *vol_button;
	PraghaStatusbar *statusbar;
	GtkWidget *search_entry;
	GtkWidget *browse_mode;
	GtkWidget *paned;
	GtkWidget *toggle_lib;
	GtkWidget *combo_order;
	GtkWidget *combo_order_label;
	GtkWidget *track_length_label;
	GtkWidget *track_time_label;
	GtkWidget *now_playing_label;
	#ifdef HAVE_LIBCLASTFM
	GtkWidget *ntag_lastfm_button;
	#endif
	GtkWidget *library_tree;
	GtkTreeStore *library_store;
	GtkStatusIcon *status_icon;
	NotifyNotification *osd_notify;
	GtkEntryCompletion *completion[3];
	GtkUIManager *bar_context_menu;
	GtkUIManager *playlist_tree_context_menu;
	GtkUIManager *library_tree_context_menu;
	GtkUIManager *header_library_tree_context_menu;
	GtkUIManager *library_page_context_menu;
	GtkUIManager *systray_menu;
#ifdef HAVE_LIBGLYR
	GlyrDatabase *cache_db;
#endif
	guint related_timeout_id;
	DBusConnection *con_dbus;
};

extern gint debug_level;
extern const gchar *mime_mpeg[];
extern const gchar *mime_wav[];
extern const gchar *mime_flac[];
extern const gchar *mime_ogg[];
#if defined(TAGLIB_WITH_ASF) && (TAGLIB_WITH_ASF==1)
extern const gchar *mime_asf[];
#endif
#if defined(TAGLIB_WITH_MP4) && (TAGLIB_WITH_MP4==1)
extern const gchar *mime_mp4[];
#endif
#ifdef HAVE_TAGLIB_1_7
extern const gchar *mime_ape[];
#endif


extern const gchar *mime_image[];

#ifdef HAVE_PLPARSER
extern const gchar *mime_playlist[];
extern const gchar *mime_dual[];
#endif

/* Convenience macros */

#define for_each_result_row(result, i)					\
	for (i=result.no_columns; i<((result.no_rows+1)*(result.no_columns)); \
	     i+=result.no_columns)

#define string_is_empty(s) (!(s) || !(s)[0])
#define string_is_not_empty(s) (s && (s)[0])

/* Debugging */

#define CDEBUG(_lvl, _fmt, ...)			\
	if (G_UNLIKELY(_lvl <= debug_level))	\
		g_debug(_fmt, ##__VA_ARGS__);

/* Menu */

void open_file_action(GtkAction *action, struct con_win *cwin);
void add_audio_cd_action(GtkAction *action, struct con_win *cwin);
void add_location_action(GtkAction *action, struct con_win *cwin);
void prev_action(GtkAction *action, struct con_win *cwin);
void play_pause_action(GtkAction *action, struct con_win *cwin);
void stop_action(GtkAction *action, struct con_win *cwin);
void next_action (GtkAction *action, struct con_win *cwin);
void add_audio_cd(struct con_win *cwin);
void quit_action(GtkAction *action, struct con_win *cwin);
void expand_all_action(GtkAction *action, struct con_win *cwin);
void collapse_all_action(GtkAction *action, struct con_win *cwin);
void search_library_action(GtkAction *action, struct con_win *cwin);
void search_playlist_action(GtkAction *action, struct con_win *cwin);
void pref_action(GtkAction *action, struct con_win *cwin);
void fullscreen_action (GtkAction *action, struct con_win *cwin);
void playlists_pane_action (GtkAction *action, struct con_win *cwin);
void status_bar_action (GtkAction *action, struct con_win *cwin);
void show_controls_below_action (GtkAction *action, struct con_win *cwin);
void jump_to_playing_song_action (GtkAction *action, struct con_win *cwin);
void show_equalizer_action(GtkAction *action, struct con_win *cwin);
void rescan_library_action(GtkAction *action, struct con_win *cwin);
void update_library_action(GtkAction *action, struct con_win *cwin);
void add_libary_action(GtkAction *action, struct con_win *cwin);
void statistics_action(GtkAction *action, struct con_win *cwin);
void home_action(GtkAction *action, struct con_win *cwin);
void community_action(GtkAction *action, struct con_win *cwin);
void wiki_action(GtkAction *action, struct con_win *cwin);
void translate_action(GtkAction *action, struct con_win *cwin);
void about_action(GtkAction *action, struct con_win *cwin);
GtkUIManager* create_menu(struct con_win *cwin);

/* Panel */

void update_current_song_info(struct con_win *cwin);
void __update_progress_song_info(struct con_win *cwin, gint length);
void __update_current_song_info(struct con_win *cwin);
void unset_current_song_info(struct con_win *cwin);
void unset_track_progress_bar(struct con_win *cwin);
void timer_remaining_mode_change(GtkWidget *w, GdkEventButton* event, struct con_win *cwin);
void edit_tags_playing_event(GtkWidget *w, GdkEventButton* event, struct con_win *cwin);
void track_progress_change_cb(GtkWidget *widget, GdkEventButton *event,struct con_win *cwin);
gboolean album_art_frame_press_callback (GtkWidget *event_box, GdkEventButton *event, struct con_win *cwin);
void update_album_art(PraghaMusicobject *mobj, struct con_win *cwin);
gboolean panel_button_key_press (GtkWidget *win, GdkEventKey *event, struct con_win *cwin);
void unfull_button_handler(GtkToggleToolButton *button, struct con_win *cwin);
void play_button_handler(GtkButton *button, struct con_win *cwin);
void stop_button_handler(GtkButton *button, struct con_win *cwin);
void prev_button_handler(GtkButton *button, struct con_win *cwin);
void next_button_handler(GtkButton *button, struct con_win *cwin);
void album_art_toggle_state(struct con_win *cwin);
void toggled_cb(GtkToggleButton *toggle, struct con_win *cwin);
GtkWidget* create_toolbar(struct con_win *cwin);

/* File utils functions */

gboolean is_playable_file(const gchar *file);
gboolean is_dir_and_accessible(const gchar *dir);
gint pragha_get_dir_count(const gchar *dir_name, GCancellable *cancellable);
gint dir_file_count(const gchar *dir_name, gint call_recur);
GList *append_mobj_list_from_folder(GList *list, gchar *dir_name);
GList *append_mobj_list_from_unknown_filename(GList *list, gchar *filename);

/* Musicobject functions */

PraghaMusicobject* new_musicobject_from_file(const gchar *file);
PraghaMusicobject* new_musicobject_from_db(PraghaDatabase *cdbase, gint location_id);
PraghaMusicobject* new_musicobject_from_cdda(struct con_win *cwin, gint track_no);
PraghaMusicobject* new_musicobject_from_location(const gchar *uri, const gchar *name);
void pragha_update_musicobject_change_tag(PraghaMusicobject *mobj, gint changed, PraghaMusicobject *nmobj);

/* Tag functions */
gboolean pragha_musicobject_set_tags_from_file(PraghaMusicobject *mobj, const gchar *file);
gboolean pragha_musicobject_save_tags_to_file(gchar *file, PraghaMusicobject *mobj, int changed);
gboolean confirm_tno_multiple_tracks(gint tno, GtkWidget *parent);
gboolean confirm_title_multiple_tracks(const gchar *title, GtkWidget *parent);
void pragha_update_local_files_change_tag(GPtrArray *file_arr, gint changed, PraghaMusicobject *mobj);
gint tag_edit_dialog(PraghaMusicobject *omobj, gint prechanged, PraghaMusicobject *nmobj, struct con_win *cwin);
void refresh_tag_completion_entries(struct con_win *cwin);
void copy_tags_selection_current_playlist(PraghaMusicobject *omobj, gint changes, struct con_win *cwin);
void edit_tags_current_playlist(GtkAction *action, struct con_win *cwin);


/* Library manipulation functions */

void library_tree_row_activated_cb(GtkTreeView *library_tree,
				   GtkTreePath *path,
				   GtkTreeViewColumn *column,
				   struct con_win *cwin);
gboolean library_tree_button_press_cb(GtkWidget *widget,
				     GdkEventButton *event,
				     struct con_win *cwin);
gboolean library_tree_button_release_cb(GtkWidget *widget,
				     GdkEventButton *event,
				     struct con_win *cwin);
gboolean library_page_right_click_cb(GtkWidget *widget,
				     GdkEventButton *event,
				     struct con_win *cwin);
gboolean dnd_library_tree_begin(GtkWidget *widget,
				    GdkDragContext *context,
				    struct con_win *cwin);
gboolean dnd_library_tree_begin(GtkWidget *widget,
				    GdkDragContext *context,
				    struct con_win *cwin);
void dnd_library_tree_get(GtkWidget *widget,
			  GdkDragContext *context,
			  GtkSelectionData *data,
			  enum dnd_target info,
			  guint time,
			  struct con_win *cwin);
void simple_library_search_keyrelease(struct con_win *cwin);
gboolean simple_library_search_keyrelease_handler(GtkEntry *entry, struct con_win *cwin);
gboolean simple_library_search_activate_handler(GtkEntry *entry, struct con_win *cwin);
void clear_library_search(struct con_win *cwin);
void folders_library_tree(GtkAction *action, struct con_win *cwin);
void artist_library_tree(GtkAction *action, struct con_win *cwin);
void album_library_tree(GtkAction *action, struct con_win *cwin);
void genre_library_tree(GtkAction *action, struct con_win *cwin);
void artist_album_library_tree(GtkAction *action, struct con_win *cwin);
void genre_album_library_tree(GtkAction *action, struct con_win *cwin);
void genre_artist_library_tree(GtkAction *action, struct con_win *cwin);
void genre_artist_album_library_tree(GtkAction *action, struct con_win *cwin);
void library_tree_replace_playlist_action(GtkAction *action, struct con_win *cwin);
void library_tree_replace_and_play(GtkAction *action, struct con_win *cwin);
void library_tree_add_to_playlist_action(GtkAction *action, struct con_win *cwin);
void library_tree_edit_tags(GtkAction *action, struct con_win *cwin);
void library_tree_delete_db(GtkAction *action, struct con_win *cwin);
void library_tree_delete_hdd(GtkAction *action, struct con_win *cwin);
void init_library_view(struct con_win *cwin);

/* DB (Sqlite) Functions */

void add_new_musicobject_db(PraghaDatabase *cdbase, PraghaMusicobject *mobj);
void add_track_playlist_db(const gchar *file, gint playlist_id, PraghaDatabase *cdbase);
void add_track_radio_db(const gchar *uri, gint radio_id, PraghaDatabase *cdbase);
gint find_playlist_db(const gchar *playlist, PraghaDatabase *cdbase);
gint find_radio_db(const gchar *radio, PraghaDatabase *cdbase);
void delete_location_db(gint location_id, PraghaDatabase *cdbase);
gchar *pragha_database_get_filename_from_location_id(PraghaDatabase *cdbase, gint location_id);
gint delete_location_hdd(gint location_id, PraghaDatabase *cdbase);
void db_update_track(PraghaDatabase *database,
		     gint location_id, gint changed,
		     gint track_no, const gchar *title,
		     gint artist_id, gint album_id, gint genre_id, gint year_id, gint comment_id);
void
pragha_db_update_local_files_change_tag(PraghaDatabase *cdbase, GArray *loc_arr, gint changed, PraghaMusicobject *mobj);
void update_playlist_name_db(const gchar *oplaylist, gchar *nplaylist, PraghaDatabase *cdbase);
gint add_new_playlist_db(const gchar *playlist, PraghaDatabase *cdbase);
gchar** get_playlist_names_db(PraghaDatabase *cdbase);
gint get_playlist_count_db(PraghaDatabase *cdbase);
void update_radio_name_db(const gchar *oradio, gchar *nradio, PraghaDatabase *cdbase);
gint add_new_radio_db(const gchar *radio, PraghaDatabase *cdbase);
gint get_radio_count_db(struct con_win *cwin);
gint get_tracklist_count_db(PraghaDatabase *cdbase);
void delete_playlist_db(const gchar *playlist, PraghaDatabase *cdbase);
void flush_playlist_db(gint playlist_id, PraghaDatabase *cdbase);
void delete_radio_db(const gchar *radio, PraghaDatabase *cdbase);
void flush_radio_db(gint radio_id, PraghaDatabase *cdbase);
void flush_stale_entries_db(PraghaDatabase *cdbase);
void flush_db(PraghaDatabase *cdbase);
void pragha_database_add_new_file(PraghaDatabase *cdbase, const gchar *file);
void
pragha_database_delete_folder(PraghaDatabase *cdbase, const gchar *dir_name);
gboolean pragha_database_init_schema (PraghaDatabase *database);
gint drop_dbase_schema(PraghaDatabase *cdbase);
gint db_get_artist_count(PraghaDatabase *cdbase);
gint db_get_album_count(PraghaDatabase *cdbase);
gint db_get_track_count(PraghaDatabase *cdbase);
void db_begin_transaction(PraghaDatabase *cdbase);
void db_commit_transaction(PraghaDatabase *cdbase);

/* Playlist mgmt functions */

gchar* get_playlist_name(PraghaPlaylist* cplaylist, enum playlist_mgmt type, enum playlist_mgmt *choice);
void add_playlist_current_playlist(gchar *playlist, struct con_win *cwin);
GList *add_playlist_to_mobj_list(PraghaDatabase *cdbase, gchar *playlist, GList *list);
GList *add_radio_to_mobj_list(PraghaDatabase *cdbase, gchar *playlist, GList *list);
void playlist_tree_rename(GtkAction *action, struct con_win *cwin);
void playlist_tree_delete(GtkAction *action, struct con_win *cwin);
void export_playlist (PraghaPlaylist* cplaylist, gint choice);
void playlist_tree_export(GtkAction *action, struct con_win *cwin);
GList *
pragha_pl_parser_append_mobj_list_by_extension (GList *mlist, const gchar *file);
GSList *pragha_pl_parser_parse_from_file_by_extension (const gchar *filename);
GSList *pragha_totem_pl_parser_parse_from_uri(const gchar *uri);
void pragha_pl_parser_open_from_file_by_extension(const gchar *file, struct con_win *cwin);
void
save_playlist(PraghaPlaylist* cplaylist,
              gint playlist_id,
              enum playlist_mgmt type);
void
new_playlist(PraghaPlaylist* cplaylist,
             const gchar *playlist,
             enum playlist_mgmt type);
void append_playlist(PraghaPlaylist* cplaylist, const gchar *playlist, gint type);
void new_radio (PraghaPlaylist* cplaylist, const gchar *uri, const gchar *name);
void update_menu_playlist_changes(struct con_win *cwin);

/* Current playlist */

void jump_to_path_on_current_playlist(PraghaPlaylist *cplaylist, GtkTreePath *path, gboolean center);
void select_numered_path_of_current_playlist(PraghaPlaylist *cplaylist, gint path_number, gboolean center);
void pragha_playlist_update_statusbar_playtime(PraghaPlaylist *cplaylist);
enum playlist_action pragha_playlist_get_current_update_action(PraghaPlaylist* cplaylist);
void pragha_playlist_report_finished_action(PraghaPlaylist* cplaylist);
void pragha_playlist_set_current_update_action(PraghaPlaylist* cplaylist, enum playlist_action action);
void pragha_playlist_update_current_playlist_state(PraghaPlaylist* cplaylist, GtkTreePath *path);
void update_current_playlist_view_new_track(PraghaPlaylist *cplaylist, PraghaBackend *backend);
void update_current_playlist_view_track(PraghaPlaylist *cplaylist, PraghaBackend *backend);
PraghaMusicobject * current_playlist_mobj_at_path(GtkTreePath *path,
						  PraghaPlaylist *cplaylist);
GtkTreePath* current_playlist_path_at_mobj(PraghaMusicobject *mobj,
					   PraghaPlaylist *cplaylist);
void
pragha_playlist_set_first_rand_ref(PraghaPlaylist *cplaylist, GtkTreePath *path);
GtkTreePath* current_playlist_get_selection(PraghaPlaylist *cplaylist);
GtkTreePath* current_playlist_get_next(PraghaPlaylist *cplaylist);
GtkTreePath* current_playlist_get_prev(PraghaPlaylist *cplaylist);
GtkTreePath* current_playlist_get_actual(PraghaPlaylist *cplaylist);
GtkTreePath* get_first_random_track(PraghaPlaylist *cplaylist);
GtkTreePath* current_playlist_nth_track(gint n, PraghaPlaylist *cplaylist);
GtkTreePath* get_next_queue_track(PraghaPlaylist *cplaylist);
gchar* get_ref_current_track(struct con_win *cwin);
void dequeue_current_playlist(GtkAction *action, struct con_win *cwin);
void queue_current_playlist(GtkAction *action, struct con_win *cwin);
void toggle_queue_selected_current_playlist (PraghaPlaylist *cplaylist);
void remove_from_playlist(GtkAction *action, struct con_win *cwin);
void crop_current_playlist(GtkAction *action, struct con_win *cwin);
void edit_tags_playing_action(GtkAction *action, struct con_win *cwin);
void pragha_playlist_remove_all (PraghaPlaylist *cplaylist);
void current_playlist_clear_action(GtkAction *action, struct con_win *cwin);
void pragha_playlist_update_change_tag(PraghaPlaylist *cplaylist, GtkTreeIter *iter, gint changed);
void pragha_playlist_update_ref_list_change_tag(PraghaPlaylist *cplaylist, GList *list, gint changed);
void pragha_playlist_update_current_track(PraghaPlaylist *cplaylist, gint changed);
void append_current_playlist(PraghaPlaylist *cplaylist, PraghaMusicobject *mobj);
void
pragha_playlist_append_single_song(PraghaPlaylist *cplaylist, PraghaMusicobject *mobj);
void
pragha_playlist_append_mobj_and_play(PraghaPlaylist *cplaylist, PraghaMusicobject *mobj);
void
pragha_playlist_append_mobj_list(PraghaPlaylist *cplaylist, GList *list);
gboolean
pragha_mobj_list_already_has_title_of_artist(GList *list,
					     const gchar *title,
					     const gchar *artist);
gboolean
pragha_playlist_already_has_title_of_artist(PraghaPlaylist *cplaylist,
					    const gchar *title,
					    const gchar *artist);
void clear_sort_current_playlist(GtkAction *action, PraghaPlaylist *cplaylist);
void save_selected_playlist(GtkAction *action, PraghaPlaylist *cplaylist);
void save_current_playlist(GtkAction *action, PraghaPlaylist *cplaylist);
void jump_to_playing_song(struct con_win *cwin);
void copy_tags_to_selection_action(GtkAction *action, struct con_win *cwin);
GList *pragha_playlist_get_mobj_list(PraghaPlaylist* cplaylist);
GList *pragha_playlist_get_selection_mobj_list(PraghaPlaylist* cplaylist);
GList *pragha_playlist_get_selection_ref_list(PraghaPlaylist *cplaylist);
PraghaMusicobject *pragha_playlist_get_selected_musicobject(PraghaPlaylist* cplaylist);
void save_current_playlist_state(PraghaPlaylist *cplaylist);
void init_current_playlist_view(PraghaPlaylist *cplaylist);
void playlist_track_column_change_cb(GtkCheckMenuItem *item,
				     PraghaPlaylist* cplaylist);
void playlist_title_column_change_cb(GtkCheckMenuItem *item,
				     PraghaPlaylist* cplaylist);
void playlist_artist_column_change_cb(GtkCheckMenuItem *item,
				      PraghaPlaylist* cplaylist);
void playlist_album_column_change_cb(GtkCheckMenuItem *item,
				     PraghaPlaylist* cplaylist);
void playlist_genre_column_change_cb(GtkCheckMenuItem *item,
				     PraghaPlaylist* cplaylist);
void playlist_bitrate_column_change_cb(GtkCheckMenuItem *item,
				       PraghaPlaylist* cplaylist);
void playlist_year_column_change_cb(GtkCheckMenuItem *item,
				    PraghaPlaylist* cplaylist);
void playlist_length_column_change_cb(GtkCheckMenuItem *item,
				      PraghaPlaylist* cplaylist);
void playlist_comment_column_change_cb(GtkCheckMenuItem *item,
				     PraghaPlaylist* cplaylist);
void playlist_filename_column_change_cb(GtkCheckMenuItem *item,
					PraghaPlaylist* cplaylist);
void clear_sort_current_playlist_cb(GtkMenuItem *item,
				    PraghaPlaylist *cplaylist);
gint compare_track_no(GtkTreeModel *model, GtkTreeIter *a,
		      GtkTreeIter *b, gpointer data);
gint compare_bitrate(GtkTreeModel *model, GtkTreeIter *a,
		     GtkTreeIter *b, gpointer data);
gint compare_year(GtkTreeModel *model, GtkTreeIter *a,
		  GtkTreeIter *b, gpointer data);
gint compare_length(GtkTreeModel *model, GtkTreeIter *a,
		    GtkTreeIter *b, gpointer data);
gboolean
pragha_playlist_propagate_event(PraghaPlaylist* cplaylist, GdkEventKey *event);
void
pragha_playlist_activate_path(PraghaPlaylist* cplaylist, GtkTreePath *path);
void
pragha_playlist_activate_unique_mobj(PraghaPlaylist* cplaylist, PraghaMusicobject *mobj);
void
pragha_playlist_set_rules_hint(PraghaPlaylist* cplaylist, gboolean use_hint);
gint
pragha_playlist_get_no_tracks(PraghaPlaylist* cplaylist);
gboolean
pragha_playlist_has_queue(PraghaPlaylist* cplaylist);
gboolean
pragha_playlist_is_changing(PraghaPlaylist* cplaylist);
void
pragha_playlist_set_changing(PraghaPlaylist* cplaylist, gboolean changing);
GtkWidget *
pragha_playlist_get_view(PraghaPlaylist* cplaylist);
GtkTreeModel *
pragha_playlist_get_model(PraghaPlaylist* cplaylist);
GtkWidget *
pragha_playlist_get_widget(PraghaPlaylist* cplaylist);
void
current_playlist_save_preferences(PraghaPlaylist* cplaylist);
void cplaylist_free(PraghaPlaylist *cplaylist);
PraghaPlaylist *cplaylist_new(struct con_win *cwin);

/* Preferences */

void save_preferences(struct con_win *cwin);
void preferences_dialog(struct con_win *cwin);
void preferences_free(struct con_pref *cpref);

/* Systray functions */

void create_status_icon (struct con_win *cwin);
void systray_display_popup_menu (struct con_win *cwin);

void about_widget(struct con_win *cwin);

/* Command line functions */

gboolean cmd_version(const gchar *opt_name, const gchar *val,
		     struct con_win *cwin, GError **error);
gboolean cmd_play(const gchar *opt_name, const gchar *val,
		  struct con_win *cwin, GError **error);
gboolean cmd_stop(const gchar *opt_name, const gchar *val,
		  struct con_win *cwin, GError **error);
gboolean cmd_pause(const gchar *opt_name, const gchar *val,
		   struct con_win *cwin, GError **error);
gboolean cmd_prev(const gchar *opt_name, const gchar *val,
		  struct con_win *cwin, GError **error);
gboolean cmd_next(const gchar *opt_name, const gchar *val,
		  struct con_win *cwin, GError **error);
gboolean cmd_shuffle(const gchar *opt_name, const gchar *val,
		     struct con_win *cwin, GError **error);
gboolean cmd_repeat(const gchar *opt_name, const gchar *val,
		    struct con_win *cwin, GError **error);
gboolean cmd_inc_volume(const gchar *opt_name, const gchar *val,
			struct con_win *cwin, GError **error);
gboolean cmd_dec_volume(const gchar *opt_name, const gchar *val,
			struct con_win *cwin, GError **error);
gboolean cmd_show_osd(const gchar *opt_name, const gchar *val,
		      struct con_win *cwin, GError **error);
gboolean cmd_toggle_view(const gchar *opt_name, const gchar *val,
		      struct con_win *cwin, GError **error);
gboolean cmd_current_state(const gchar *opt_name, const gchar *val,
			   struct con_win *cwin, GError **error);
gboolean cmd_add_file(const gchar *opt_name, const gchar *val,
		      struct con_win *cwin, GError **error);

/* D-BUS functions */

DBusHandlerResult dbus_filter_handler(DBusConnection *conn,
				      DBusMessage *msg,
				      gpointer data);
void dbus_send_signal(const gchar *signal, struct con_win *cwin);
void dbus_handlers_free(struct con_win *cwin);

/* MPRIS functions */

gint mpris_init(struct con_win *cwin);
void mpris_update_any(struct con_win *cwin);
void mpris_update_metadata_changed(struct con_win *cwin);
void mpris_update_mobj_remove(struct con_win *cwin, PraghaMusicobject *mobj);
void mpris_update_mobj_added(struct con_win *cwin, PraghaMusicobject *mobj, GtkTreeIter *iter);
void mpris_update_mobj_changed(struct con_win *cwin, PraghaMusicobject *mobj, gint bitmask);
void mpris_update_tracklist_replaced(struct con_win *cwin);
void mpris_close(struct con_mpris2 *cmpris2);
void mpris_free(struct con_mpris2 *cmpris2);

/* Utilities */

void pragha_log_to_file (const gchar* log_domain, GLogLevelFlags log_level, const gchar* message, gpointer user_data);
gchar *e2_utf8_ndup (const gchar *str, glong num);
gsize levenshtein_strcmp(const gchar * s, const gchar * t);
gsize levenshtein_safe_strcmp(const gchar * s, const gchar * t);
gchar *g_strstr_lv (gchar *haystack, gchar *needle, gsize lv_distance);
gchar *pragha_strstr_lv(gchar *haystack, gchar *needle, struct con_win *cwin);
#if !GLIB_CHECK_VERSION(2,32,0)
gboolean nm_is_online ();
#endif
gboolean already_in_current_playlist(PraghaMusicobject *mobj, struct con_win *cwin);
GList *prepend_song_with_artist_and_title_to_mobj_list(const gchar *artist, const gchar *title, GList *list, struct con_win *cwin);
void set_watch_cursor (GtkWidget *widget);
void remove_watch_cursor (GtkWidget *widget);
GdkPixbuf *vgdk_pixbuf_new_from_memory (const char *data, size_t size);
gchar* sanitize_string_to_sqlite3(const gchar *str);
enum file_type get_file_type(const gchar *file);
gchar* get_mime_type(const gchar *file);
enum playlist_type pragha_pl_parser_guess_format_from_extension (const gchar *filename);
gboolean is_image_file(const gchar *file);
gchar* convert_length_str(gint length);
gboolean is_present_str_list(const gchar *str, GSList *list);
GSList* delete_from_str_list(const gchar *str, GSList *list);
gchar * path_get_dir_as_uri (const gchar *path);
gchar* get_display_filename(const gchar *filename, gboolean get_folder);
gchar* get_display_name(PraghaMusicobject *mobj);
void free_str_list(GSList *list);
gint compare_utf8_str(const gchar *str1, const gchar *str2);
gboolean validate_album_art_pattern(const gchar *pattern);
gboolean pragha_process_gtk_events ();
void open_url(const gchar *url, GtkWidget *parent);
void menu_position(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer user_data);
gboolean is_incompatible_upgrade(struct con_win *cwin);

/* Some widgets. */

gpointer sokoke_xfce_header_new (const gchar *header, const gchar *icon);
GtkWidget* pragha_search_entry_new(struct con_win *cwin);

/* GUI */

GtkWidget* create_main_region(struct con_win *cwin);
GtkWidget* create_playing_box(struct con_win *cwin);
GtkWidget* create_info_box(struct con_win *cwin);
GtkWidget* create_paned_region(struct con_win *cwin);
GtkWidget* create_search_bar(struct con_win *cwin);
GtkWidget* create_combo_order(struct con_win *cwin);
void create_status_icon(struct con_win *cwin);
gboolean exit_gui(GtkWidget *widget, GdkEvent *event, struct con_win *cwin);
void mainwindow_add_widget_to_info_box(struct con_win *cwin, GtkWidget *widget);
void gui_free(struct con_win *cwin);
void gui_backend_error_show_dialog_cb (PraghaBackend *backend, const GError *error, gpointer user_data);
void gui_backend_error_update_current_playlist_cb (PraghaBackend *backend, const GError *error, struct con_win *cwin);

/* Info bar import music */

gboolean info_bar_import_music_will_be_useful(struct con_win *cwin);
GtkWidget* create_info_bar_import_music(struct con_win *cwin);

/* Init */

gint init_dbus(struct con_win *cwin);
gint init_dbus_handlers(struct con_win *cwin);
gint init_options(struct con_win *cwin, int argc, char **argv);
gint init_taglib(struct con_win *cwin);
gint init_config(struct con_win *cwin);
gint init_audio(struct con_win *cwin);
gint init_threads(struct con_win *cwin);
gint init_first_state(struct con_win *cwin);
void state_free(struct con_state *cstate);
void init_tag_completion(struct con_win *cwin);
void init_gui(gint argc, gchar **argv, struct con_win *cwin);

/* gnome media keys */

gboolean gnome_media_keys_will_be_useful();
gint init_gnome_media_keys(struct con_win *cwin);
void gnome_media_keys_free(struct con_gnome_media_keys *gmk);

/* keybinder */

gint init_keybinder(struct con_win *cwin);
void keybinder_free();

/* notify */

gboolean can_support_actions(void);
void show_osd(struct con_win *cwin);
gint init_notify(struct con_win *cwin);
void notify_free();

/* pragha-hig.c: HIG helpers and pango extention. */

void gtk_label_set_attribute_bold(GtkLabel *label);
GtkWidget *
pragha_hig_workarea_table_add_section_title(GtkWidget *table, guint *row, const char *section_title);
void pragha_hig_workarea_table_add_wide_control(GtkWidget *table, guint *row, GtkWidget *widget);
void pragha_hig_workarea_table_add_wide_tall_control(GtkWidget *table, guint *row, GtkWidget *widget);
void pragha_hig_workarea_table_add_row(GtkWidget *table, guint *row, GtkWidget *label, GtkWidget *control);
GtkWidget *pragha_hig_workarea_table_new();
void pragha_hig_workarea_table_finish(GtkWidget *table, guint *row);

/* pragha-playback.c: Functions to control playback and notify events. */

void pragha_playback_notificate_new_track (PraghaBackend *backend, GParamSpec *pspec, struct con_win *cwin);

void pragha_playback_prev_track(struct con_win *cwin);
void pragha_playback_play_pause_resume(struct con_win *cwin);
void pragha_playback_stop(struct con_win *cwin);
void pragha_playback_next_track(struct con_win *cwin);
void pragha_advance_playback (struct con_win *cwin);


/* pragha-simple-async.c: Very simple and generic async API. */

typedef struct {
	gpointer userdata;
	gpointer finished_data;
	GThreadFunc func_w;
	GSourceFunc func_f;
} AsyncSimple;

gboolean pragha_async_set_idle_message (gpointer user_data);
GThread *pragha_async_launch(GThreadFunc worker_func, GSourceFunc finish_func, gpointer userdata);

/* Lastfm Helper */

#ifdef HAVE_LIBCLASTFM
void update_menubar_lastfm_state (struct con_win *cwin);
void edit_tags_corrected_by_lastfm(GtkButton *button, struct con_win *cwin);
void lastfm_get_similar_current_playlist_action (GtkAction *action, struct con_win *cwin);
void lastfm_track_current_playlist_love_action (GtkAction *action, struct con_win *cwin);
void lastfm_track_current_playlist_unlove_action (GtkAction *action, struct con_win *cwin);
void lastfm_add_favorites_action (GtkAction *action, struct con_win *cwin);
void lastfm_get_similar_action (GtkAction *action, struct con_win *cwin);
void lastfm_import_xspf_action (GtkAction *action, struct con_win *cwin);
void lastfm_track_love_action(GtkAction *action, struct con_win *cwin);
void lastfm_track_unlove_action (GtkAction *action, struct con_win *cwin);
void lastfm_now_playing_handler (struct con_win *cwin);
gint just_init_lastfm (struct con_win *cwin);
gint init_lastfm(struct con_win *cwin);
void lastfm_free(struct con_lastfm *clastfm);
#endif

/* Related info helpers */

void related_get_lyric_current_playlist_action(GtkAction *action, struct con_win *cwin);
void related_get_artist_info_current_playlist_action(GtkAction *action, struct con_win *cwin);
void related_get_artist_info_action(GtkAction *action, struct con_win *cwin);
void related_get_lyric_action(GtkAction *action, struct con_win *cwin);

int init_glyr_related (struct con_win *cwin);
void glyr_related_free (struct con_win *cwin);

/* Others */

void pragha_filter_dialog (struct con_win *cwin);

void exit_pragha(GtkWidget *widget, struct con_win *cwin);

void toogle_main_window(struct con_win *cwin, gboolean ignoreActivity);

#endif /* PRAGHA_H */
