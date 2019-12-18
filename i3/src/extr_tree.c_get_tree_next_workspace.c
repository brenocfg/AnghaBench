#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  direction_t ;
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_14__ {TYPE_1__ rect; } ;
struct TYPE_13__ {int /*<<< orphan*/  con; } ;
typedef  TYPE_2__ Output ;
typedef  TYPE_3__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  CF_GLOBAL ; 
 int /*<<< orphan*/  CLOSEST_OUTPUT ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  GREP_FIRST (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child ; 
 scalar_t__ con_get_fullscreen_con (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_output_containing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_output_next (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_get_content (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_primary_name (TYPE_2__*) ; 
 int /*<<< orphan*/  workspace_is_visible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Con *get_tree_next_workspace(Con *con, direction_t direction) {
    if (con_get_fullscreen_con(con, CF_GLOBAL)) {
        DLOG("Cannot change workspace while in global fullscreen mode.\n");
        return NULL;
    }

    Output *current_output = get_output_containing(con->rect.x, con->rect.y);
    if (!current_output) {
        return NULL;
    }
    DLOG("Current output is %s\n", output_primary_name(current_output));

    Output *next_output = get_output_next(direction, current_output, CLOSEST_OUTPUT);
    if (!next_output) {
        return NULL;
    }
    DLOG("Next output is %s\n", output_primary_name(next_output));

    /* Find visible workspace on next output */
    Con *workspace = NULL;
    GREP_FIRST(workspace, output_get_content(next_output->con), workspace_is_visible(child));
    return workspace;
}