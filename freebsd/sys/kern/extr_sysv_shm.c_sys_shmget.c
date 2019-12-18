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
struct thread {TYPE_1__* td_ucred; } ;
struct shmget_args {int shmflg; scalar_t__ key; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_prison; } ;

/* Variables and functions */
 int ACCESSPERMS ; 
 int ENOENT ; 
 int ENOSYS ; 
 int IPC_CREAT ; 
 scalar_t__ IPC_PRIVATE ; 
 int /*<<< orphan*/  SYSVSHM_LOCK () ; 
 int /*<<< orphan*/  SYSVSHM_UNLOCK () ; 
 int /*<<< orphan*/ * shm_find_prison (TYPE_1__*) ; 
 int shm_find_segment_by_key (int /*<<< orphan*/ ,scalar_t__) ; 
 int shmget_allocate_segment (struct thread*,struct shmget_args*,int) ; 
 int shmget_existing (struct thread*,struct shmget_args*,int,int) ; 

int
sys_shmget(struct thread *td, struct shmget_args *uap)
{
	int segnum, mode;
	int error;

	if (shm_find_prison(td->td_ucred) == NULL)
		return (ENOSYS);
	mode = uap->shmflg & ACCESSPERMS;
	SYSVSHM_LOCK();
	if (uap->key == IPC_PRIVATE) {
		error = shmget_allocate_segment(td, uap, mode);
	} else {
		segnum = shm_find_segment_by_key(td->td_ucred->cr_prison,
		    uap->key);
		if (segnum >= 0)
			error = shmget_existing(td, uap, mode, segnum);
		else if ((uap->shmflg & IPC_CREAT) == 0)
			error = ENOENT;
		else
			error = shmget_allocate_segment(td, uap, mode);
	}
	SYSVSHM_UNLOCK();
	return (error);
}