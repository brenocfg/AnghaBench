#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_intern_atom_cookie_t ;
struct TYPE_8__ {scalar_t__ owner; } ;
typedef  TYPE_1__ xcb_get_selection_owner_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_selection_owner_cookie_t ;
typedef  int uint32_t ;
struct TYPE_11__ {int black_pixel; } ;
struct TYPE_10__ {int visual_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  atom; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  ELOG (char*,char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  XCB_ATOM_CARDINAL ; 
 int /*<<< orphan*/  XCB_ATOM_VISUALID ; 
 int /*<<< orphan*/  XCB_CURRENT_TIME ; 
 int XCB_CW_BACK_PIXEL ; 
 int XCB_CW_BORDER_PIXEL ; 
 int XCB_CW_COLORMAP ; 
 int XCB_CW_OVERRIDE_REDIRECT ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 int /*<<< orphan*/  XCB_WINDOW_CLASS_INPUT_OUTPUT ; 
 size_t _NET_SYSTEM_TRAY_ORIENTATION ; 
 int _NET_SYSTEM_TRAY_ORIENTATION_HORZ ; 
 size_t _NET_SYSTEM_TRAY_VISUAL ; 
 int /*<<< orphan*/ * atoms ; 
 int colormap ; 
 int /*<<< orphan*/  depth ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  init_tray_colors () ; 
 TYPE_6__* root_screen ; 
 int screen ; 
 scalar_t__ selwin ; 
 int /*<<< orphan*/  send_tray_clientmessage () ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_2__* tray_reply ; 
 TYPE_4__* visual_type ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  xcb_connection ; 
 int /*<<< orphan*/  xcb_create_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 scalar_t__ xcb_generate_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_get_selection_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_get_selection_owner_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_intern_atom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* xcb_intern_atom_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_root ; 
 int /*<<< orphan*/  xcb_set_selection_owner (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_tray(void) {
    DLOG("Initializing system tray functionality\n");
    /* request the tray manager atom for the X11 display we are running on */
    char atomname[strlen("_NET_SYSTEM_TRAY_S") + 11];
    snprintf(atomname, strlen("_NET_SYSTEM_TRAY_S") + 11, "_NET_SYSTEM_TRAY_S%d", screen);
    xcb_intern_atom_cookie_t tray_cookie;
    if (tray_reply == NULL)
        tray_cookie = xcb_intern_atom(xcb_connection, 0, strlen(atomname), atomname);

    /* tray support: we need a window to own the selection */
    selwin = xcb_generate_id(xcb_connection);
    uint32_t selmask = XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_OVERRIDE_REDIRECT | XCB_CW_COLORMAP;
    uint32_t selval[] = {root_screen->black_pixel, root_screen->black_pixel, 1, colormap};
    xcb_create_window(xcb_connection,
                      depth,
                      selwin,
                      xcb_root,
                      -1, -1,
                      1, 1,
                      0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      visual_type->visual_id,
                      selmask,
                      selval);

    uint32_t orientation = _NET_SYSTEM_TRAY_ORIENTATION_HORZ;
    /* set the atoms */
    xcb_change_property(xcb_connection,
                        XCB_PROP_MODE_REPLACE,
                        selwin,
                        atoms[_NET_SYSTEM_TRAY_ORIENTATION],
                        XCB_ATOM_CARDINAL,
                        32,
                        1,
                        &orientation);
    xcb_change_property(xcb_connection,
                        XCB_PROP_MODE_REPLACE,
                        selwin,
                        atoms[_NET_SYSTEM_TRAY_VISUAL],
                        XCB_ATOM_VISUALID,
                        32,
                        1,
                        &visual_type->visual_id);

    init_tray_colors();

    if (tray_reply == NULL) {
        if (!(tray_reply = xcb_intern_atom_reply(xcb_connection, tray_cookie, NULL))) {
            ELOG("Could not get atom %s\n", atomname);
            exit(EXIT_FAILURE);
        }
    }

    xcb_set_selection_owner(xcb_connection,
                            selwin,
                            tray_reply->atom,
                            XCB_CURRENT_TIME);

    /* Verify that we have the selection */
    xcb_get_selection_owner_cookie_t selcookie;
    xcb_get_selection_owner_reply_t *selreply;

    selcookie = xcb_get_selection_owner(xcb_connection, tray_reply->atom);
    if (!(selreply = xcb_get_selection_owner_reply(xcb_connection, selcookie, NULL))) {
        ELOG("Could not get selection owner for %s\n", atomname);
        exit(EXIT_FAILURE);
    }

    if (selreply->owner != selwin) {
        ELOG("Could not set the %s selection. "
             "Maybe another tray is already running?\n",
             atomname);
        /* NOTE that this error is not fatal. We just can’t provide tray
         * functionality */
        free(selreply);
        return;
    }

    free(selreply);

    send_tray_clientmessage();
}