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
struct msgrcv_args {scalar_t__ msgp; int /*<<< orphan*/  msgflg; int /*<<< orphan*/  msgtyp; int /*<<< orphan*/  msgsz; int /*<<< orphan*/  msqid; } ;
typedef  int /*<<< orphan*/  mtype ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int copyout (long*,scalar_t__,int) ; 
 int kern_msgrcv (struct thread*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*) ; 

int
sys_msgrcv(struct thread *td, struct msgrcv_args *uap)
{
	int error;
	long mtype;

	DPRINTF(("call to msgrcv(%d, %p, %zu, %ld, %d)\n", uap->msqid,
	    uap->msgp, uap->msgsz, uap->msgtyp, uap->msgflg));

	if ((error = kern_msgrcv(td, uap->msqid,
	    (char *)uap->msgp + sizeof(mtype), uap->msgsz,
	    uap->msgtyp, uap->msgflg, &mtype)) != 0)
		return (error);
	if ((error = copyout(&mtype, uap->msgp, sizeof(mtype))) != 0)
		DPRINTF(("error %d copying the message type\n", error));
	return (error);
}