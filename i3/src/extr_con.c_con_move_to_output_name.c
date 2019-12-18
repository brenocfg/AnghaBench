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
typedef  int /*<<< orphan*/  Output ;
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,char const*) ; 
 int /*<<< orphan*/  con_move_to_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * get_output_for_con (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_output_from_string (int /*<<< orphan*/ *,char const*) ; 

bool con_move_to_output_name(Con *con, const char *name, bool fix_coordinates) {
    Output *current_output = get_output_for_con(con);
    Output *output = get_output_from_string(current_output, name);
    if (output == NULL) {
        ELOG("Could not find output \"%s\"\n", name);
        return false;
    }

    con_move_to_output(con, output, fix_coordinates);
    return true;
}