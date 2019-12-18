#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_3__* vm_map_t ;
typedef  TYPE_4__* vm_map_entry_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_25__ {int flags; scalar_t__ size; int /*<<< orphan*/  pmap; int /*<<< orphan*/  system_map; } ;
struct vmspace {int /*<<< orphan*/  vm_ssize; scalar_t__ vm_maxsaddr; TYPE_3__ vm_map; } ;
struct ucred {int dummy; } ;
struct proc {int p_flag2; int p_fctl0; TYPE_2__* p_sysent; int /*<<< orphan*/ * p_textvp; struct vmspace* p_vmspace; } ;
typedef  scalar_t__ rlim_t ;
struct TYPE_27__ {struct ucred* cred; } ;
struct TYPE_23__ {TYPE_5__* vm_object; } ;
struct TYPE_26__ {int eflags; scalar_t__ start; scalar_t__ end; scalar_t__ next_read; int /*<<< orphan*/  offset; TYPE_1__ object; struct ucred* cred; int /*<<< orphan*/  max_protection; int /*<<< orphan*/  protection; } ;
struct TYPE_24__ {scalar_t__ sv_usrstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_FAILURE ; 
 int KERN_NO_SPACE ; 
 int KERN_SUCCESS ; 
 int MAP_CREATE_GUARD ; 
 int MAP_CREATE_STACK_GAP_DN ; 
 int MAP_ENTRY_GROWS_DOWN ; 
 int MAP_ENTRY_GROWS_UP ; 
 int MAP_ENTRY_GUARD ; 
 int MAP_ENTRY_STACK_GAP_DN ; 
 int MAP_ENTRY_STACK_GAP_UP ; 
 int MAP_STACK_GROWS_DOWN ; 
 int MAP_WIREFUTURE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NT_FREEBSD_FCTL_STKGAP_DISABLE ; 
 int P2_STKGAP_DISABLE ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  RACCT_MEMLOCK ; 
 int /*<<< orphan*/  RACCT_STACK ; 
 int /*<<< orphan*/  RACCT_VMEM ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIMIT_STACK ; 
 int /*<<< orphan*/  RLIMIT_VMEM ; 
 int VM_MAP_WIRE_NOHOLES ; 
 int VM_MAP_WIRE_USER ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 scalar_t__ btoc (scalar_t__) ; 
 scalar_t__ ctob (int /*<<< orphan*/ ) ; 
 struct proc* curproc ; 
 int /*<<< orphan*/  curthread ; 
 struct proc* initproc ; 
 scalar_t__ lim_cur (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_mlock ; 
 int /*<<< orphan*/  pmap_wired_count (int /*<<< orphan*/ ) ; 
 scalar_t__ ptoa (int /*<<< orphan*/ ) ; 
 scalar_t__ racct_enable ; 
 scalar_t__ racct_get_available (struct proc*,int /*<<< orphan*/ ) ; 
 int racct_set (struct proc*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgrowsiz ; 
 int /*<<< orphan*/  swap_reserve_by_cred (scalar_t__,struct ucred*) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_entry_delete (TYPE_3__*,TYPE_4__*) ; 
 TYPE_4__* vm_map_entry_pred (TYPE_4__*) ; 
 int /*<<< orphan*/  vm_map_entry_resize (TYPE_3__*,TYPE_4__*,scalar_t__) ; 
 TYPE_4__* vm_map_entry_succ (TYPE_4__*) ; 
 int vm_map_insert (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_map_lock_downgrade (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (TYPE_3__*) ; 
 scalar_t__ vm_map_lock_upgrade (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (TYPE_3__*,scalar_t__,TYPE_4__**) ; 
 int vm_map_wire_locked (TYPE_3__*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ vm_object_coalesce (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vm_map_growstack(vm_map_t map, vm_offset_t addr, vm_map_entry_t gap_entry)
{
	vm_map_entry_t stack_entry;
	struct proc *p;
	struct vmspace *vm;
	struct ucred *cred;
	vm_offset_t gap_end, gap_start, grow_start;
	vm_size_t grow_amount, guard, max_grow;
	rlim_t lmemlim, stacklim, vmemlim;
	int rv, rv1;
	bool gap_deleted, grow_down, is_procstack;
#ifdef notyet
	uint64_t limit;
#endif
#ifdef RACCT
	int error;
#endif

	p = curproc;
	vm = p->p_vmspace;

	/*
	 * Disallow stack growth when the access is performed by a
	 * debugger or AIO daemon.  The reason is that the wrong
	 * resource limits are applied.
	 */
	if (p != initproc && (map != &p->p_vmspace->vm_map ||
	    p->p_textvp == NULL))
		return (KERN_FAILURE);

	MPASS(!map->system_map);

	lmemlim = lim_cur(curthread, RLIMIT_MEMLOCK);
	stacklim = lim_cur(curthread, RLIMIT_STACK);
	vmemlim = lim_cur(curthread, RLIMIT_VMEM);
retry:
	/* If addr is not in a hole for a stack grow area, no need to grow. */
	if (gap_entry == NULL && !vm_map_lookup_entry(map, addr, &gap_entry))
		return (KERN_FAILURE);
	if ((gap_entry->eflags & MAP_ENTRY_GUARD) == 0)
		return (KERN_SUCCESS);
	if ((gap_entry->eflags & MAP_ENTRY_STACK_GAP_DN) != 0) {
		stack_entry = vm_map_entry_succ(gap_entry);
		if ((stack_entry->eflags & MAP_ENTRY_GROWS_DOWN) == 0 ||
		    stack_entry->start != gap_entry->end)
			return (KERN_FAILURE);
		grow_amount = round_page(stack_entry->start - addr);
		grow_down = true;
	} else if ((gap_entry->eflags & MAP_ENTRY_STACK_GAP_UP) != 0) {
		stack_entry = vm_map_entry_pred(gap_entry);
		if ((stack_entry->eflags & MAP_ENTRY_GROWS_UP) == 0 ||
		    stack_entry->end != gap_entry->start)
			return (KERN_FAILURE);
		grow_amount = round_page(addr + 1 - stack_entry->end);
		grow_down = false;
	} else {
		return (KERN_FAILURE);
	}
	guard = ((curproc->p_flag2 & P2_STKGAP_DISABLE) != 0 ||
	    (curproc->p_fctl0 & NT_FREEBSD_FCTL_STKGAP_DISABLE) != 0) ? 0 :
	    gap_entry->next_read;
	max_grow = gap_entry->end - gap_entry->start;
	if (guard > max_grow)
		return (KERN_NO_SPACE);
	max_grow -= guard;
	if (grow_amount > max_grow)
		return (KERN_NO_SPACE);

	/*
	 * If this is the main process stack, see if we're over the stack
	 * limit.
	 */
	is_procstack = addr >= (vm_offset_t)vm->vm_maxsaddr &&
	    addr < (vm_offset_t)p->p_sysent->sv_usrstack;
	if (is_procstack && (ctob(vm->vm_ssize) + grow_amount > stacklim))
		return (KERN_NO_SPACE);

#ifdef RACCT
	if (racct_enable) {
		PROC_LOCK(p);
		if (is_procstack && racct_set(p, RACCT_STACK,
		    ctob(vm->vm_ssize) + grow_amount)) {
			PROC_UNLOCK(p);
			return (KERN_NO_SPACE);
		}
		PROC_UNLOCK(p);
	}
#endif

	grow_amount = roundup(grow_amount, sgrowsiz);
	if (grow_amount > max_grow)
		grow_amount = max_grow;
	if (is_procstack && (ctob(vm->vm_ssize) + grow_amount > stacklim)) {
		grow_amount = trunc_page((vm_size_t)stacklim) -
		    ctob(vm->vm_ssize);
	}

#ifdef notyet
	PROC_LOCK(p);
	limit = racct_get_available(p, RACCT_STACK);
	PROC_UNLOCK(p);
	if (is_procstack && (ctob(vm->vm_ssize) + grow_amount > limit))
		grow_amount = limit - ctob(vm->vm_ssize);
#endif

	if (!old_mlock && (map->flags & MAP_WIREFUTURE) != 0) {
		if (ptoa(pmap_wired_count(map->pmap)) + grow_amount > lmemlim) {
			rv = KERN_NO_SPACE;
			goto out;
		}
#ifdef RACCT
		if (racct_enable) {
			PROC_LOCK(p);
			if (racct_set(p, RACCT_MEMLOCK,
			    ptoa(pmap_wired_count(map->pmap)) + grow_amount)) {
				PROC_UNLOCK(p);
				rv = KERN_NO_SPACE;
				goto out;
			}
			PROC_UNLOCK(p);
		}
#endif
	}

	/* If we would blow our VMEM resource limit, no go */
	if (map->size + grow_amount > vmemlim) {
		rv = KERN_NO_SPACE;
		goto out;
	}
#ifdef RACCT
	if (racct_enable) {
		PROC_LOCK(p);
		if (racct_set(p, RACCT_VMEM, map->size + grow_amount)) {
			PROC_UNLOCK(p);
			rv = KERN_NO_SPACE;
			goto out;
		}
		PROC_UNLOCK(p);
	}
#endif

	if (vm_map_lock_upgrade(map)) {
		gap_entry = NULL;
		vm_map_lock_read(map);
		goto retry;
	}

	if (grow_down) {
		grow_start = gap_entry->end - grow_amount;
		if (gap_entry->start + grow_amount == gap_entry->end) {
			gap_start = gap_entry->start;
			gap_end = gap_entry->end;
			vm_map_entry_delete(map, gap_entry);
			gap_deleted = true;
		} else {
			MPASS(gap_entry->start < gap_entry->end - grow_amount);
			vm_map_entry_resize(map, gap_entry, -grow_amount);
			gap_deleted = false;
		}
		rv = vm_map_insert(map, NULL, 0, grow_start,
		    grow_start + grow_amount,
		    stack_entry->protection, stack_entry->max_protection,
		    MAP_STACK_GROWS_DOWN);
		if (rv != KERN_SUCCESS) {
			if (gap_deleted) {
				rv1 = vm_map_insert(map, NULL, 0, gap_start,
				    gap_end, VM_PROT_NONE, VM_PROT_NONE,
				    MAP_CREATE_GUARD | MAP_CREATE_STACK_GAP_DN);
				MPASS(rv1 == KERN_SUCCESS);
			} else
				vm_map_entry_resize(map, gap_entry,
				    grow_amount);
		}
	} else {
		grow_start = stack_entry->end;
		cred = stack_entry->cred;
		if (cred == NULL && stack_entry->object.vm_object != NULL)
			cred = stack_entry->object.vm_object->cred;
		if (cred != NULL && !swap_reserve_by_cred(grow_amount, cred))
			rv = KERN_NO_SPACE;
		/* Grow the underlying object if applicable. */
		else if (stack_entry->object.vm_object == NULL ||
		    vm_object_coalesce(stack_entry->object.vm_object,
		    stack_entry->offset,
		    (vm_size_t)(stack_entry->end - stack_entry->start),
		    grow_amount, cred != NULL)) {
			if (gap_entry->start + grow_amount == gap_entry->end) {
				vm_map_entry_delete(map, gap_entry);
				vm_map_entry_resize(map, stack_entry,
				    grow_amount);
			} else {
				gap_entry->start += grow_amount;
				stack_entry->end += grow_amount;
			}
			map->size += grow_amount;
			rv = KERN_SUCCESS;
		} else
			rv = KERN_FAILURE;
	}
	if (rv == KERN_SUCCESS && is_procstack)
		vm->vm_ssize += btoc(grow_amount);

	/*
	 * Heed the MAP_WIREFUTURE flag if it was set for this process.
	 */
	if (rv == KERN_SUCCESS && (map->flags & MAP_WIREFUTURE) != 0) {
		rv = vm_map_wire_locked(map, grow_start,
		    grow_start + grow_amount,
		    VM_MAP_WIRE_USER | VM_MAP_WIRE_NOHOLES);
	}
	vm_map_lock_downgrade(map);

out:
#ifdef RACCT
	if (racct_enable && rv != KERN_SUCCESS) {
		PROC_LOCK(p);
		error = racct_set(p, RACCT_VMEM, map->size);
		KASSERT(error == 0, ("decreasing RACCT_VMEM failed"));
		if (!old_mlock) {
			error = racct_set(p, RACCT_MEMLOCK,
			    ptoa(pmap_wired_count(map->pmap)));
			KASSERT(error == 0, ("decreasing RACCT_MEMLOCK failed"));
		}
	    	error = racct_set(p, RACCT_STACK, ctob(vm->vm_ssize));
		KASSERT(error == 0, ("decreasing RACCT_STACK failed"));
		PROC_UNLOCK(p);
	}
#endif

	return (rv);
}