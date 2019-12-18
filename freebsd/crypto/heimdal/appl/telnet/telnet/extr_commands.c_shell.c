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
 scalar_t__ TerminalWindowSize (long*,long*) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  connected ; 
 int /*<<< orphan*/  execl (char*,char*,char*,...) ; 
 int fork () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * saveline ; 
 int /*<<< orphan*/  sendnaws () ; 
 int /*<<< orphan*/  setcommandmode () ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static int
shell(int argc, char **argv)
{
    long oldrows, oldcols, newrows, newcols, err;

    setcommandmode();

    err = (TerminalWindowSize(&oldrows, &oldcols) == 0) ? 1 : 0;
    switch(fork()) {
    case -1:
	perror("Fork failed\r\n");
	break;

    case 0:
	{
	    /*
	     * Fire up the shell in the child.
	     */
	    char *shellp, *shellname;

	    shellp = getenv("SHELL");
	    if (shellp == NULL)
		shellp = "/bin/sh";
	    if ((shellname = strrchr(shellp, '/')) == 0)
		shellname = shellp;
	    else
		shellname++;
	    if (argc > 1)
		execl(shellp, shellname, "-c", &saveline[1], NULL);
	    else
		execl(shellp, shellname, NULL);
	    perror("Execl");
	    _exit(1);
	}
    default:
	    wait((int *)0);	/* Wait for the shell to complete */

	    if (TerminalWindowSize(&newrows, &newcols) && connected &&
		(err || ((oldrows != newrows) || (oldcols != newcols)))) {
		    sendnaws();
	    }
	    break;
    }
    return 1;
}