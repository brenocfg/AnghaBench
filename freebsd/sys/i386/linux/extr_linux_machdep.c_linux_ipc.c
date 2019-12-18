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
typedef  int /*<<< orphan*/  tmp ;
struct thread {int /*<<< orphan*/ * td_retval; } ;
struct linux_shmget_args {int /*<<< orphan*/  shmflg; int /*<<< orphan*/  size; int /*<<< orphan*/  key; } ;
struct linux_shmdt_args {void* shmaddr; } ;
struct linux_shmctl_args {void* buf; int /*<<< orphan*/  cmd; int /*<<< orphan*/  shmid; } ;
struct linux_shmat_args {int /*<<< orphan*/  shmflg; void* shmaddr; int /*<<< orphan*/  shmid; } ;
struct linux_semop_args {int /*<<< orphan*/  nsops; void* tsops; int /*<<< orphan*/  semid; } ;
struct linux_semget_args {int /*<<< orphan*/  semflg; int /*<<< orphan*/  nsems; int /*<<< orphan*/  key; } ;
struct l_ipc_kludge {int /*<<< orphan*/  msgtyp; int /*<<< orphan*/  msgp; } ;
struct linux_semctl_args {struct l_ipc_kludge arg; int /*<<< orphan*/  cmd; int /*<<< orphan*/  semnum; int /*<<< orphan*/  semid; } ;
struct linux_msgsnd_args {int /*<<< orphan*/  msgflg; int /*<<< orphan*/  msgsz; void* msgp; int /*<<< orphan*/  msqid; } ;
struct linux_msgrcv_args {int /*<<< orphan*/  msgtyp; void* msgp; int /*<<< orphan*/  msgflg; int /*<<< orphan*/  msgsz; int /*<<< orphan*/  msqid; } ;
struct linux_msgget_args {int /*<<< orphan*/  msgflg; int /*<<< orphan*/  key; } ;
struct linux_msgctl_args {void* buf; int /*<<< orphan*/  cmd; int /*<<< orphan*/  msqid; } ;
struct linux_ipc_args {int what; int /*<<< orphan*/  ptr; int /*<<< orphan*/  arg2; int /*<<< orphan*/  arg1; int /*<<< orphan*/  arg3; int /*<<< orphan*/  arg5; } ;
typedef  int /*<<< orphan*/  l_uintptr_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int EINVAL ; 
#define  LINUX_MSGCTL 138 
#define  LINUX_MSGGET 137 
#define  LINUX_MSGRCV 136 
#define  LINUX_MSGSND 135 
#define  LINUX_SEMCTL 134 
#define  LINUX_SEMGET 133 
#define  LINUX_SEMOP 132 
#define  LINUX_SHMAT 131 
#define  LINUX_SHMCTL 130 
#define  LINUX_SHMDT 129 
#define  LINUX_SHMGET 128 
 void* PTRIN (int /*<<< orphan*/ ) ; 
 int copyin (void*,struct l_ipc_kludge*,int) ; 
 int copyout (int /*<<< orphan*/ *,void*,int) ; 
 int linux_msgctl (struct thread*,struct linux_msgctl_args*) ; 
 int linux_msgget (struct thread*,struct linux_msgget_args*) ; 
 int linux_msgrcv (struct thread*,struct linux_msgrcv_args*) ; 
 int linux_msgsnd (struct thread*,struct linux_msgsnd_args*) ; 
 int linux_semctl (struct thread*,struct linux_semctl_args*) ; 
 int linux_semget (struct thread*,struct linux_semget_args*) ; 
 int linux_semop (struct thread*,struct linux_semop_args*) ; 
 int linux_shmat (struct thread*,struct linux_shmat_args*) ; 
 int linux_shmctl (struct thread*,struct linux_shmctl_args*) ; 
 int linux_shmdt (struct thread*,struct linux_shmdt_args*) ; 
 int linux_shmget (struct thread*,struct linux_shmget_args*) ; 

int
linux_ipc(struct thread *td, struct linux_ipc_args *args)
{

	switch (args->what & 0xFFFF) {
	case LINUX_SEMOP: {
		struct linux_semop_args a;

		a.semid = args->arg1;
		a.tsops = PTRIN(args->ptr);
		a.nsops = args->arg2;
		return (linux_semop(td, &a));
	}
	case LINUX_SEMGET: {
		struct linux_semget_args a;

		a.key = args->arg1;
		a.nsems = args->arg2;
		a.semflg = args->arg3;
		return (linux_semget(td, &a));
	}
	case LINUX_SEMCTL: {
		struct linux_semctl_args a;
		int error;

		a.semid = args->arg1;
		a.semnum = args->arg2;
		a.cmd = args->arg3;
		error = copyin(PTRIN(args->ptr), &a.arg, sizeof(a.arg));
		if (error)
			return (error);
		return (linux_semctl(td, &a));
	}
	case LINUX_MSGSND: {
		struct linux_msgsnd_args a;

		a.msqid = args->arg1;
		a.msgp = PTRIN(args->ptr);
		a.msgsz = args->arg2;
		a.msgflg = args->arg3;
		return (linux_msgsnd(td, &a));
	}
	case LINUX_MSGRCV: {
		struct linux_msgrcv_args a;

		a.msqid = args->arg1;
		a.msgsz = args->arg2;
		a.msgflg = args->arg3;
		if ((args->what >> 16) == 0) {
			struct l_ipc_kludge tmp;
			int error;

			if (args->ptr == 0)
				return (EINVAL);
			error = copyin(PTRIN(args->ptr), &tmp, sizeof(tmp));
			if (error)
				return (error);
			a.msgp = PTRIN(tmp.msgp);
			a.msgtyp = tmp.msgtyp;
		} else {
			a.msgp = PTRIN(args->ptr);
			a.msgtyp = args->arg5;
		}
		return (linux_msgrcv(td, &a));
	}
	case LINUX_MSGGET: {
		struct linux_msgget_args a;

		a.key = args->arg1;
		a.msgflg = args->arg2;
		return (linux_msgget(td, &a));
	}
	case LINUX_MSGCTL: {
		struct linux_msgctl_args a;

		a.msqid = args->arg1;
		a.cmd = args->arg2;
		a.buf = PTRIN(args->ptr);
		return (linux_msgctl(td, &a));
	}
	case LINUX_SHMAT: {
		struct linux_shmat_args a;
		l_uintptr_t addr;
		int error;

		a.shmid = args->arg1;
		a.shmaddr = PTRIN(args->ptr);
		a.shmflg = args->arg2;
		error = linux_shmat(td, &a);
		if (error != 0)
			return (error);
		addr = td->td_retval[0];
		error = copyout(&addr, PTRIN(args->arg3), sizeof(addr));
		td->td_retval[0] = 0;
		return (error);
	}
	case LINUX_SHMDT: {
		struct linux_shmdt_args a;

		a.shmaddr = PTRIN(args->ptr);
		return (linux_shmdt(td, &a));
	}
	case LINUX_SHMGET: {
		struct linux_shmget_args a;

		a.key = args->arg1;
		a.size = args->arg2;
		a.shmflg = args->arg3;
		return (linux_shmget(td, &a));
	}
	case LINUX_SHMCTL: {
		struct linux_shmctl_args a;

		a.shmid = args->arg1;
		a.cmd = args->arg2;
		a.buf = PTRIN(args->ptr);
		return (linux_shmctl(td, &a));
	}
	default:
		break;
	}

	return (EINVAL);
}