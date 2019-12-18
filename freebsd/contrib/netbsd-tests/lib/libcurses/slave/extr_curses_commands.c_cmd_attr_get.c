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
typedef  short attr_t ;

/* Variables and functions */
 int attr_get (short*,short*,int /*<<< orphan*/ *) ; 
 int check_arg_count (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_count (int) ; 
 int /*<<< orphan*/  report_int (short) ; 
 int /*<<< orphan*/  report_return (int) ; 

void
cmd_attr_get(int nargs, char **args)
{
	attr_t attrs;
	short colours;
	int retval;

	if (check_arg_count(nargs, 0) == 1)
		return;

	retval = attr_get(&attrs, &colours, NULL);

	/* XXXX - call3 */
	report_count(3);
	report_return(retval);
	report_int(attrs);
	report_int(colours);
}