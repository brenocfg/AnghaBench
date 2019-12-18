#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ rlim_t ;
struct TYPE_6__ {int flags; scalar_t__ size; } ;

/* Variables and functions */
 int KERN_NO_SPACE ; 
 int MAP_WIREFUTURE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  RLIMIT_VMEM ; 
 int /*<<< orphan*/  curthread ; 
 scalar_t__ lim_cur (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sgrowsiz ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_1__*) ; 
 int vm_map_stack_locked (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_1__*) ; 

int
vm_map_stack(vm_map_t map, vm_offset_t addrbos, vm_size_t max_ssize,
    vm_prot_t prot, vm_prot_t max, int cow)
{
	vm_size_t growsize, init_ssize;
	rlim_t vmemlim;
	int rv;

	MPASS((map->flags & MAP_WIREFUTURE) == 0);
	growsize = sgrowsiz;
	init_ssize = (max_ssize < growsize) ? max_ssize : growsize;
	vm_map_lock(map);
	vmemlim = lim_cur(curthread, RLIMIT_VMEM);
	/* If we would blow our VMEM resource limit, no go */
	if (map->size + init_ssize > vmemlim) {
		rv = KERN_NO_SPACE;
		goto out;
	}
	rv = vm_map_stack_locked(map, addrbos, max_ssize, growsize, prot,
	    max, cow);
out:
	vm_map_unlock(map);
	return (rv);
}