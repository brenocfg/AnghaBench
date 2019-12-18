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
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int WNOHANG ; 
 int __WALL ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_kill_ptraced_process (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uml_abort () ; 
 int waitpid (int,int /*<<< orphan*/ *,int) ; 

void os_dump_core(void)
{
	int pid;

	signal(SIGSEGV, SIG_DFL);

	/*
	 * We are about to SIGTERM this entire process group to ensure that
	 * nothing is around to run after the kernel exits.  The
	 * kernel wants to abort, not die through SIGTERM, so we
	 * ignore it here.
	 */

	signal(SIGTERM, SIG_IGN);
	kill(0, SIGTERM);
	/*
	 * Most of the other processes associated with this UML are
	 * likely sTopped, so give them a SIGCONT so they see the
	 * SIGTERM.
	 */
	kill(0, SIGCONT);

	/*
	 * Now, having sent signals to everyone but us, make sure they
	 * die by ptrace.  Processes can survive what's been done to
	 * them so far - the mechanism I understand is receiving a
	 * SIGSEGV and segfaulting immediately upon return.  There is
	 * always a SIGSEGV pending, and (I'm guessing) signals are
	 * processed in numeric order so the SIGTERM (signal 15 vs
	 * SIGSEGV being signal 11) is never handled.
	 *
	 * Run a waitpid loop until we get some kind of error.
	 * Hopefully, it's ECHILD, but there's not a lot we can do if
	 * it's something else.  Tell os_kill_ptraced_process not to
	 * wait for the child to report its death because there's
	 * nothing reasonable to do if that fails.
	 */

	while ((pid = waitpid(-1, NULL, WNOHANG | __WALL)) > 0)
		os_kill_ptraced_process(pid, 0);

	uml_abort();
}