#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_31__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_ooffset_t ;
typedef  TYPE_4__* vm_object_t ;
typedef  TYPE_5__* vm_map_t ;
typedef  TYPE_6__* vm_map_entry_t ;
typedef  int vm_inherit_t ;
struct vnode {int /*<<< orphan*/  v_writecount; } ;
struct TYPE_34__ {TYPE_4__* vm_object; } ;
struct TYPE_40__ {int eflags; int inheritance; scalar_t__ start; scalar_t__ end; int /*<<< orphan*/ * cred; int /*<<< orphan*/  max_protection; int /*<<< orphan*/  protection; TYPE_1__ object; int /*<<< orphan*/  wired_count; int /*<<< orphan*/ * wiring_thread; int /*<<< orphan*/  offset; struct TYPE_40__* next; } ;
struct TYPE_39__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pmap; TYPE_6__ header; int /*<<< orphan*/  anon_loc; scalar_t__ busy; } ;
struct vmspace {TYPE_5__ vm_map; int /*<<< orphan*/  vm_maxsaddr; int /*<<< orphan*/  vm_daddr; int /*<<< orphan*/  vm_taddr; } ;
struct TYPE_35__ {int /*<<< orphan*/  writemappings; } ;
struct TYPE_37__ {TYPE_2__ vnp; } ;
struct TYPE_38__ {TYPE_3__ un_pager; scalar_t__ handle; int /*<<< orphan*/  type; scalar_t__ charge; int /*<<< orphan*/ * cred; } ;
struct TYPE_36__ {int /*<<< orphan*/ * td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAP_ENTRY_GUARD ; 
 int MAP_ENTRY_IN_TRANSITION ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int MAP_ENTRY_NEEDS_COPY ; 
 int MAP_ENTRY_USER_WIRED ; 
 int MAP_ENTRY_VN_EXEC ; 
 int MAP_ENTRY_WRITECNT ; 
 int /*<<< orphan*/  OBJT_VNODE ; 
 int /*<<< orphan*/  OBJ_ONEMAPPING ; 
#define  VM_INHERIT_COPY 131 
#define  VM_INHERIT_NONE 130 
#define  VM_INHERIT_SHARE 129 
#define  VM_INHERIT_ZERO 128 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ *) ; 
 TYPE_31__* curthread ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_pinit ; 
 int pmap_vmspace_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_copy_entry (TYPE_5__*,TYPE_5__*,TYPE_6__*,TYPE_6__*,scalar_t__*) ; 
 int /*<<< orphan*/  vm_map_entry_back (TYPE_6__*) ; 
 TYPE_6__* vm_map_entry_create (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_entry_link (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  vm_map_entry_set_vnode_text (TYPE_6__*,int) ; 
 TYPE_6__* vm_map_entry_succ (TYPE_6__*) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_max (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_min (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_process_deferred () ; 
 int vm_map_trylock (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_wait_busy (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_object_clear_flag (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_4__*) ; 
 int /*<<< orphan*/  vm_object_reference (TYPE_4__*) ; 
 int /*<<< orphan*/  vm_object_shadow (TYPE_4__**,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vm_pager_update_writecount (TYPE_4__*,scalar_t__,scalar_t__) ; 
 struct vmspace* vmspace_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmspace_free (struct vmspace*) ; 
 int /*<<< orphan*/  vmspace_map_entry_forked (struct vmspace*,struct vmspace*,TYPE_6__*) ; 

struct vmspace *
vmspace_fork(struct vmspace *vm1, vm_ooffset_t *fork_charge)
{
	struct vmspace *vm2;
	vm_map_t new_map, old_map;
	vm_map_entry_t new_entry, old_entry;
	vm_object_t object;
	int error, locked;
	vm_inherit_t inh;

	old_map = &vm1->vm_map;
	/* Copy immutable fields of vm1 to vm2. */
	vm2 = vmspace_alloc(vm_map_min(old_map), vm_map_max(old_map),
	    pmap_pinit);
	if (vm2 == NULL)
		return (NULL);

	vm2->vm_taddr = vm1->vm_taddr;
	vm2->vm_daddr = vm1->vm_daddr;
	vm2->vm_maxsaddr = vm1->vm_maxsaddr;
	vm_map_lock(old_map);
	if (old_map->busy)
		vm_map_wait_busy(old_map);
	new_map = &vm2->vm_map;
	locked = vm_map_trylock(new_map); /* trylock to silence WITNESS */
	KASSERT(locked, ("vmspace_fork: lock failed"));

	error = pmap_vmspace_copy(new_map->pmap, old_map->pmap);
	if (error != 0) {
		sx_xunlock(&old_map->lock);
		sx_xunlock(&new_map->lock);
		vm_map_process_deferred();
		vmspace_free(vm2);
		return (NULL);
	}

	new_map->anon_loc = old_map->anon_loc;

	old_entry = old_map->header.next;

	while (old_entry != &old_map->header) {
		if (old_entry->eflags & MAP_ENTRY_IS_SUB_MAP)
			panic("vm_map_fork: encountered a submap");

		inh = old_entry->inheritance;
		if ((old_entry->eflags & MAP_ENTRY_GUARD) != 0 &&
		    inh != VM_INHERIT_NONE)
			inh = VM_INHERIT_COPY;

		switch (inh) {
		case VM_INHERIT_NONE:
			break;

		case VM_INHERIT_SHARE:
			/*
			 * Clone the entry, creating the shared object if necessary.
			 */
			object = old_entry->object.vm_object;
			if (object == NULL) {
				vm_map_entry_back(old_entry);
				object = old_entry->object.vm_object;
			}

			/*
			 * Add the reference before calling vm_object_shadow
			 * to insure that a shadow object is created.
			 */
			vm_object_reference(object);
			if (old_entry->eflags & MAP_ENTRY_NEEDS_COPY) {
				vm_object_shadow(&old_entry->object.vm_object,
				    &old_entry->offset,
				    old_entry->end - old_entry->start);
				old_entry->eflags &= ~MAP_ENTRY_NEEDS_COPY;
				/* Transfer the second reference too. */
				vm_object_reference(
				    old_entry->object.vm_object);

				/*
				 * As in vm_map_merged_neighbor_dispose(),
				 * the vnode lock will not be acquired in
				 * this call to vm_object_deallocate().
				 */
				vm_object_deallocate(object);
				object = old_entry->object.vm_object;
			}
			VM_OBJECT_WLOCK(object);
			vm_object_clear_flag(object, OBJ_ONEMAPPING);
			if (old_entry->cred != NULL) {
				KASSERT(object->cred == NULL, ("vmspace_fork both cred"));
				object->cred = old_entry->cred;
				object->charge = old_entry->end - old_entry->start;
				old_entry->cred = NULL;
			}

			/*
			 * Assert the correct state of the vnode
			 * v_writecount while the object is locked, to
			 * not relock it later for the assertion
			 * correctness.
			 */
			if (old_entry->eflags & MAP_ENTRY_WRITECNT &&
			    object->type == OBJT_VNODE) {
				KASSERT(((struct vnode *)object->handle)->
				    v_writecount > 0,
				    ("vmspace_fork: v_writecount %p", object));
				KASSERT(object->un_pager.vnp.writemappings > 0,
				    ("vmspace_fork: vnp.writecount %p",
				    object));
			}
			VM_OBJECT_WUNLOCK(object);

			/*
			 * Clone the entry, referencing the shared object.
			 */
			new_entry = vm_map_entry_create(new_map);
			*new_entry = *old_entry;
			new_entry->eflags &= ~(MAP_ENTRY_USER_WIRED |
			    MAP_ENTRY_IN_TRANSITION);
			new_entry->wiring_thread = NULL;
			new_entry->wired_count = 0;
			if (new_entry->eflags & MAP_ENTRY_WRITECNT) {
				vm_pager_update_writecount(object,
				    new_entry->start, new_entry->end);
			}
			vm_map_entry_set_vnode_text(new_entry, true);

			/*
			 * Insert the entry into the new map -- we know we're
			 * inserting at the end of the new map.
			 */
			vm_map_entry_link(new_map, new_entry);
			vmspace_map_entry_forked(vm1, vm2, new_entry);

			/*
			 * Update the physical map
			 */
			pmap_copy(new_map->pmap, old_map->pmap,
			    new_entry->start,
			    (old_entry->end - old_entry->start),
			    old_entry->start);
			break;

		case VM_INHERIT_COPY:
			/*
			 * Clone the entry and link into the map.
			 */
			new_entry = vm_map_entry_create(new_map);
			*new_entry = *old_entry;
			/*
			 * Copied entry is COW over the old object.
			 */
			new_entry->eflags &= ~(MAP_ENTRY_USER_WIRED |
			    MAP_ENTRY_IN_TRANSITION | MAP_ENTRY_WRITECNT);
			new_entry->wiring_thread = NULL;
			new_entry->wired_count = 0;
			new_entry->object.vm_object = NULL;
			new_entry->cred = NULL;
			vm_map_entry_link(new_map, new_entry);
			vmspace_map_entry_forked(vm1, vm2, new_entry);
			vm_map_copy_entry(old_map, new_map, old_entry,
			    new_entry, fork_charge);
			vm_map_entry_set_vnode_text(new_entry, true);
			break;

		case VM_INHERIT_ZERO:
			/*
			 * Create a new anonymous mapping entry modelled from
			 * the old one.
			 */
			new_entry = vm_map_entry_create(new_map);
			memset(new_entry, 0, sizeof(*new_entry));

			new_entry->start = old_entry->start;
			new_entry->end = old_entry->end;
			new_entry->eflags = old_entry->eflags &
			    ~(MAP_ENTRY_USER_WIRED | MAP_ENTRY_IN_TRANSITION |
			    MAP_ENTRY_WRITECNT | MAP_ENTRY_VN_EXEC);
			new_entry->protection = old_entry->protection;
			new_entry->max_protection = old_entry->max_protection;
			new_entry->inheritance = VM_INHERIT_ZERO;

			vm_map_entry_link(new_map, new_entry);
			vmspace_map_entry_forked(vm1, vm2, new_entry);

			new_entry->cred = curthread->td_ucred;
			crhold(new_entry->cred);
			*fork_charge += (new_entry->end - new_entry->start);

			break;
		}
		old_entry = vm_map_entry_succ(old_entry);
	}
	/*
	 * Use inlined vm_map_unlock() to postpone handling the deferred
	 * map entries, which cannot be done until both old_map and
	 * new_map locks are released.
	 */
	sx_xunlock(&old_map->lock);
	sx_xunlock(&new_map->lock);
	vm_map_process_deferred();

	return (vm2);
}