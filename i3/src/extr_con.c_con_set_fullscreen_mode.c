#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ fullscreen_mode_t ;
struct TYPE_7__ {scalar_t__ fullscreen_mode; TYPE_1__* window; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  A__NET_WM_STATE ; 
 int /*<<< orphan*/  A__NET_WM_STATE_FULLSCREEN ; 
 scalar_t__ CF_NONE ; 
 int /*<<< orphan*/  DLOG (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  ipc_send_window_event (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  xcb_add_property_atom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_remove_property_atom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void con_set_fullscreen_mode(Con *con, fullscreen_mode_t fullscreen_mode) {
    con->fullscreen_mode = fullscreen_mode;

    DLOG("mode now: %d\n", con->fullscreen_mode);

    /* Send an ipc window "fullscreen_mode" event */
    ipc_send_window_event("fullscreen_mode", con);

    /* update _NET_WM_STATE if this container has a window */
    /* TODO: when a window is assigned to a container which is already
     * fullscreened, this state needs to be pushed to the client, too */
    if (con->window == NULL)
        return;

    if (con->fullscreen_mode != CF_NONE) {
        DLOG("Setting _NET_WM_STATE_FULLSCREEN for con = %p / window = %d.\n", con, con->window->id);
        xcb_add_property_atom(conn, con->window->id, A__NET_WM_STATE, A__NET_WM_STATE_FULLSCREEN);
    } else {
        DLOG("Removing _NET_WM_STATE_FULLSCREEN for con = %p / window = %d.\n", con, con->window->id);
        xcb_remove_property_atom(conn, con->window->id, A__NET_WM_STATE, A__NET_WM_STATE_FULLSCREEN);
    }
}