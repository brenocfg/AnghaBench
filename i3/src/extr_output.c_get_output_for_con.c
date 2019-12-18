#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  Output ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* con_get_output (TYPE_1__*) ; 
 int /*<<< orphan*/ * get_output_by_name (int /*<<< orphan*/ ,int) ; 

Output *get_output_for_con(Con *con) {
    Con *output_con = con_get_output(con);
    Output *output = get_output_by_name(output_con->name, true);
    assert(output != NULL);

    return output;
}