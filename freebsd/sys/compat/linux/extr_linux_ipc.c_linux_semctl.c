#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union semun {void* array; struct semid_ds* buf; int /*<<< orphan*/  val; } ;
struct thread {int /*<<< orphan*/ * td_retval; } ;
struct semid_ds {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  array; int /*<<< orphan*/  buf; int /*<<< orphan*/  val; } ;
struct linux_semctl_args {int cmd; int /*<<< orphan*/  semnum; int /*<<< orphan*/  semid; TYPE_1__ arg; } ;
struct l_seminfo {int /*<<< orphan*/  semmns; int /*<<< orphan*/  semmap; int /*<<< orphan*/  semmni; } ;
struct l_semid64_ds {int /*<<< orphan*/  semmns; int /*<<< orphan*/  semmap; int /*<<< orphan*/  semmni; } ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  linux_seminfo ;
typedef  int /*<<< orphan*/  linux_semid64 ;
struct TYPE_5__ {int /*<<< orphan*/  semmni; } ;

/* Variables and functions */
 int EINVAL ; 
 int GETALL ; 
 int GETNCNT ; 
 int GETPID ; 
 int GETVAL ; 
 int GETZCNT ; 
 int IPC_RMID ; 
 int IPC_SET ; 
 int IPC_STAT ; 
#define  LINUX_GETALL 140 
#define  LINUX_GETNCNT 139 
#define  LINUX_GETPID 138 
#define  LINUX_GETVAL 137 
#define  LINUX_GETZCNT 136 
 int LINUX_IPC_64 ; 
#define  LINUX_IPC_INFO 135 
#define  LINUX_IPC_RMID 134 
#define  LINUX_IPC_SET 133 
#define  LINUX_IPC_STAT 132 
#define  LINUX_SEM_INFO 131 
#define  LINUX_SEM_STAT 130 
#define  LINUX_SETALL 129 
#define  LINUX_SETVAL 128 
 void* PTRIN (int /*<<< orphan*/ ) ; 
 int SEM_STAT ; 
 int SETALL ; 
 int SETVAL ; 
 int /*<<< orphan*/  bcopy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsd_to_linux_semid_ds (struct semid_ds*,struct l_seminfo*) ; 
 int copyout (struct l_seminfo*,void*,int) ; 
 int kern_semctl (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,union semun*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_msg (struct thread*,char*,int) ; 
 int linux_semid_pullup (int,struct l_seminfo*,void*) ; 
 int linux_semid_pushdown (int,struct l_seminfo*,void*) ; 
 int /*<<< orphan*/  linux_to_bsd_semid_ds (struct l_seminfo*,struct semid_ds*) ; 
 int /*<<< orphan*/  memset (struct l_seminfo*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ seminfo ; 

int
linux_semctl(struct thread *td, struct linux_semctl_args *args)
{
	struct l_semid64_ds linux_semid64;
	struct l_seminfo linux_seminfo;
	struct semid_ds semid;
	union semun semun;
	register_t rval;
	int cmd, error;

	memset(&linux_seminfo, 0, sizeof(linux_seminfo));
	memset(&linux_semid64, 0, sizeof(linux_semid64));

	switch (args->cmd & ~LINUX_IPC_64) {
	case LINUX_IPC_RMID:
		cmd = IPC_RMID;
		break;
	case LINUX_GETNCNT:
		cmd = GETNCNT;
		break;
	case LINUX_GETPID:
		cmd = GETPID;
		break;
	case LINUX_GETVAL:
		cmd = GETVAL;
		break;
	case LINUX_GETZCNT:
		cmd = GETZCNT;
		break;
	case LINUX_SETVAL:
		cmd = SETVAL;
		semun.val = args->arg.val;
		break;
	case LINUX_IPC_SET:
		cmd = IPC_SET;
		error = linux_semid_pullup(args->cmd & LINUX_IPC_64,
		    &linux_semid64, PTRIN(args->arg.buf));
		if (error != 0)
			return (error);
		linux_to_bsd_semid_ds(&linux_semid64, &semid);
		semun.buf = &semid;
		return (kern_semctl(td, args->semid, args->semnum, cmd, &semun,
		    td->td_retval));
	case LINUX_IPC_STAT:
		cmd = IPC_STAT;
		semun.buf = &semid;
		error = kern_semctl(td, args->semid, args->semnum, cmd, &semun,
		    &rval);
		if (error != 0)
			return (error);
		bsd_to_linux_semid_ds(&semid, &linux_semid64);
		return (linux_semid_pushdown(args->cmd & LINUX_IPC_64,
		    &linux_semid64, PTRIN(args->arg.buf)));
	case LINUX_SEM_STAT:
		cmd = SEM_STAT;
		semun.buf = &semid;
		error = kern_semctl(td, args->semid, args->semnum, cmd, &semun,
		    &rval);
		if (error != 0)
			return (error);
		bsd_to_linux_semid_ds(&semid, &linux_semid64);
		error = linux_semid_pushdown(args->cmd & LINUX_IPC_64,
		    &linux_semid64, PTRIN(args->arg.buf));
		if (error == 0)
			td->td_retval[0] = rval;
		return (error);
	case LINUX_IPC_INFO:
	case LINUX_SEM_INFO:
		bcopy(&seminfo, &linux_seminfo.semmni, sizeof(linux_seminfo) -
		    sizeof(linux_seminfo.semmap) );
		/*
		 * Linux does not use the semmap field but populates it with
		 * the defined value from SEMMAP, which really is redefined to
		 * SEMMNS, which they define as SEMMNI * SEMMSL.  Try to
		 * simulate this returning our dynamic semmns value.
		 */
		linux_seminfo.semmap = linux_seminfo.semmns;
/* XXX BSD equivalent?
#define used_semids 10
#define used_sems 10
		linux_seminfo.semusz = used_semids;
		linux_seminfo.semaem = used_sems;
*/
		error = copyout(&linux_seminfo,
		    PTRIN(args->arg.buf), sizeof(linux_seminfo));
		if (error != 0)
			return (error);
		/*
		 * TODO: Linux return the last assigned id, not the semmni.
		 */
		td->td_retval[0] = seminfo.semmni;
		return (0);
	case LINUX_GETALL:
		cmd = GETALL;
		semun.array = PTRIN(args->arg.array);
		break;
	case LINUX_SETALL:
		cmd = SETALL;
		semun.array = PTRIN(args->arg.array);
		break;
	default:
		linux_msg(td, "ipc type %d is not implemented",
		  args->cmd & ~LINUX_IPC_64);
		return (EINVAL);
	}
	return (kern_semctl(td, args->semid, args->semnum, cmd, &semun,
	    td->td_retval));
}