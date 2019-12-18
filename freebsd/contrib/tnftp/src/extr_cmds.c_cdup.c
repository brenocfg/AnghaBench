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
 int COMPLETE ; 
 int ERROR ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int command (char*) ; 
 int dirchange ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  updateremotecwd () ; 
 scalar_t__ verbose ; 

void
cdup(int argc, char *argv[])
{
	int r;

	if (argc == 0) {
		UPRINTF("usage: %s\n", argv[0]);
		code = -1;
		return;
	}
	r = command("CDUP");
	if (r == ERROR && code == 500) {
		if (verbose)
			fputs("CDUP command not recognized, trying XCUP.\n",
			    ttyout);
		r = command("XCUP");
	}
	if (r == COMPLETE) {
		dirchange = 1;
		updateremotecwd();
	}
}