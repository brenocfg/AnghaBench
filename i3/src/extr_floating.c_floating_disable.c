#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ type; double percent; int /*<<< orphan*/  floating; struct TYPE_18__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  AFTER ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DONT_KILL_WINDOW ; 
 int /*<<< orphan*/  FLOATING_USER_OFF ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  con_attach (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* con_descend_tiling_focused (TYPE_1__*) ; 
 int /*<<< orphan*/  con_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  con_fix_percent (TYPE_1__*) ; 
 TYPE_1__* con_get_workspace (TYPE_1__*) ; 
 int /*<<< orphan*/  con_is_floating (TYPE_1__*) ; 
 scalar_t__ con_is_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  floating_set_hint_atom (TYPE_1__*,int) ; 
 int /*<<< orphan*/  insert_con_into (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_send_window_event (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  tree_close_internal (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void floating_disable(Con *con) {
    if (!con_is_floating(con)) {
        LOG("Container isn't floating, not doing anything.\n");
        return;
    }

    Con *ws = con_get_workspace(con);
    if (con_is_internal(ws)) {
        LOG("Can't disable floating for container in internal workspace.\n");
        return;
    }
    Con *tiling_focused = con_descend_tiling_focused(ws);

    if (tiling_focused->type == CT_WORKSPACE) {
        Con *parent = con->parent;
        con_detach(con);
        con->parent = NULL;
        tree_close_internal(parent, DONT_KILL_WINDOW, true);
        con_attach(con, tiling_focused, false);
        con->percent = 0.0;
        con_fix_percent(con->parent);
    } else {
        insert_con_into(con, tiling_focused, AFTER);
    }

    con->floating = FLOATING_USER_OFF;
    floating_set_hint_atom(con, false);
    ipc_send_window_event("floating", con);
}