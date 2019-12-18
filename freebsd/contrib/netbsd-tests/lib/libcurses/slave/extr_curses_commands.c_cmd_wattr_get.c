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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int check_arg_count (int,int) ; 
 int /*<<< orphan*/  report_count (int) ; 
 int /*<<< orphan*/  report_error (char*) ; 
 int /*<<< orphan*/  report_int (short) ; 
 int /*<<< orphan*/  report_return (int /*<<< orphan*/ ) ; 
 scalar_t__ sscanf (char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  wattr_get (int /*<<< orphan*/ *,int*,short*,int /*<<< orphan*/ *) ; 

void
cmd_wattr_get(int nargs, char **args)
{
	WINDOW *win;
	int attr;
	short pair;

	if (check_arg_count(nargs, 1) == 1)
		return;

	if (sscanf(args[0], "%p", &win) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	/* XXX - call3 */
	report_count(3);
	report_return(wattr_get(win, &attr, &pair, NULL));
	report_int(attr);
	report_int(pair);
}