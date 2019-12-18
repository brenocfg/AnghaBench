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
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int command (char*,char*) ; 
 int dirchange ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyout ; 
 scalar_t__ verbose ; 

void
makedir(int argc, char *argv[])
{
	int r;

	if (argc == 0 || argc > 2 ||
	    (argc == 1 && !another(&argc, &argv, "directory-name"))) {
		UPRINTF("usage: %s directory-name\n", argv[0]);
		code = -1;
		return;
	}
	r = command("MKD %s", argv[1]);
	if (r == ERROR && code == 500) {
		if (verbose)
			fputs("MKD command not recognized, trying XMKD.\n",
			    ttyout);
		r = command("XMKD %s", argv[1]);
	}
	if (r == COMPLETE)
		dirchange = 1;
}