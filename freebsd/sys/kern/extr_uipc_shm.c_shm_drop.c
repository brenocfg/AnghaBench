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
struct shmfd {int /*<<< orphan*/  shm_object; int /*<<< orphan*/  shm_mtx; int /*<<< orphan*/  shm_rl; int /*<<< orphan*/  shm_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SHMFD ; 
 int /*<<< orphan*/  free (struct shmfd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_posixshm_destroy (struct shmfd*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rangelock_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

void
shm_drop(struct shmfd *shmfd)
{

	if (refcount_release(&shmfd->shm_refs)) {
#ifdef MAC
		mac_posixshm_destroy(shmfd);
#endif
		rangelock_destroy(&shmfd->shm_rl);
		mtx_destroy(&shmfd->shm_mtx);
		vm_object_deallocate(shmfd->shm_object);
		free(shmfd, M_SHMFD);
	}
}