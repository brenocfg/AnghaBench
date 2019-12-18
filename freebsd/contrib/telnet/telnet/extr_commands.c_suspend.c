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
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  TerminalSaveState () ; 
 scalar_t__ TerminalWindowSize (long*,long*) ; 
 scalar_t__ connected ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sendnaws () ; 
 int /*<<< orphan*/  setcommandmode () ; 
 int /*<<< orphan*/  setconnmode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
suspend(void)
{
#ifdef	SIGTSTP
    setcommandmode();
    {
	long oldrows, oldcols, newrows, newcols, err_;

	err_ = (TerminalWindowSize(&oldrows, &oldcols) == 0) ? 1 : 0;
	(void) kill(0, SIGTSTP);
	/*
	 * If we didn't get the window size before the SUSPEND, but we
	 * can get them now (?), then send the NAWS to make sure that
	 * we are set up for the right window size.
	 */
	if (TerminalWindowSize(&newrows, &newcols) && connected &&
	    (err_ || ((oldrows != newrows) || (oldcols != newcols)))) {
		sendnaws();
	}
    }
    /* reget parameters in case they were changed */
    TerminalSaveState();
    setconnmode(0);
#else
    printf("Suspend is not supported.  Try the '!' command instead\n");
#endif
    return 1;
}