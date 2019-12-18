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

/* Variables and functions */
 int /*<<< orphan*/  border (int,int,int,int,int,int,int,int) ; 
 int check_arg_count (int,int) ; 
 int /*<<< orphan*/  report_count (int) ; 
 int /*<<< orphan*/  report_error (char*) ; 
 int /*<<< orphan*/  report_return (int /*<<< orphan*/ ) ; 
 scalar_t__ sscanf (char*,char*,int*) ; 

void
cmd_border(int nargs, char **args)
{
	int ls, rs, ts, bs, tl, tr, bl, br;

	if (check_arg_count(nargs, 8) == 1)
		return;

	if (sscanf(args[0], "%d", &ls) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}
	if (sscanf(args[1], "%d", &rs) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}
	if (sscanf(args[2], "%d", &ts) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}
	if (sscanf(args[3], "%d", &bs) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}
	if (sscanf(args[4], "%d", &tl) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}
	if (sscanf(args[5], "%d", &tr) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}
	if (sscanf(args[6], "%d", &bl) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}
	if (sscanf(args[7], "%d", &br) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	report_count(1);
	report_return(border(ls, rs, ts, bs, tl, tr, bl, br));
}