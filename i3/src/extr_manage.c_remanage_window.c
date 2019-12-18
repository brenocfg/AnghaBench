#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xcb_window_t ;
struct TYPE_18__ {scalar_t__ managed_since; int /*<<< orphan*/  id; } ;
struct TYPE_17__ {TYPE_4__* window; } ;
typedef  int /*<<< orphan*/  Match ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 scalar_t__ XCB_NONE ; 
 scalar_t__ _match_depth (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  _remove_matches (TYPE_1__*) ; 
 TYPE_1__* con_for_window (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ **) ; 
 scalar_t__ con_get_workspace (TYPE_1__*) ; 
 int /*<<< orphan*/  con_merge_into (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  croot ; 
 int /*<<< orphan*/  ewmh_update_wm_desktop () ; 
 int /*<<< orphan*/  restore_kill_placeholder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_assignments (TYPE_4__*) ; 
 int /*<<< orphan*/  startup_sequence_delete_by_window (TYPE_4__*) ; 
 int /*<<< orphan*/  window_free (TYPE_4__*) ; 
 int /*<<< orphan*/  x_reparent_child (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  xcb_destroy_window (int /*<<< orphan*/ ,scalar_t__) ; 

Con *remanage_window(Con *con) {
    Match *match;
    Con *nc = con_for_window(croot, con->window, &match);
    if (nc == NULL || nc->window == NULL || nc->window == con->window) {
        run_assignments(con->window);
        return con;
    }
    /* Make sure the placeholder that wants to swallow this window didn't spawn
     * after the window to follow current behavior: adding a placeholder won't
     * swallow windows currently managed. */
    if (nc->window->managed_since > con->window->managed_since) {
        run_assignments(con->window);
        return con;
    }

    if (!restore_kill_placeholder(nc->window->id)) {
        DLOG("Uh?! Container without a placeholder, but with a window, has swallowed this managed window?!\n");
    } else {
        _remove_matches(nc);
    }
    window_free(nc->window);

    xcb_window_t old_frame = _match_depth(con->window, nc);

    x_reparent_child(nc, con);

    bool moved_workpaces = (con_get_workspace(nc) != con_get_workspace(con));

    con_merge_into(con, nc);

    /* Destroy the old frame if we had to reframe the container. This needs to be done
     * after rendering in order to prevent the background from flickering in its place. */
    if (old_frame != XCB_NONE) {
        xcb_destroy_window(conn, old_frame);
    }

    run_assignments(nc->window);

    if (moved_workpaces) {
        /* If the window is associated with a startup sequence, delete it so
         * child windows won't be created on the old workspace. */
        startup_sequence_delete_by_window(nc->window);

        ewmh_update_wm_desktop();
    }

    return nc;
}