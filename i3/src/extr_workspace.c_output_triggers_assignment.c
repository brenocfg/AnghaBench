#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Workspace_Assignment {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * con; } ;
typedef  TYPE_1__ Output ;
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/ * get_assigned_output (int /*<<< orphan*/ ,int) ; 

bool output_triggers_assignment(Output *output, struct Workspace_Assignment *assignment) {
    Con *assigned = get_assigned_output(assignment->name, -1);
    return assigned && assigned == output->con;
}