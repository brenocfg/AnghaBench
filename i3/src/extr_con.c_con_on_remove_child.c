#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ylength ;
typedef  int /*<<< orphan*/  yajl_gen ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/  urgent; int /*<<< orphan*/  name; int /*<<< orphan*/  focus_head; TYPE_1__* parent; } ;
struct TYPE_12__ {scalar_t__ type; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 scalar_t__ CT_DOCKAREA ; 
 scalar_t__ CT_OUTPUT ; 
 scalar_t__ CT_ROOT ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  DONT_KILL_WINDOW ; 
 int /*<<< orphan*/  I3_IPC_EVENT_WORKSPACE ; 
 int /*<<< orphan*/  LOG (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_force_split_parents_redraw (TYPE_2__*) ; 
 int /*<<< orphan*/  con_has_urgent_child (TYPE_2__*) ; 
 int con_num_children (TYPE_2__*) ; 
 int /*<<< orphan*/  con_update_parents_urgency (TYPE_2__*) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  get_buf ; 
 int /*<<< orphan*/  ipc_marshal_workspace_event (char*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_send_event (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tree_close_internal (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  workspace_is_visible (TYPE_2__*) ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void con_on_remove_child(Con *con) {
    DLOG("on_remove_child\n");

    /* Every container 'above' (in the hierarchy) the workspace content should
     * not be closed when the last child was removed */
    if (con->type == CT_OUTPUT ||
        con->type == CT_ROOT ||
        con->type == CT_DOCKAREA ||
        (con->parent != NULL && con->parent->type == CT_OUTPUT)) {
        DLOG("not handling, type = %d, name = %s\n", con->type, con->name);
        return;
    }

    /* For workspaces, close them only if they're not visible anymore */
    if (con->type == CT_WORKSPACE) {
        if (TAILQ_EMPTY(&(con->focus_head)) && !workspace_is_visible(con)) {
            LOG("Closing old workspace (%p / %s), it is empty\n", con, con->name);
            yajl_gen gen = ipc_marshal_workspace_event("empty", con, NULL);
            tree_close_internal(con, DONT_KILL_WINDOW, false);

            const unsigned char *payload;
            ylength length;
            y(get_buf, &payload, &length);
            ipc_send_event("workspace", I3_IPC_EVENT_WORKSPACE, (const char *)payload);

            y(free);
        }
        return;
    }

    con_force_split_parents_redraw(con);
    con->urgent = con_has_urgent_child(con);
    con_update_parents_urgency(con);

    /* TODO: check if this container would swallow any other client and
     * don’t close it automatically. */
    int children = con_num_children(con);
    if (children == 0) {
        DLOG("Container empty, closing\n");
        tree_close_internal(con, DONT_KILL_WINDOW, false);
        return;
    }
}