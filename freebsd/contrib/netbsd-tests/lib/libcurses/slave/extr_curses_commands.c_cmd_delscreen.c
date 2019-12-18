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
typedef  int /*<<< orphan*/  SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  OK ; 
 int check_arg_count (int,int) ; 
 int /*<<< orphan*/  delscreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_count (int) ; 
 int /*<<< orphan*/  report_error (char*) ; 
 int /*<<< orphan*/  report_return (int /*<<< orphan*/ ) ; 
 scalar_t__ sscanf (char*,char*,int /*<<< orphan*/ **) ; 

void
cmd_delscreen(int nargs, char **args)
{
	SCREEN *scrn;

	if (check_arg_count(nargs, 1) == 1)
		return;

	if (sscanf(args[0], "%p", &scrn) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	delscreen(scrn); /* void return */
	report_count(1);
	report_return(OK);
}