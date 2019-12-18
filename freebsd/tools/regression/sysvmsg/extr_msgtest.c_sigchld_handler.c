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
struct msqid_ds {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_STAT ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ child_pid ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int msgctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msqid_ds*) ; 
 int /*<<< orphan*/  print_msqid_ds (struct msqid_ds*,int) ; 
 int /*<<< orphan*/  sender_msqid ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

void
sigchld_handler(int signo)
{
	struct msqid_ds m_ds;
	int cstatus;

	/*
	 * Reap the child; if it exited successfully, then the test passed!
	 */
	if (waitpid(child_pid, &cstatus, 0) != child_pid)
		err(1, "waitpid");

	if (WIFEXITED(cstatus) == 0)
		errx(1, "receiver exited abnormally");

	if (WEXITSTATUS(cstatus) != 0)
		errx(1, "receiver exited with status %d",
		    WEXITSTATUS(cstatus));

	/*
	 * If we get here, the child has exited normally, and thus
	 * we should exit normally too.  First, tho, we print out
	 * the final stats for the message queue.
	 */

	if (msgctl(sender_msqid, IPC_STAT, &m_ds) == -1)
		err(1, "msgctl IPC_STAT");

	print_msqid_ds(&m_ds, 0600);

	exit(0);
}