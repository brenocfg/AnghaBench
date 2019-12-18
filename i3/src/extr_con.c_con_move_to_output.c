#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  con; } ;
typedef  TYPE_1__ Output ;
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GREP_FIRST (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child ; 
 int /*<<< orphan*/  con_move_to_workspace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  output_get_content (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_primary_name (TYPE_1__*) ; 
 int /*<<< orphan*/  workspace_is_visible (int /*<<< orphan*/ ) ; 

void con_move_to_output(Con *con, Output *output, bool fix_coordinates) {
    Con *ws = NULL;
    GREP_FIRST(ws, output_get_content(output->con), workspace_is_visible(child));
    assert(ws != NULL);
    DLOG("Moving con %p to output %s\n", con, output_primary_name(output));
    con_move_to_workspace(con, ws, fix_coordinates, false, false);
}