#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_20__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_size_t ;
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  void* vm_offset_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  TYPE_3__* vm_map_t ;
typedef  TYPE_4__* vm_map_entry_t ;
struct ucred {int dummy; } ;
typedef  int boolean_t ;
struct TYPE_23__ {TYPE_2__* vm_object; TYPE_3__* sub_map; } ;
struct TYPE_27__ {int eflags; int protection; int max_protection; scalar_t__ wired_count; TYPE_1__ object; void* offset; void* start; struct ucred* cred; void* end; } ;
struct TYPE_26__ {int /*<<< orphan*/  system_map; } ;
struct TYPE_25__ {void* charge; struct ucred* cred; } ;
struct TYPE_24__ {struct ucred* td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_INVALID_ADDRESS ; 
 int KERN_PROTECTION_FAILURE ; 
 int KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int MAP_ENTRY_COW ; 
 int MAP_ENTRY_GUARD ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int MAP_ENTRY_NEEDS_COPY ; 
 int MAP_ENTRY_STACK_GAP_DN ; 
 int MAP_ENTRY_STACK_GAP_UP ; 
 int MAP_ENTRY_USER_WIRED ; 
 int /*<<< orphan*/  OBJT_DEFAULT ; 
 int /*<<< orphan*/  OFF_TO_IDX (void*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 int VM_PROT_COPY ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_FAULT_LOOKUP ; 
 int VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  atop (void*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 TYPE_20__* curthread ; 
 TYPE_3__* kernel_map ; 
 int /*<<< orphan*/  swap_release_by_cred (void*,struct ucred*) ; 
 int /*<<< orphan*/  swap_reserve_by_cred (void*,struct ucred*) ; 
 scalar_t__ vm_map_growstack (TYPE_3__*,void*,TYPE_4__*) ; 
 int /*<<< orphan*/  vm_map_lock_downgrade (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (TYPE_3__*) ; 
 scalar_t__ vm_map_lock_upgrade (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (TYPE_3__*,void*,TYPE_4__**) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (TYPE_3__*) ; 
 TYPE_2__* vm_object_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_shadow (TYPE_2__**,void**,void*) ; 

int
vm_map_lookup(vm_map_t *var_map,		/* IN/OUT */
	      vm_offset_t vaddr,
	      vm_prot_t fault_typea,
	      vm_map_entry_t *out_entry,	/* OUT */
	      vm_object_t *object,		/* OUT */
	      vm_pindex_t *pindex,		/* OUT */
	      vm_prot_t *out_prot,		/* OUT */
	      boolean_t *wired)			/* OUT */
{
	vm_map_entry_t entry;
	vm_map_t map = *var_map;
	vm_prot_t prot;
	vm_prot_t fault_type = fault_typea;
	vm_object_t eobject;
	vm_size_t size;
	struct ucred *cred;

RetryLookup:

	vm_map_lock_read(map);

RetryLookupLocked:
	/*
	 * Lookup the faulting address.
	 */
	if (!vm_map_lookup_entry(map, vaddr, out_entry)) {
		vm_map_unlock_read(map);
		return (KERN_INVALID_ADDRESS);
	}

	entry = *out_entry;

	/*
	 * Handle submaps.
	 */
	if (entry->eflags & MAP_ENTRY_IS_SUB_MAP) {
		vm_map_t old_map = map;

		*var_map = map = entry->object.sub_map;
		vm_map_unlock_read(old_map);
		goto RetryLookup;
	}

	/*
	 * Check whether this task is allowed to have this page.
	 */
	prot = entry->protection;
	if ((fault_typea & VM_PROT_FAULT_LOOKUP) != 0) {
		fault_typea &= ~VM_PROT_FAULT_LOOKUP;
		if (prot == VM_PROT_NONE && map != kernel_map &&
		    (entry->eflags & MAP_ENTRY_GUARD) != 0 &&
		    (entry->eflags & (MAP_ENTRY_STACK_GAP_DN |
		    MAP_ENTRY_STACK_GAP_UP)) != 0 &&
		    vm_map_growstack(map, vaddr, entry) == KERN_SUCCESS)
			goto RetryLookupLocked;
	}
	fault_type &= VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXECUTE;
	if ((fault_type & prot) != fault_type || prot == VM_PROT_NONE) {
		vm_map_unlock_read(map);
		return (KERN_PROTECTION_FAILURE);
	}
	KASSERT((prot & VM_PROT_WRITE) == 0 || (entry->eflags &
	    (MAP_ENTRY_USER_WIRED | MAP_ENTRY_NEEDS_COPY)) !=
	    (MAP_ENTRY_USER_WIRED | MAP_ENTRY_NEEDS_COPY),
	    ("entry %p flags %x", entry, entry->eflags));
	if ((fault_typea & VM_PROT_COPY) != 0 &&
	    (entry->max_protection & VM_PROT_WRITE) == 0 &&
	    (entry->eflags & MAP_ENTRY_COW) == 0) {
		vm_map_unlock_read(map);
		return (KERN_PROTECTION_FAILURE);
	}

	/*
	 * If this page is not pageable, we have to get it for all possible
	 * accesses.
	 */
	*wired = (entry->wired_count != 0);
	if (*wired)
		fault_type = entry->protection;
	size = entry->end - entry->start;
	/*
	 * If the entry was copy-on-write, we either ...
	 */
	if (entry->eflags & MAP_ENTRY_NEEDS_COPY) {
		/*
		 * If we want to write the page, we may as well handle that
		 * now since we've got the map locked.
		 *
		 * If we don't need to write the page, we just demote the
		 * permissions allowed.
		 */
		if ((fault_type & VM_PROT_WRITE) != 0 ||
		    (fault_typea & VM_PROT_COPY) != 0) {
			/*
			 * Make a new object, and place it in the object
			 * chain.  Note that no new references have appeared
			 * -- one just moved from the map to the new
			 * object.
			 */
			if (vm_map_lock_upgrade(map))
				goto RetryLookup;

			if (entry->cred == NULL) {
				/*
				 * The debugger owner is charged for
				 * the memory.
				 */
				cred = curthread->td_ucred;
				crhold(cred);
				if (!swap_reserve_by_cred(size, cred)) {
					crfree(cred);
					vm_map_unlock(map);
					return (KERN_RESOURCE_SHORTAGE);
				}
				entry->cred = cred;
			}
			vm_object_shadow(&entry->object.vm_object,
			    &entry->offset, size);
			entry->eflags &= ~MAP_ENTRY_NEEDS_COPY;
			eobject = entry->object.vm_object;
			if (eobject->cred != NULL) {
				/*
				 * The object was not shadowed.
				 */
				swap_release_by_cred(size, entry->cred);
				crfree(entry->cred);
				entry->cred = NULL;
			} else if (entry->cred != NULL) {
				VM_OBJECT_WLOCK(eobject);
				eobject->cred = entry->cred;
				eobject->charge = size;
				VM_OBJECT_WUNLOCK(eobject);
				entry->cred = NULL;
			}

			vm_map_lock_downgrade(map);
		} else {
			/*
			 * We're attempting to read a copy-on-write page --
			 * don't allow writes.
			 */
			prot &= ~VM_PROT_WRITE;
		}
	}

	/*
	 * Create an object if necessary.
	 */
	if (entry->object.vm_object == NULL &&
	    !map->system_map) {
		if (vm_map_lock_upgrade(map))
			goto RetryLookup;
		entry->object.vm_object = vm_object_allocate(OBJT_DEFAULT,
		    atop(size));
		entry->offset = 0;
		if (entry->cred != NULL) {
			VM_OBJECT_WLOCK(entry->object.vm_object);
			entry->object.vm_object->cred = entry->cred;
			entry->object.vm_object->charge = size;
			VM_OBJECT_WUNLOCK(entry->object.vm_object);
			entry->cred = NULL;
		}
		vm_map_lock_downgrade(map);
	}

	/*
	 * Return the object/offset from this entry.  If the entry was
	 * copy-on-write or empty, it has been fixed up.
	 */
	*pindex = OFF_TO_IDX((vaddr - entry->start) + entry->offset);
	*object = entry->object.vm_object;

	*out_prot = prot;
	return (KERN_SUCCESS);
}