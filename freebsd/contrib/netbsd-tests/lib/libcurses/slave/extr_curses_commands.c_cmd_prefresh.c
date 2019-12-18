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
 int /*<<< orphan*/  prefresh (int /*<<< orphan*/ *,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  report_count (int) ; 
 int /*<<< orphan*/  report_error (char*) ; 
 int /*<<< orphan*/  report_return (int /*<<< orphan*/ ) ; 
 scalar_t__ sscanf (char*,char*,int*) ; 

void
cmd_prefresh(int nargs, char **args)
{
	int pbeg_y, pbeg_x, sbeg_y, sbeg_x, smax_y, smax_x;
	WINDOW *pad;

	if (check_arg_count(nargs, 7) == 1)
		return;

	if (sscanf(args[0], "%p", &pad) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[1], "%d", &pbeg_y) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[2], "%d", &pbeg_x) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[3], "%d", &sbeg_y) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[4], "%d", &sbeg_x) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[5], "%d", &smax_y) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[6], "%d", &smax_x) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	/* XXX causes refresh */
	report_count(1);
	report_return(prefresh(pad, pbeg_y, pbeg_x, sbeg_y, sbeg_x, smax_y,
			       smax_x));

}