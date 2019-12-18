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
 int /*<<< orphan*/  addarg (char const*) ; 
 int /*<<< orphan*/ * arglist ; 
 int /*<<< orphan*/  childpid ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  crash () ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * fin ; 
 int /*<<< orphan*/  fork () ; 
 char* infilename ; 
 int /*<<< orphan*/  pipe (int*) ; 
 int /*<<< orphan*/  prepend_cpp () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
open_input(const char *infile, const char *define)
{
	int pd[2];

	infilename = (infile == NULL) ? "<stdin>" : infile;
	(void) pipe(pd);
	switch (childpid = fork()) {
	case 0:
		prepend_cpp();
		addarg(define);
		if (infile)
			addarg(infile);
		addarg((char *)NULL);
		(void) close(1);
		(void) dup2(pd[1], 1);
		(void) close(pd[0]);
		execvp(arglist[0], arglist);
		err(1, "execvp %s", arglist[0]);
	case -1:
		err(1, "fork");
	}
	(void) close(pd[1]);
	fin = fdopen(pd[0], "r");
	if (fin == NULL) {
		warn("%s", infilename);
		crash();
	}
}