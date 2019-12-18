#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_29__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ vm_prot_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  TYPE_3__* vm_map_t ;
typedef  TYPE_4__* vm_map_entry_t ;
typedef  scalar_t__ vm_inherit_t ;
typedef  int vm_eflags_t ;
struct ucred {int dummy; } ;
struct TYPE_34__ {TYPE_2__* vm_object; } ;
struct TYPE_38__ {scalar_t__ start; int eflags; scalar_t__ end; scalar_t__ offset; scalar_t__ inheritance; scalar_t__ protection; scalar_t__ max_protection; scalar_t__ wired_count; struct ucred* cred; scalar_t__ next_read; int /*<<< orphan*/  read_ahead; int /*<<< orphan*/ * wiring_thread; TYPE_1__ object; } ;
struct TYPE_37__ {int /*<<< orphan*/  size; } ;
struct TYPE_36__ {int ref_count; scalar_t__ shadow_count; struct ucred* cred; } ;
struct TYPE_35__ {struct ucred* td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_CHARGED (TYPE_4__*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_INVALID_ADDRESS ; 
 int KERN_INVALID_ARGUMENT ; 
 int KERN_NO_SPACE ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 int MAP_ACC_CHARGED ; 
 int MAP_ACC_NO_CHARGE ; 
 int MAP_COPY_ON_WRITE ; 
 int MAP_CREATE_GUARD ; 
 int MAP_CREATE_STACK_GAP_DN ; 
 int MAP_CREATE_STACK_GAP_UP ; 
 int MAP_DISABLE_COREDUMP ; 
 int MAP_DISABLE_SYNCER ; 
 int MAP_ENTRY_COW ; 
 int MAP_ENTRY_GROWS_DOWN ; 
 int MAP_ENTRY_GROWS_UP ; 
 int MAP_ENTRY_GUARD ; 
 int MAP_ENTRY_NEEDS_COPY ; 
 int MAP_ENTRY_NOCOREDUMP ; 
 int MAP_ENTRY_NOFAULT ; 
 int MAP_ENTRY_NOSYNC ; 
 int MAP_ENTRY_STACK_GAP_DN ; 
 int MAP_ENTRY_STACK_GAP_UP ; 
 int MAP_ENTRY_USER_WIRED ; 
 int MAP_ENTRY_VN_EXEC ; 
 int MAP_ENTRY_WRITECNT ; 
 int MAP_INHERIT_SHARE ; 
 int MAP_NOFAULT ; 
 int MAP_PREFAULT ; 
 int MAP_PREFAULT_PARTIAL ; 
 int MAP_STACK_GROWS_DOWN ; 
 int MAP_STACK_GROWS_UP ; 
 int MAP_VN_EXEC ; 
 int MAP_WRITECOUNT ; 
 int /*<<< orphan*/  OBJ_ONEMAPPING ; 
 int /*<<< orphan*/  OFF_TO_IDX (scalar_t__) ; 
 int /*<<< orphan*/  VM_FAULT_READ_AHEAD_INIT ; 
 scalar_t__ VM_INHERIT_DEFAULT ; 
 scalar_t__ VM_INHERIT_SHARE ; 
 int /*<<< orphan*/  VM_MAP_ASSERT_LOCKED (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 scalar_t__ VM_PROT_NONE ; 
 scalar_t__ VM_PROT_WRITE ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 TYPE_29__* curthread ; 
 TYPE_3__* kernel_map ; 
 TYPE_2__* kernel_object ; 
 scalar_t__ kernel_vm_end ; 
 int /*<<< orphan*/  pmap_growkernel (scalar_t__) ; 
 int /*<<< orphan*/  swap_reserve (scalar_t__) ; 
 TYPE_4__* vm_map_entry_create (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_entry_link (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  vm_map_entry_resize (TYPE_3__*,TYPE_4__*,scalar_t__) ; 
 TYPE_4__* vm_map_entry_succ (TYPE_4__*) ; 
 scalar_t__ vm_map_lookup_entry (TYPE_3__*,scalar_t__,TYPE_4__**) ; 
 scalar_t__ vm_map_max (TYPE_3__*) ; 
 scalar_t__ vm_map_min (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_pmap_enter (TYPE_3__*,scalar_t__,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  vm_map_try_merge_entries (TYPE_3__*,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  vm_object_clear_flag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_object_coalesce (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_object_reference (TYPE_2__*) ; 

int
vm_map_insert(vm_map_t map, vm_object_t object, vm_ooffset_t offset,
    vm_offset_t start, vm_offset_t end, vm_prot_t prot, vm_prot_t max, int cow)
{
	vm_map_entry_t new_entry, prev_entry;
	struct ucred *cred;
	vm_eflags_t protoeflags;
	vm_inherit_t inheritance;

	VM_MAP_ASSERT_LOCKED(map);
	KASSERT(object != kernel_object ||
	    (cow & MAP_COPY_ON_WRITE) == 0,
	    ("vm_map_insert: kernel object and COW"));
	KASSERT(object == NULL || (cow & MAP_NOFAULT) == 0,
	    ("vm_map_insert: paradoxical MAP_NOFAULT request"));
	KASSERT((prot & ~max) == 0,
	    ("prot %#x is not subset of max_prot %#x", prot, max));

	/*
	 * Check that the start and end points are not bogus.
	 */
	if (start < vm_map_min(map) || end > vm_map_max(map) ||
	    start >= end)
		return (KERN_INVALID_ADDRESS);

	/*
	 * Find the entry prior to the proposed starting address; if it's part
	 * of an existing entry, this range is bogus.
	 */
	if (vm_map_lookup_entry(map, start, &prev_entry))
		return (KERN_NO_SPACE);

	/*
	 * Assert that the next entry doesn't overlap the end point.
	 */
	if (vm_map_entry_succ(prev_entry)->start < end)
		return (KERN_NO_SPACE);

	if ((cow & MAP_CREATE_GUARD) != 0 && (object != NULL ||
	    max != VM_PROT_NONE))
		return (KERN_INVALID_ARGUMENT);

	protoeflags = 0;
	if (cow & MAP_COPY_ON_WRITE)
		protoeflags |= MAP_ENTRY_COW | MAP_ENTRY_NEEDS_COPY;
	if (cow & MAP_NOFAULT)
		protoeflags |= MAP_ENTRY_NOFAULT;
	if (cow & MAP_DISABLE_SYNCER)
		protoeflags |= MAP_ENTRY_NOSYNC;
	if (cow & MAP_DISABLE_COREDUMP)
		protoeflags |= MAP_ENTRY_NOCOREDUMP;
	if (cow & MAP_STACK_GROWS_DOWN)
		protoeflags |= MAP_ENTRY_GROWS_DOWN;
	if (cow & MAP_STACK_GROWS_UP)
		protoeflags |= MAP_ENTRY_GROWS_UP;
	if (cow & MAP_WRITECOUNT)
		protoeflags |= MAP_ENTRY_WRITECNT;
	if (cow & MAP_VN_EXEC)
		protoeflags |= MAP_ENTRY_VN_EXEC;
	if ((cow & MAP_CREATE_GUARD) != 0)
		protoeflags |= MAP_ENTRY_GUARD;
	if ((cow & MAP_CREATE_STACK_GAP_DN) != 0)
		protoeflags |= MAP_ENTRY_STACK_GAP_DN;
	if ((cow & MAP_CREATE_STACK_GAP_UP) != 0)
		protoeflags |= MAP_ENTRY_STACK_GAP_UP;
	if (cow & MAP_INHERIT_SHARE)
		inheritance = VM_INHERIT_SHARE;
	else
		inheritance = VM_INHERIT_DEFAULT;

	cred = NULL;
	if ((cow & (MAP_ACC_NO_CHARGE | MAP_NOFAULT | MAP_CREATE_GUARD)) != 0)
		goto charged;
	if ((cow & MAP_ACC_CHARGED) || ((prot & VM_PROT_WRITE) &&
	    ((protoeflags & MAP_ENTRY_NEEDS_COPY) || object == NULL))) {
		if (!(cow & MAP_ACC_CHARGED) && !swap_reserve(end - start))
			return (KERN_RESOURCE_SHORTAGE);
		KASSERT(object == NULL ||
		    (protoeflags & MAP_ENTRY_NEEDS_COPY) != 0 ||
		    object->cred == NULL,
		    ("overcommit: vm_map_insert o %p", object));
		cred = curthread->td_ucred;
	}

charged:
	/* Expand the kernel pmap, if necessary. */
	if (map == kernel_map && end > kernel_vm_end)
		pmap_growkernel(end);
	if (object != NULL) {
		/*
		 * OBJ_ONEMAPPING must be cleared unless this mapping
		 * is trivially proven to be the only mapping for any
		 * of the object's pages.  (Object granularity
		 * reference counting is insufficient to recognize
		 * aliases with precision.)
		 */
		VM_OBJECT_WLOCK(object);
		if (object->ref_count > 1 || object->shadow_count != 0)
			vm_object_clear_flag(object, OBJ_ONEMAPPING);
		VM_OBJECT_WUNLOCK(object);
	} else if ((prev_entry->eflags & ~MAP_ENTRY_USER_WIRED) ==
	    protoeflags &&
	    (cow & (MAP_STACK_GROWS_DOWN | MAP_STACK_GROWS_UP |
	    MAP_VN_EXEC)) == 0 &&
	    prev_entry->end == start && (prev_entry->cred == cred ||
	    (prev_entry->object.vm_object != NULL &&
	    prev_entry->object.vm_object->cred == cred)) &&
	    vm_object_coalesce(prev_entry->object.vm_object,
	    prev_entry->offset,
	    (vm_size_t)(prev_entry->end - prev_entry->start),
	    (vm_size_t)(end - prev_entry->end), cred != NULL &&
	    (protoeflags & MAP_ENTRY_NEEDS_COPY) == 0)) {
		/*
		 * We were able to extend the object.  Determine if we
		 * can extend the previous map entry to include the
		 * new range as well.
		 */
		if (prev_entry->inheritance == inheritance &&
		    prev_entry->protection == prot &&
		    prev_entry->max_protection == max &&
		    prev_entry->wired_count == 0) {
			KASSERT((prev_entry->eflags & MAP_ENTRY_USER_WIRED) ==
			    0, ("prev_entry %p has incoherent wiring",
			    prev_entry));
			if ((prev_entry->eflags & MAP_ENTRY_GUARD) == 0)
				map->size += end - prev_entry->end;
			vm_map_entry_resize(map, prev_entry,
			    end - prev_entry->end);
			vm_map_try_merge_entries(map, prev_entry,
			    vm_map_entry_succ(prev_entry));
			return (KERN_SUCCESS);
		}

		/*
		 * If we can extend the object but cannot extend the
		 * map entry, we have to create a new map entry.  We
		 * must bump the ref count on the extended object to
		 * account for it.  object may be NULL.
		 */
		object = prev_entry->object.vm_object;
		offset = prev_entry->offset +
		    (prev_entry->end - prev_entry->start);
		vm_object_reference(object);
		if (cred != NULL && object != NULL && object->cred != NULL &&
		    !(prev_entry->eflags & MAP_ENTRY_NEEDS_COPY)) {
			/* Object already accounts for this uid. */
			cred = NULL;
		}
	}
	if (cred != NULL)
		crhold(cred);

	/*
	 * Create a new entry
	 */
	new_entry = vm_map_entry_create(map);
	new_entry->start = start;
	new_entry->end = end;
	new_entry->cred = NULL;

	new_entry->eflags = protoeflags;
	new_entry->object.vm_object = object;
	new_entry->offset = offset;

	new_entry->inheritance = inheritance;
	new_entry->protection = prot;
	new_entry->max_protection = max;
	new_entry->wired_count = 0;
	new_entry->wiring_thread = NULL;
	new_entry->read_ahead = VM_FAULT_READ_AHEAD_INIT;
	new_entry->next_read = start;

	KASSERT(cred == NULL || !ENTRY_CHARGED(new_entry),
	    ("overcommit: vm_map_insert leaks vm_map %p", new_entry));
	new_entry->cred = cred;

	/*
	 * Insert the new entry into the list
	 */
	vm_map_entry_link(map, new_entry);
	if ((new_entry->eflags & MAP_ENTRY_GUARD) == 0)
		map->size += new_entry->end - new_entry->start;

	/*
	 * Try to coalesce the new entry with both the previous and next
	 * entries in the list.  Previously, we only attempted to coalesce
	 * with the previous entry when object is NULL.  Here, we handle the
	 * other cases, which are less common.
	 */
	vm_map_try_merge_entries(map, prev_entry, new_entry);
	vm_map_try_merge_entries(map, new_entry, vm_map_entry_succ(new_entry));

	if ((cow & (MAP_PREFAULT | MAP_PREFAULT_PARTIAL)) != 0) {
		vm_map_pmap_enter(map, start, prot, object, OFF_TO_IDX(offset),
		    end - start, cow & MAP_PREFAULT_PARTIAL);
	}

	return (KERN_SUCCESS);
}