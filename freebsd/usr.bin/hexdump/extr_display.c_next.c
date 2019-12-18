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
 int /*<<< orphan*/  CAPH_READ ; 
 char** _argv ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doskip (char*,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int exitval ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freopen (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ skip ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
next(char **argv)
{
	static int done;
	int statok;

	if (argv) {
		_argv = argv;
		return(1);
	}
	for (;;) {
		if (*_argv) {
			done = 1;
			if (!(freopen(*_argv, "r", stdin))) {
				warn("%s", *_argv);
				exitval = 1;
				++_argv;
				continue;
			}
			statok = 1;
		} else {
			if (done++)
				return(0);
			statok = 0;
		}

		if (caph_limit_stream(fileno(stdin), CAPH_READ) < 0)
			err(1, "unable to restrict %s",
			    statok ? *_argv : "stdin");

		/*
		 * We've opened our last input file; enter capsicum sandbox.
		 */
		if (statok == 0 || *(_argv + 1) == NULL) {
			if (caph_enter() < 0)
				err(1, "unable to enter capability mode");
		}

		if (skip)
			doskip(statok ? *_argv : "stdin", statok);
		if (*_argv)
			++_argv;
		if (!skip)
			return(1);
	}
	/* NOTREACHED */
}