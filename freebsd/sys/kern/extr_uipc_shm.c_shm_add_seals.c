#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_ooffset_t ;
struct shmfd {int shm_seals; int /*<<< orphan*/  shm_mtx; int /*<<< orphan*/  shm_rl; TYPE_3__* shm_object; } ;
struct file {struct shmfd* f_data; } ;
struct TYPE_5__ {scalar_t__ writemappings; } ;
struct TYPE_6__ {TYPE_1__ swp; } ;
struct TYPE_7__ {TYPE_2__ un_pager; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 int F_SEAL_SEAL ; 
 int F_SEAL_WRITE ; 
 int /*<<< orphan*/  OFF_MAX ; 
 int /*<<< orphan*/  VM_OBJECT_RLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  rangelock_unlock (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 void* rangelock_wlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
shm_add_seals(struct file *fp, int seals)
{
	struct shmfd *shmfd;
	void *rl_cookie;
	vm_ooffset_t writemappings;
	int error, nseals;

	error = 0;
	shmfd = fp->f_data;
	rl_cookie = rangelock_wlock(&shmfd->shm_rl, 0, OFF_MAX,
	    &shmfd->shm_mtx);

	/* Even already-set seals should result in EPERM. */
	if ((shmfd->shm_seals & F_SEAL_SEAL) != 0) {
		error = EPERM;
		goto out;
	}
	nseals = seals & ~shmfd->shm_seals;
	if ((nseals & F_SEAL_WRITE) != 0) {
		/*
		 * The rangelock above prevents writable mappings from being
		 * added after we've started applying seals.  The RLOCK here
		 * is to avoid torn reads on ILP32 arches as unmapping/reducing
		 * writemappings will be done without a rangelock.
		 */
		VM_OBJECT_RLOCK(shmfd->shm_object);
		writemappings = shmfd->shm_object->un_pager.swp.writemappings;
		VM_OBJECT_RUNLOCK(shmfd->shm_object);
		/* kmappings are also writable */
		if (writemappings > 0) {
			error = EBUSY;
			goto out;
		}
	}
	shmfd->shm_seals |= nseals;
out:
	rangelock_unlock(&shmfd->shm_rl, rl_cookie, &shmfd->shm_mtx);
	return (error);
}