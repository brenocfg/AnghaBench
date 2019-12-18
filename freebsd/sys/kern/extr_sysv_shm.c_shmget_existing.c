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
struct thread {int /*<<< orphan*/ * td_retval; int /*<<< orphan*/  td_ucred; } ;
struct TYPE_2__ {scalar_t__ shm_segsz; int /*<<< orphan*/  shm_perm; } ;
struct shmid_kernel {TYPE_1__ u; } ;
struct shmget_args {int shmflg; scalar_t__ size; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int IPC_CREAT ; 
 int IPC_EXCL ; 
 int /*<<< orphan*/  IXSEQ_TO_IPCID (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SYSVSHM_ASSERT_LOCKED () ; 
 int mac_sysvshm_check_shmget (int /*<<< orphan*/ ,struct shmid_kernel*,int) ; 
 int shmalloced ; 
 struct shmid_kernel* shmsegs ; 

__attribute__((used)) static int
shmget_existing(struct thread *td, struct shmget_args *uap, int mode,
    int segnum)
{
	struct shmid_kernel *shmseg;
#ifdef MAC
	int error;
#endif

	SYSVSHM_ASSERT_LOCKED();
	KASSERT(segnum >= 0 && segnum < shmalloced,
	    ("segnum %d shmalloced %d", segnum, shmalloced));
	shmseg = &shmsegs[segnum];
	if ((uap->shmflg & (IPC_CREAT | IPC_EXCL)) == (IPC_CREAT | IPC_EXCL))
		return (EEXIST);
#ifdef MAC
	error = mac_sysvshm_check_shmget(td->td_ucred, shmseg, uap->shmflg);
	if (error != 0)
		return (error);
#endif
	if (uap->size != 0 && uap->size > shmseg->u.shm_segsz)
		return (EINVAL);
	td->td_retval[0] = IXSEQ_TO_IPCID(segnum, shmseg->u.shm_perm);
	return (0);
}