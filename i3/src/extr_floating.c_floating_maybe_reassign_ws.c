#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  name; int /*<<< orphan*/  focus_head; int /*<<< orphan*/  rect; } ;
struct TYPE_13__ {scalar_t__ con; } ;
typedef  TYPE_1__ Output ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  ELOG (char*) ; 
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_activate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_descend_focused (TYPE_2__*) ; 
 scalar_t__ con_get_output (TYPE_2__*) ; 
 int /*<<< orphan*/  con_get_workspace (TYPE_2__*) ; 
 scalar_t__ con_is_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_move_to_workspace (TYPE_2__*,TYPE_2__*,int,int,int) ; 
 TYPE_1__* get_output_from_rect (int /*<<< orphan*/ ) ; 
 TYPE_2__* output_get_content (scalar_t__) ; 
 int /*<<< orphan*/  workspace_show (TYPE_2__*) ; 

bool floating_maybe_reassign_ws(Con *con) {
    if (con_is_internal(con_get_workspace(con))) {
        DLOG("Con in an internal workspace\n");
        return false;
    }

    Output *output = get_output_from_rect(con->rect);

    if (!output) {
        ELOG("No output found at destination coordinates?\n");
        return false;
    }

    if (con_get_output(con) == output->con) {
        DLOG("still the same ws\n");
        return false;
    }

    DLOG("Need to re-assign!\n");

    Con *content = output_get_content(output->con);
    Con *ws = TAILQ_FIRST(&(content->focus_head));
    DLOG("Moving con %p / %s to workspace %p / %s\n", con, con->name, ws, ws->name);
    con_move_to_workspace(con, ws, false, true, false);
    workspace_show(ws);
    con_activate(con_descend_focused(con));
    return true;
}