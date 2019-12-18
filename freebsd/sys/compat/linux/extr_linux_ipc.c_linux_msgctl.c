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
struct thread {scalar_t__* td_retval; } ;
struct msqid_ds {int dummy; } ;
struct linux_msgctl_args {int cmd; int /*<<< orphan*/  buf; int /*<<< orphan*/  msqid; } ;
struct l_msqid64_ds {long msgpool; int /*<<< orphan*/  msgseg; int /*<<< orphan*/  msgtql; int /*<<< orphan*/  msgssz; scalar_t__ msgmni; scalar_t__ msgmnb; int /*<<< orphan*/  msgmax; scalar_t__ msgmap; } ;
struct l_msginfo {long msgpool; int /*<<< orphan*/  msgseg; int /*<<< orphan*/  msgtql; int /*<<< orphan*/  msgssz; scalar_t__ msgmni; scalar_t__ msgmnb; int /*<<< orphan*/  msgmax; scalar_t__ msgmap; } ;
typedef  int /*<<< orphan*/  linux_msqid64 ;
typedef  int /*<<< orphan*/  linux_msginfo ;
struct TYPE_2__ {scalar_t__ msgmni; int /*<<< orphan*/  msgseg; int /*<<< orphan*/  msgtql; int /*<<< orphan*/  msgssz; scalar_t__ msgmnb; int /*<<< orphan*/  msgmax; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EPERM ; 
 int LINUX_IPC_64 ; 
#define  LINUX_IPC_INFO 132 
#define  LINUX_IPC_RMID 131 
#define  LINUX_IPC_SET 130 
#define  LINUX_IPC_STAT 129 
#define  LINUX_MSG_INFO 128 
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsd_to_linux_msqid_ds (struct msqid_ds*,struct l_msqid64_ds*) ; 
 int copyout (struct l_msqid64_ds*,int /*<<< orphan*/ ,int) ; 
 int kern_msgctl (struct thread*,int /*<<< orphan*/ ,int,struct msqid_ds*) ; 
 int linux_msqid_pullup (int,struct l_msqid64_ds*,int /*<<< orphan*/ ) ; 
 int linux_msqid_pushdown (int,struct l_msqid64_ds*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_to_bsd_msqid_ds (struct l_msqid64_ds*,struct msqid_ds*) ; 
 int /*<<< orphan*/  memset (struct l_msqid64_ds*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ msginfo ; 

int
linux_msgctl(struct thread *td, struct linux_msgctl_args *args)
{
	int error, bsd_cmd;
	struct l_msqid64_ds linux_msqid64;
	struct msqid_ds bsd_msqid;

	memset(&linux_msqid64, 0, sizeof(linux_msqid64));

	bsd_cmd = args->cmd & ~LINUX_IPC_64;
	switch (bsd_cmd) {
	case LINUX_IPC_INFO:
	case LINUX_MSG_INFO: {
		struct l_msginfo linux_msginfo;

		memset(&linux_msginfo, 0, sizeof(linux_msginfo));
		/*
		 * XXX MSG_INFO uses the same data structure but returns different
		 * dynamic counters in msgpool, msgmap, and msgtql fields.
		 */
		linux_msginfo.msgpool = (long)msginfo.msgmni *
		    (long)msginfo.msgmnb / 1024L;	/* XXX MSG_INFO. */
		linux_msginfo.msgmap = msginfo.msgmnb;	/* XXX MSG_INFO. */
		linux_msginfo.msgmax = msginfo.msgmax;
		linux_msginfo.msgmnb = msginfo.msgmnb;
		linux_msginfo.msgmni = msginfo.msgmni;
		linux_msginfo.msgssz = msginfo.msgssz;
		linux_msginfo.msgtql = msginfo.msgtql;	/* XXX MSG_INFO. */
		linux_msginfo.msgseg = msginfo.msgseg;
		error = copyout(&linux_msginfo, PTRIN(args->buf),
		    sizeof(linux_msginfo));
		if (error == 0)
		    td->td_retval[0] = msginfo.msgmni;	/* XXX */

		return (error);
	}

	/*
	 * TODO: implement this
	 * case LINUX_MSG_STAT:
	 */
	case LINUX_IPC_STAT:
		/* NOTHING */
		break;

	case LINUX_IPC_SET:
		error = linux_msqid_pullup(args->cmd & LINUX_IPC_64,
		    &linux_msqid64, PTRIN(args->buf));
		if (error != 0)
			return (error);
		linux_to_bsd_msqid_ds(&linux_msqid64, &bsd_msqid);
		break;

	case LINUX_IPC_RMID:
		/* NOTHING */
		break;

	default:
		return (EINVAL);
		break;
	}

	error = kern_msgctl(td, args->msqid, bsd_cmd, &bsd_msqid);
	if (error != 0) {
		if (bsd_cmd == LINUX_IPC_RMID && error == EACCES)
			return (EPERM);
		if (bsd_cmd != LINUX_IPC_RMID || error != EINVAL)
			return (error);
	}

	if (bsd_cmd == LINUX_IPC_STAT) {
		bsd_to_linux_msqid_ds(&bsd_msqid, &linux_msqid64);
		return (linux_msqid_pushdown(args->cmd & LINUX_IPC_64,
		    &linux_msqid64, PTRIN(args->buf)));
	}

	return (0);
}