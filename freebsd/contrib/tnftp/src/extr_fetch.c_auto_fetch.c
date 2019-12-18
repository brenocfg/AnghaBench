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
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int anonftp ; 
 scalar_t__ connected ; 
 int /*<<< orphan*/  disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int go_fetch (char*) ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  lostpeer ; 
 char* outfile ; 
 scalar_t__ redirect_loop ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  toplevel ; 
 int /*<<< orphan*/  xsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
auto_fetch(int argc, char *argv[])
{
	volatile int	argpos, rval;

	argpos = rval = 0;

	if (sigsetjmp(toplevel, 1)) {
		if (connected)
			disconnect(0, NULL);
		if (rval > 0)
			rval = argpos + 1;
		return (rval);
	}
	(void)xsignal(SIGINT, intr);
	(void)xsignal(SIGPIPE, lostpeer);

	/*
	 * Loop through as long as there's files to fetch.
	 */
	for (; (rval == 0) && (argpos < argc); argpos++) {
		if (strchr(argv[argpos], ':') == NULL)
			break;
		redirect_loop = 0;
		if (!anonftp)
			anonftp = 2;	/* Handle "automatic" transfers. */
		rval = go_fetch(argv[argpos]);
		if (outfile != NULL && strcmp(outfile, "-") != 0
		    && outfile[0] != '|')
			outfile = NULL;
		if (rval > 0)
			rval = argpos + 1;
	}

	if (connected && rval != -1)
		disconnect(0, NULL);
	return (rval);
}