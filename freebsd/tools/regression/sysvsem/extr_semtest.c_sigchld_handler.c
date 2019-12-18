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
union semun {struct semid_ds* buf; } ;
struct semid_ds {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_STAT ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ child_count ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_semid_ds (struct semid_ds*,int) ; 
 int semctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union semun) ; 
 int /*<<< orphan*/  sender_semid ; 
 int signal_was_sigchld ; 
 int wait (int*) ; 

void
sigchld_handler(int signo)
{
	union semun sun;
	struct semid_ds s_ds;
	int cstatus;

	/*
	 * Reap the child; if it exited successfully, then we're on the
	 * right track!
	 */
	if (wait(&cstatus) == -1)
		err(1, "wait");

	if (WIFEXITED(cstatus) == 0)
		errx(1, "receiver exited abnormally");

	if (WEXITSTATUS(cstatus) != 0)
		errx(1, "receiver exited with status %d",
		    WEXITSTATUS(cstatus));

	/*
	 * If we get here, the child has exited normally, and we should
	 * decrement the child count.  If the child_count reaches 0, we
	 * should exit.
	 */

	sun.buf = &s_ds;
	if (semctl(sender_semid, 0, IPC_STAT, sun) == -1)
		err(1, "semctl IPC_STAT");

	print_semid_ds(&s_ds, 0600);

	if (--child_count != 0) {
		signal_was_sigchld = 1;
		return;
	}

	exit(0);
}