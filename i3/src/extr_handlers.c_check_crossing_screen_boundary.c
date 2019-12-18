#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ disable_focus_follows_mouse; } ;
struct TYPE_4__ {int /*<<< orphan*/ * con; } ;
typedef  TYPE_1__ Output ;
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/ * con_descend_focused (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_focus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_get_workspace (int /*<<< orphan*/ *) ; 
 TYPE_3__ config ; 
 int /*<<< orphan*/ * focused ; 
 TYPE_1__* get_output_containing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_get_content (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_render () ; 
 int /*<<< orphan*/  workspace_show (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_crossing_screen_boundary(uint32_t x, uint32_t y) {
    Output *output;

    /* If the user disable focus follows mouse, we have nothing to do here */
    if (config.disable_focus_follows_mouse)
        return;

    if ((output = get_output_containing(x, y)) == NULL) {
        ELOG("ERROR: No such screen\n");
        return;
    }

    if (output->con == NULL) {
        ELOG("ERROR: The screen is not recognized by i3 (no container associated)\n");
        return;
    }

    /* Focus the output on which the user moved their cursor */
    Con *old_focused = focused;
    Con *next = con_descend_focused(output_get_content(output->con));
    /* Since we are switching outputs, this *must* be a different workspace, so
     * call workspace_show() */
    workspace_show(con_get_workspace(next));
    con_focus(next);

    /* If the focus changed, we re-render to get updated decorations */
    if (old_focused != focused)
        tree_render();
}