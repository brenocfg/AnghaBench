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
struct thread {int dummy; } ;
struct msgsnd_args {int /*<<< orphan*/  msgflg; int /*<<< orphan*/  msgsz; scalar_t__ msgp; int /*<<< orphan*/  msqid; } ;
typedef  int /*<<< orphan*/  mtype ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int copyin (scalar_t__,long*,int) ; 
 int kern_msgsnd (struct thread*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

int
sys_msgsnd(struct thread *td, struct msgsnd_args *uap)
{
	int error;
	long mtype;

	DPRINTF(("call to msgsnd(%d, %p, %zu, %d)\n", uap->msqid, uap->msgp,
	    uap->msgsz, uap->msgflg));

	if ((error = copyin(uap->msgp, &mtype, sizeof(mtype))) != 0) {
		DPRINTF(("error %d copying the message type\n", error));
		return (error);
	}
	return (kern_msgsnd(td, uap->msqid,
	    (const char *)uap->msgp + sizeof(mtype),
	    uap->msgsz, uap->msgflg, mtype));
}