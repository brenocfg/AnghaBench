#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  direction_t ;
struct TYPE_18__ {int /*<<< orphan*/  deco_render_params; } ;
struct TYPE_17__ {int /*<<< orphan*/  con; } ;
typedef  TYPE_1__ Output ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSEST_OUTPUT ; 
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GREP_FIRST (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attach_to_workspace (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child ; 
 int /*<<< orphan*/  con_focus (TYPE_2__*) ; 
 TYPE_2__* con_get_workspace (TYPE_2__*) ; 
 int /*<<< orphan*/  croot ; 
 int /*<<< orphan*/  ewmh_update_wm_desktop () ; 
 TYPE_2__* focused ; 
 TYPE_1__* get_output_for_con (TYPE_2__*) ; 
 TYPE_1__* get_output_next (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_send_window_event (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  output_get_content (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_flatten (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workspace_is_visible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workspace_show (TYPE_2__*) ; 

__attribute__((used)) static void move_to_output_directed(Con *con, direction_t direction) {
    Output *current_output = get_output_for_con(con);
    Output *output = get_output_next(direction, current_output, CLOSEST_OUTPUT);

    if (!output) {
        DLOG("No output in this direction found. Not moving.\n");
        return;
    }

    Con *ws = NULL;
    GREP_FIRST(ws, output_get_content(output->con), workspace_is_visible(child));

    if (!ws) {
        DLOG("No workspace on output in this direction found. Not moving.\n");
        return;
    }

    Con *old_ws = con_get_workspace(con);
    const bool moves_focus = (focused == con);
    attach_to_workspace(con, ws, direction);
    if (moves_focus) {
        /* workspace_show will not correctly update the active workspace because
         * the focused container, con, is now a child of ws. To work around this
         * and still produce the correct workspace focus events (see
         * 517-regress-move-direction-ipc.t) we need to temporarily set focused
         * to the old workspace. */
        focused = old_ws;
        workspace_show(ws);
        con_focus(con);
    }

    /* force re-painting the indicators */
    FREE(con->deco_render_params);

    ipc_send_window_event("move", con);
    tree_flatten(croot);
    ewmh_update_wm_desktop();
}