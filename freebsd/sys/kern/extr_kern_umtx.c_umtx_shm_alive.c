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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_3__* vm_object_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_entry_t ;
struct thread {TYPE_2__* td_proc; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {TYPE_1__* p_vmspace; } ;
struct TYPE_5__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOTTY ; 
 int KERN_SUCCESS ; 
 int OBJ_UMTXDEAD ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int vm_map_lookup (int /*<<< orphan*/ **,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_lookup_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
umtx_shm_alive(struct thread *td, void *addr)
{
	vm_map_t map;
	vm_map_entry_t entry;
	vm_object_t object;
	vm_pindex_t pindex;
	vm_prot_t prot;
	int res, ret;
	boolean_t wired;

	map = &td->td_proc->p_vmspace->vm_map;
	res = vm_map_lookup(&map, (uintptr_t)addr, VM_PROT_READ, &entry,
	    &object, &pindex, &prot, &wired);
	if (res != KERN_SUCCESS)
		return (EFAULT);
	if (object == NULL)
		ret = EINVAL;
	else
		ret = (object->flags & OBJ_UMTXDEAD) != 0 ? ENOTTY : 0;
	vm_map_lookup_done(map, entry);
	return (ret);
}