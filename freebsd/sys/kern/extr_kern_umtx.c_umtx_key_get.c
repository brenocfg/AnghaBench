#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  TYPE_6__* vm_map_entry_t ;
struct TYPE_12__ {uintptr_t addr; TYPE_2__* vs; } ;
struct TYPE_9__ {int /*<<< orphan*/  object; scalar_t__ offset; } ;
struct TYPE_13__ {TYPE_4__ private; TYPE_1__ shared; } ;
struct umtx_key {int type; int shared; TYPE_5__ info; } ;
struct thread {TYPE_3__* td_proc; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_14__ {scalar_t__ inheritance; scalar_t__ offset; scalar_t__ start; } ;
struct TYPE_11__ {TYPE_2__* p_vmspace; } ;
struct TYPE_10__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int AUTO_SHARE ; 
 int EFAULT ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int PROCESS_SHARE ; 
 int THREAD_SHARE ; 
 scalar_t__ VM_INHERIT_SHARE ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  umtxq_hash (struct umtx_key*) ; 
 scalar_t__ vm_map_lookup (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ,TYPE_6__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_lookup_done (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  vm_object_reference (int /*<<< orphan*/ ) ; 

int
umtx_key_get(const void *addr, int type, int share, struct umtx_key *key)
{
	struct thread *td = curthread;
	vm_map_t map;
	vm_map_entry_t entry;
	vm_pindex_t pindex;
	vm_prot_t prot;
	boolean_t wired;

	key->type = type;
	if (share == THREAD_SHARE) {
		key->shared = 0;
		key->info.private.vs = td->td_proc->p_vmspace;
		key->info.private.addr = (uintptr_t)addr;
	} else {
		MPASS(share == PROCESS_SHARE || share == AUTO_SHARE);
		map = &td->td_proc->p_vmspace->vm_map;
		if (vm_map_lookup(&map, (vm_offset_t)addr, VM_PROT_WRITE,
		    &entry, &key->info.shared.object, &pindex, &prot,
		    &wired) != KERN_SUCCESS) {
			return (EFAULT);
		}

		if ((share == PROCESS_SHARE) ||
		    (share == AUTO_SHARE &&
		     VM_INHERIT_SHARE == entry->inheritance)) {
			key->shared = 1;
			key->info.shared.offset = (vm_offset_t)addr -
			    entry->start + entry->offset;
			vm_object_reference(key->info.shared.object);
		} else {
			key->shared = 0;
			key->info.private.vs = td->td_proc->p_vmspace;
			key->info.private.addr = (uintptr_t)addr;
		}
		vm_map_lookup_done(map, entry);
	}

	umtxq_hash(key);
	return (0);
}