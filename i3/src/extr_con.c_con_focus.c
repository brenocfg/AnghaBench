#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ urgent; struct TYPE_14__* parent; int /*<<< orphan*/  focus_head; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_get_workspace (TYPE_1__*) ; 
 scalar_t__ con_is_leaf (TYPE_1__*) ; 
 int /*<<< orphan*/  con_set_urgency (TYPE_1__*,int) ; 
 int /*<<< orphan*/  con_update_parents_urgency (TYPE_1__*) ; 
 TYPE_1__* focused ; 
 int /*<<< orphan*/  ipc_send_window_event (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  workspace_update_urgent_flag (int /*<<< orphan*/ ) ; 

void con_focus(Con *con) {
    assert(con != NULL);
    DLOG("con_focus = %p\n", con);

    /* 1: set focused-pointer to the new con */
    /* 2: exchange the position of the container in focus stack of the parent all the way up */
    TAILQ_REMOVE(&(con->parent->focus_head), con, focused);
    TAILQ_INSERT_HEAD(&(con->parent->focus_head), con, focused);
    if (con->parent->parent != NULL)
        con_focus(con->parent);

    focused = con;
    /* We can't blindly reset non-leaf containers since they might have
     * other urgent children. Therefore we only reset leafs and propagate
     * the changes upwards via con_update_parents_urgency() which does proper
     * checks before resetting the urgency.
     */
    if (con->urgent && con_is_leaf(con)) {
        con_set_urgency(con, false);
        con_update_parents_urgency(con);
        workspace_update_urgent_flag(con_get_workspace(con));
        ipc_send_window_event("urgent", con);
    }
}