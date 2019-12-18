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
struct msqid_ds {int dummy; } ;
struct msgctl_args {int msqid; int cmd; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  msqbuf ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int IPC_SET ; 
 int IPC_STAT ; 
 int copyin (int /*<<< orphan*/ ,struct msqid_ds*,int) ; 
 int copyout (struct msqid_ds*,int /*<<< orphan*/ ,int) ; 
 int kern_msgctl (struct thread*,int,int,struct msqid_ds*) ; 

int
sys_msgctl(struct thread *td, struct msgctl_args *uap)
{
	int msqid = uap->msqid;
	int cmd = uap->cmd;
	struct msqid_ds msqbuf;
	int error;

	DPRINTF(("call to msgctl(%d, %d, %p)\n", msqid, cmd, uap->buf));
	if (cmd == IPC_SET &&
	    (error = copyin(uap->buf, &msqbuf, sizeof(msqbuf))) != 0)
		return (error);
	error = kern_msgctl(td, msqid, cmd, &msqbuf);
	if (cmd == IPC_STAT && error == 0)
		error = copyout(&msqbuf, uap->buf, sizeof(struct msqid_ds));
	return (error);
}