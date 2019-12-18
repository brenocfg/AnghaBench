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
typedef  int /*<<< orphan*/  chtype ;

/* Variables and functions */
 int check_arg_count (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  mvinchnstr (int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  report_count (int) ; 
 int /*<<< orphan*/  report_error (char*) ; 
 int /*<<< orphan*/  report_nstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_return (int /*<<< orphan*/ ) ; 
 scalar_t__ sscanf (char*,char*,int*) ; 

void
cmd_mvinchnstr(int nargs, char **args)
{
	int y, x, count;
	chtype *string;

	if (check_arg_count(nargs, 3) == 1)
		return;

	if (sscanf(args[0], "%d", &y) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[1], "%d", &x) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[2], "%d", &count) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if ((string = malloc((count + 1) * sizeof(chtype))) == NULL) {
		report_count(1);
		report_error("MALLOC_FAILED");
		return;
	}

	/* XXX call2 */
	report_count(2);
	report_return(mvinchnstr(y, x, string, count));
	report_nstr(string);
	free(string);
}