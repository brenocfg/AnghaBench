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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int check_arg_count (int,int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  newterm (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_count (int) ; 
 int /*<<< orphan*/  report_error (char*) ; 
 int /*<<< orphan*/  report_ptr (int /*<<< orphan*/ ) ; 

void
cmd_newterm(int nargs, char **args)
{
	FILE *in, *out;

	if (check_arg_count(nargs, 3) == 1)
		return;

	if ((in = fopen(args[1], "rw")) == NULL) {
		report_count(1);
		report_error("BAD FILE_ARGUMENT");
		return;
	}


	if ((out = fopen(args[2], "rw")) == NULL) {
		report_count(1);
		report_error("BAD FILE_ARGUMENT");
		return;
	}

	report_count(1);
	report_ptr(newterm(args[0], out, in));
}