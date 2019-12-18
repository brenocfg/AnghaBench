#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_4__ {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int ENOMEM ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 int PMAP_ENTER_NOSLEEP ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_UNLOCKED (int /*<<< orphan*/ ) ; 
 int moea_enter_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

int
moea_enter(mmu_t mmu, pmap_t pmap, vm_offset_t va, vm_page_t m, vm_prot_t prot,
    u_int flags, int8_t psind)
{
	int error;

	for (;;) {
		rw_wlock(&pvh_global_lock);
		PMAP_LOCK(pmap);
		error = moea_enter_locked(pmap, va, m, prot, flags, psind);
		rw_wunlock(&pvh_global_lock);
		PMAP_UNLOCK(pmap);
		if (error != ENOMEM)
			return (KERN_SUCCESS);
		if ((flags & PMAP_ENTER_NOSLEEP) != 0)
			return (KERN_RESOURCE_SHORTAGE);
		VM_OBJECT_ASSERT_UNLOCKED(m->object);
		vm_wait(NULL);
	}
}