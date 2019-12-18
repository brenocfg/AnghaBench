#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct test_mymsg {int /*<<< orphan*/  mtext; int /*<<< orphan*/  mtype; } ;
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct TYPE_2__ {int mode; } ;
struct msqid_ds {TYPE_1__ msg_perm; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int IPC_CREAT ; 
 int /*<<< orphan*/  IPC_SET ; 
 int /*<<< orphan*/  IPC_STAT ; 
 int /*<<< orphan*/  MTYPE_1 ; 
 int /*<<< orphan*/  MTYPE_1_ACK ; 
 int /*<<< orphan*/  MTYPE_2 ; 
 int /*<<< orphan*/  MTYPE_2_ACK ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGSYS ; 
 int atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct msqid_ds*,int) ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  ftok (char*,int) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  m1_str ; 
 int /*<<< orphan*/  m2_str ; 
 int msgctl (int,int /*<<< orphan*/ ,struct msqid_ds*) ; 
 int msgget (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msgkey ; 
 scalar_t__ msgrcv (int,struct test_mymsg*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msgsnd (int,struct test_mymsg*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_msqid_ds (struct msqid_ds*,int) ; 
 int /*<<< orphan*/  receiver () ; 
 int sender_msqid ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigchld_handler ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigsuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigsys_handler ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct sigaction sa;
	struct msqid_ds m_ds;
	struct test_mymsg m;
	sigset_t sigmask;

	if (argc != 2)
		usage();

	/*
	 * Install a SIGSYS handler so that we can exit gracefully if
	 * System V Message Queue support isn't in the kernel.
	 */
	sa.sa_handler = sigsys_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGSYS, &sa, NULL) == -1)
		err(1, "sigaction SIGSYS");

	/*
	 * Install and SIGCHLD handler to deal with all possible exit
	 * conditions of the receiver.
	 */
	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
		err(1, "sigaction SIGCHLD");

	msgkey = ftok(argv[1], 4160);

	/*
	 * Initialize child_pid to ourselves to that the cleanup function
	 * works before we create the receiver.
	 */
	child_pid = getpid();

	/*
	 * Make sure that when the sender exits, the message queue is
	 * removed.
	 */
	if (atexit(cleanup) == -1)
		err(1, "atexit");

	if ((sender_msqid = msgget(msgkey, IPC_CREAT | 0640)) == -1)
		err(1, "msgget");

	if (msgctl(sender_msqid, IPC_STAT, &m_ds) == -1)
		err(1, "msgctl IPC_STAT");

	print_msqid_ds(&m_ds, 0640);

	m_ds.msg_perm.mode = (m_ds.msg_perm.mode & ~0777) | 0600;

	if (msgctl(sender_msqid, IPC_SET, &m_ds) == -1)
		err(1, "msgctl IPC_SET");

	bzero(&m_ds, sizeof m_ds);

	if (msgctl(sender_msqid, IPC_STAT, &m_ds) == -1)
		err(1, "msgctl IPC_STAT");

	if ((m_ds.msg_perm.mode & 0777) != 0600)
		err(1, "IPC_SET of mode didn't hold");

	print_msqid_ds(&m_ds, 0600);

	switch ((child_pid = fork())) {
	case -1:
		err(1, "fork");
		/* NOTREACHED */

	case 0:
		receiver();
		break;

	default:
		break;
	}

	/*
	 * Send the first message to the receiver and wait for the ACK.
	 */
	m.mtype = MTYPE_1;
	strcpy(m.mtext, m1_str);
	if (msgsnd(sender_msqid, &m, strlen(m1_str) + 1, 0) == -1)
		err(1, "sender: msgsnd 1");

	if (msgrcv(sender_msqid, &m, sizeof(m.mtext), MTYPE_1_ACK, 0) !=
	    strlen(m1_str) + 1)
		err(1, "sender: msgrcv 1 ack");

	print_msqid_ds(&m_ds, 0600);

	/*
	 * Send the second message to the receiver and wait for the ACK.
	 */
	m.mtype = MTYPE_2;
	strcpy(m.mtext, m2_str);
	if (msgsnd(sender_msqid, &m, strlen(m2_str) + 1, 0) == -1)
		err(1, "sender: msgsnd 2");

	if (msgrcv(sender_msqid, &m, sizeof(m.mtext), MTYPE_2_ACK, 0) !=
	    strlen(m2_str) + 1)
		err(1, "sender: msgrcv 2 ack");

	/*
	 * Suspend forever; when we get SIGCHLD, the handler will exit.
	 */
	sigemptyset(&sigmask);
	(void) sigsuspend(&sigmask);

	/*
	 * ...and any other signal is an unexpected error.
	 */
	errx(1, "sender: received unexpected signal");
}