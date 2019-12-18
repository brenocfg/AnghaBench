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
 int /*<<< orphan*/  report_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  subpad (int /*<<< orphan*/ *,int,int,int,int) ; 

void
cmd_subpad(int nargs, char **args)
{
	WINDOW *pad;
	int lines, cols, begin_y, begin_x;

	if (check_arg_count(nargs, 5) == 1)
		return;

	if (sscanf(args[0], "%p", &pad) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[1], "%d", &lines) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[2], "%d", &cols) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[3], "%d", &begin_y) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[4], "%d", &begin_x) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	report_count(1);
	report_ptr(subpad(pad, lines, cols, begin_y, begin_x));
}