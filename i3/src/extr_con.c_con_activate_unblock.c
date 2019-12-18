#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  con_activate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_disable_fullscreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * con_get_fullscreen_covering_ws (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * con_get_workspace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_has_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * focused ; 
 int /*<<< orphan*/  workspace_show (int /*<<< orphan*/ *) ; 

void con_activate_unblock(Con *con) {
    Con *ws = con_get_workspace(con);
    Con *previous_focus = focused;
    Con *fullscreen_on_ws = con_get_fullscreen_covering_ws(ws);

    if (fullscreen_on_ws && fullscreen_on_ws != con && !con_has_parent(con, fullscreen_on_ws)) {
        con_disable_fullscreen(fullscreen_on_ws);
    }

    con_activate(con);

    /* If the container is not on the current workspace, workspace_show() will
     * switch to a different workspace and (if enabled) trigger a mouse pointer
     * warp to the currently focused container (!) on the target workspace.
     *
     * Therefore, before calling workspace_show(), we make sure that 'con' will
     * be focused on the workspace. However, we cannot just con_focus(con)
     * because then the pointer will not be warped at all (the code thinks we
     * are already there).
     *
     * So we focus 'con' to make it the currently focused window of the target
     * workspace, then revert focus. */
    if (ws != con_get_workspace(previous_focus)) {
        con_activate(previous_focus);
        /* Now switch to the workspace, then focus */
        workspace_show(ws);
        con_activate(con);
    }
}