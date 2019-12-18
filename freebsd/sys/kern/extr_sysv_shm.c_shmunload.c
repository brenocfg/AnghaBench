#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mode; } ;
struct TYPE_7__ {TYPE_1__ shm_perm; } ;
struct TYPE_8__ {int /*<<< orphan*/  object; TYPE_2__ u; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  M_SHM ; 
 scalar_t__ SHMSEG_FREE ; 
 int /*<<< orphan*/  free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_sysvshm_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  osd_jail_deregister (scalar_t__) ; 
 int /*<<< orphan*/  shm32_syscalls ; 
 scalar_t__ shm_nused ; 
 scalar_t__ shm_prison_slot ; 
 int /*<<< orphan*/  shm_syscalls ; 
 int shmalloced ; 
 int /*<<< orphan*/ * shmexit_hook ; 
 int /*<<< orphan*/ * shmfork_hook ; 
 TYPE_3__* shmsegs ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscall32_helper_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscall_helper_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysvshmsx ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
shmunload(void)
{
	int i;

	if (shm_nused > 0)
		return (EBUSY);

#ifdef COMPAT_FREEBSD32
	syscall32_helper_unregister(shm32_syscalls);
#endif
	syscall_helper_unregister(shm_syscalls);
	if (shm_prison_slot != 0)
		osd_jail_deregister(shm_prison_slot);

	for (i = 0; i < shmalloced; i++) {
#ifdef MAC
		mac_sysvshm_destroy(&shmsegs[i]);
#endif
		/*
		 * Objects might be still mapped into the processes
		 * address spaces.  Actual free would happen on the
		 * last mapping destruction.
		 */
		if (shmsegs[i].u.shm_perm.mode != SHMSEG_FREE)
			vm_object_deallocate(shmsegs[i].object);
	}
	free(shmsegs, M_SHM);
#ifndef SYSVSHM
	shmexit_hook = NULL;
	shmfork_hook = NULL;
#endif
	sx_destroy(&sysvshmsx);
	return (0);
}