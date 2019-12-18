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
struct thread {int* td_retval; } ;
struct shmid_ds {int dummy; } ;
struct shmctl_args {int cmd; int /*<<< orphan*/  buf; int /*<<< orphan*/  shmid; } ;

/* Variables and functions */
 int EINVAL ; 
 int IPC_INFO ; 
 int IPC_SET ; 
#define  IPC_STAT 128 
 int SHM_INFO ; 
 int SHM_STAT ; 
 int copyin (int /*<<< orphan*/ ,struct shmid_ds*,int) ; 
 int copyout (struct shmid_ds*,int /*<<< orphan*/ ,size_t) ; 
 int kern_shmctl (struct thread*,int /*<<< orphan*/ ,int,void*,size_t*) ; 

int
sys_shmctl(struct thread *td, struct shmctl_args *uap)
{
	int error;
	struct shmid_ds buf;
	size_t bufsz;

	/*
	 * The only reason IPC_INFO, SHM_INFO, SHM_STAT exists is to support
	 * Linux binaries.  If we see the call come through the FreeBSD ABI,
	 * return an error back to the user since we do not to support this.
	 */
	if (uap->cmd == IPC_INFO || uap->cmd == SHM_INFO ||
	    uap->cmd == SHM_STAT)
		return (EINVAL);

	/* IPC_SET needs to copyin the buffer before calling kern_shmctl */
	if (uap->cmd == IPC_SET) {
		if ((error = copyin(uap->buf, &buf, sizeof(struct shmid_ds))))
			goto done;
	}

	error = kern_shmctl(td, uap->shmid, uap->cmd, (void *)&buf, &bufsz);
	if (error)
		goto done;

	/* Cases in which we need to copyout */
	switch (uap->cmd) {
	case IPC_STAT:
		error = copyout(&buf, uap->buf, bufsz);
		break;
	}

done:
	if (error) {
		/* Invalidate the return value */
		td->td_retval[0] = -1;
	}
	return (error);
}