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
 int check_arg_count (int,int) ; 
 int /*<<< orphan*/  chgat (int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_count (int) ; 
 int /*<<< orphan*/  report_error (char*) ; 
 int /*<<< orphan*/  report_return (int /*<<< orphan*/ ) ; 
 scalar_t__ sscanf (char*,char*,int*) ; 

void
cmd_chgat(int nargs, char **args)
{
	int n, attr, colour;

	if (check_arg_count(nargs, 4) == 1)
		return;

	if (sscanf(args[0], "%d", &n) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[1], "%d", &attr) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[2], "%d", &colour) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	/* Note: 4th argument unused in current curses implementation */
	report_count(1);
	report_return(chgat(n, attr, colour, NULL));
}