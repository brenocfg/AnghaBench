#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sequence; int /*<<< orphan*/  window; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ xcb_unmap_notify_event_t ;
typedef  int /*<<< orphan*/  xcb_get_input_focus_cookie_t ;
struct TYPE_8__ {scalar_t__ ignore_unmap; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  A__NET_WM_DESKTOP ; 
 int /*<<< orphan*/  A__NET_WM_STATE ; 
 int /*<<< orphan*/  DLOG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  DONT_KILL_WINDOW ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  XCB_ENTER_NOTIFY ; 
 int /*<<< orphan*/  add_ignore_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* con_by_frame_id (int /*<<< orphan*/ ) ; 
 TYPE_2__* con_by_window_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_close_internal (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tree_render () ; 
 int /*<<< orphan*/  xcb_delete_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_get_input_focus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_get_input_focus_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_unmap_notify_event(xcb_unmap_notify_event_t *event) {
    DLOG("UnmapNotify for 0x%08x (received from 0x%08x), serial %d\n", event->window, event->event, event->sequence);
    xcb_get_input_focus_cookie_t cookie;
    Con *con = con_by_window_id(event->window);
    if (con == NULL) {
        /* This could also be an UnmapNotify for the frame. We need to
         * decrement the ignore_unmap counter. */
        con = con_by_frame_id(event->window);
        if (con == NULL) {
            LOG("Not a managed window, ignoring UnmapNotify event\n");
            return;
        }

        if (con->ignore_unmap > 0)
            con->ignore_unmap--;
        /* See the end of this function. */
        cookie = xcb_get_input_focus(conn);
        DLOG("ignore_unmap = %d for frame of container %p\n", con->ignore_unmap, con);
        goto ignore_end;
    }

    /* See the end of this function. */
    cookie = xcb_get_input_focus(conn);

    if (con->ignore_unmap > 0) {
        DLOG("ignore_unmap = %d, dec\n", con->ignore_unmap);
        con->ignore_unmap--;
        goto ignore_end;
    }

    /* Since we close the container, we need to unset _NET_WM_DESKTOP and
     * _NET_WM_STATE according to the spec. */
    xcb_delete_property(conn, event->window, A__NET_WM_DESKTOP);
    xcb_delete_property(conn, event->window, A__NET_WM_STATE);

    tree_close_internal(con, DONT_KILL_WINDOW, false);
    tree_render();

ignore_end:
    /* If the client (as opposed to i3) destroyed or unmapped a window, an
     * EnterNotify event will follow (indistinguishable from an EnterNotify
     * event caused by moving your mouse), causing i3 to set focus to whichever
     * window is now visible.
     *
     * In a complex stacked or tabbed layout (take two v-split containers in a
     * tabbed container), when the bottom window in tab2 is closed, the bottom
     * window of tab1 is visible instead. X11 will thus send an EnterNotify
     * event for the bottom window of tab1, while the focus should be set to
     * the remaining window of tab2.
     *
     * Therefore, we ignore all EnterNotify events which have the same sequence
     * as an UnmapNotify event. */
    add_ignore_event(event->sequence, XCB_ENTER_NOTIFY);

    /* Since we just ignored the sequence of this UnmapNotify, we want to make
     * sure that following events use a different sequence. When putting xterm
     * into fullscreen and moving the pointer to a different window, without
     * using GetInputFocus, subsequent (legitimate) EnterNotify events arrived
     * with the same sequence and thus were ignored (see ticket #609). */
    free(xcb_get_input_focus_reply(conn, cookie, NULL));
}