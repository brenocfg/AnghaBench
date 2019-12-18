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
struct sigaction {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSHTTY ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tcgetpgrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcsetpgrp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setttypgrp(int pgrp)
{
    /*
     * If we are piping out a builtin, eg. 'echo | more' things can go
     * out of sequence, i.e. the more can run before the echo. This
     * can happen even if we have vfork, since the echo will be forked
     * with the regular fork. In this case, we need to set the tty
     * pgrp ourselves. If that happens, then the process will be still
     * alive. And the tty process group will already be set.
     * This should fix the famous sequent problem as a side effect:
     *    The controlling terminal is lost if all processes in the
     *    terminal process group are zombies. In this case tcgetpgrp()
     *    returns 0. If this happens we must set the terminal process
     *    group again.
     */
    if (tcgetpgrp(FSHTTY) != pgrp) {
#ifdef POSIXJOBS
	struct sigaction old;

        /*
	 * tcsetpgrp will set SIGTTOU to all the the processes in 
	 * the background according to POSIX... We ignore this here.
	 */
	sigaction(SIGTTOU, NULL, &old);
	signal(SIGTTOU, SIG_IGN);
#endif
	(void) tcsetpgrp(FSHTTY, pgrp);
# ifdef POSIXJOBS
	sigaction(SIGTTOU, &old, NULL);
# endif

    }
}