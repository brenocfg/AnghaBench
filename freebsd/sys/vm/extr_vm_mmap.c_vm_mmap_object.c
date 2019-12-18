#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int vm_ooffset_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
typedef  TYPE_2__* vm_map_t ;
struct thread {TYPE_10__* td_proc; } ;
typedef  int boolean_t ;
struct TYPE_16__ {scalar_t__ size; int flags; int /*<<< orphan*/  pmap; } ;
struct TYPE_15__ {scalar_t__ vm_daddr; TYPE_2__ vm_map; } ;
struct TYPE_14__ {TYPE_1__* p_vmspace; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FALSE ; 
 int KERN_SUCCESS ; 
 int MAP_32BIT ; 
 scalar_t__ MAP_32BIT_MAX_ADDR ; 
 int MAP_ALIGNED_SUPER ; 
 int MAP_ALIGNMENT_MASK ; 
 int MAP_ALIGNMENT_SHIFT ; 
 int MAP_ANON ; 
 int MAP_CHECK_EXCL ; 
 int MAP_COPY_ON_WRITE ; 
 int MAP_CREATE_GUARD ; 
 int MAP_DISABLE_COREDUMP ; 
 int MAP_DISABLE_SYNCER ; 
 int MAP_EXCL ; 
 int MAP_FIXED ; 
 int MAP_GUARD ; 
 int MAP_INHERIT_SHARE ; 
 int MAP_NOCORE ; 
 int MAP_NOSYNC ; 
 int MAP_PREFAULT ; 
 int MAP_PREFAULT_PARTIAL ; 
 int MAP_PREFAULT_READ ; 
 int MAP_SHARED ; 
 int MAP_STACK ; 
 int MAP_STACK_GROWS_DOWN ; 
 int MAP_WIREFUTURE ; 
 int MAP_WRITECOUNT ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  RACCT_MEMLOCK ; 
 int /*<<< orphan*/  RACCT_PROC_LOCK (TYPE_10__*) ; 
 int /*<<< orphan*/  RACCT_PROC_UNLOCK (TYPE_10__*) ; 
 int /*<<< orphan*/  RACCT_VMEM ; 
 int /*<<< orphan*/  RLIMIT_DATA ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIMIT_VMEM ; 
 int TRUE ; 
 int VMFS_ALIGNED_SPACE (int) ; 
 int VMFS_OPTIMAL_SPACE ; 
 int VMFS_SUPER_SPACE ; 
 int VM_MAP_WIRE_HOLESOK ; 
 int VM_MAP_WIRE_NOHOLES ; 
 int VM_MAP_WIRE_USER ; 
 scalar_t__ lim_cur (struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ lim_max (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_mlock ; 
 int /*<<< orphan*/  pmap_wired_count (int /*<<< orphan*/ ) ; 
 scalar_t__ ptoa (int /*<<< orphan*/ ) ; 
 int racct_set (TYPE_10__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  racct_set_force (TYPE_10__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int vm_map_find (TYPE_2__*,int /*<<< orphan*/ *,int,scalar_t__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vm_map_find_min (TYPE_2__*,int /*<<< orphan*/ *,int,scalar_t__*,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vm_map_fixed (TYPE_2__*,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_wire_locked (TYPE_2__*,scalar_t__,scalar_t__,int) ; 
 int vm_mmap_to_errno (int) ; 

int
vm_mmap_object(vm_map_t map, vm_offset_t *addr, vm_size_t size, vm_prot_t prot,
    vm_prot_t maxprot, int flags, vm_object_t object, vm_ooffset_t foff,
    boolean_t writecounted, struct thread *td)
{
	boolean_t curmap, fitit;
	vm_offset_t max_addr;
	int docow, error, findspace, rv;

	curmap = map == &td->td_proc->p_vmspace->vm_map;
	if (curmap) {
		RACCT_PROC_LOCK(td->td_proc);
		if (map->size + size > lim_cur(td, RLIMIT_VMEM)) {
			RACCT_PROC_UNLOCK(td->td_proc);
			return (ENOMEM);
		}
		if (racct_set(td->td_proc, RACCT_VMEM, map->size + size)) {
			RACCT_PROC_UNLOCK(td->td_proc);
			return (ENOMEM);
		}
		if (!old_mlock && map->flags & MAP_WIREFUTURE) {
			if (ptoa(pmap_wired_count(map->pmap)) + size >
			    lim_cur(td, RLIMIT_MEMLOCK)) {
				racct_set_force(td->td_proc, RACCT_VMEM,
				    map->size);
				RACCT_PROC_UNLOCK(td->td_proc);
				return (ENOMEM);
			}
			error = racct_set(td->td_proc, RACCT_MEMLOCK,
			    ptoa(pmap_wired_count(map->pmap)) + size);
			if (error != 0) {
				racct_set_force(td->td_proc, RACCT_VMEM,
				    map->size);
				RACCT_PROC_UNLOCK(td->td_proc);
				return (error);
			}
		}
		RACCT_PROC_UNLOCK(td->td_proc);
	}

	/*
	 * We currently can only deal with page aligned file offsets.
	 * The mmap() system call already enforces this by subtracting
	 * the page offset from the file offset, but checking here
	 * catches errors in device drivers (e.g. d_single_mmap()
	 * callbacks) and other internal mapping requests (such as in
	 * exec).
	 */
	if (foff & PAGE_MASK)
		return (EINVAL);

	if ((flags & MAP_FIXED) == 0) {
		fitit = TRUE;
		*addr = round_page(*addr);
	} else {
		if (*addr != trunc_page(*addr))
			return (EINVAL);
		fitit = FALSE;
	}

	if (flags & MAP_ANON) {
		if (object != NULL || foff != 0)
			return (EINVAL);
		docow = 0;
	} else if (flags & MAP_PREFAULT_READ)
		docow = MAP_PREFAULT;
	else
		docow = MAP_PREFAULT_PARTIAL;

	if ((flags & (MAP_ANON|MAP_SHARED)) == 0)
		docow |= MAP_COPY_ON_WRITE;
	if (flags & MAP_NOSYNC)
		docow |= MAP_DISABLE_SYNCER;
	if (flags & MAP_NOCORE)
		docow |= MAP_DISABLE_COREDUMP;
	/* Shared memory is also shared with children. */
	if (flags & MAP_SHARED)
		docow |= MAP_INHERIT_SHARE;
	if (writecounted)
		docow |= MAP_WRITECOUNT;
	if (flags & MAP_STACK) {
		if (object != NULL)
			return (EINVAL);
		docow |= MAP_STACK_GROWS_DOWN;
	}
	if ((flags & MAP_EXCL) != 0)
		docow |= MAP_CHECK_EXCL;
	if ((flags & MAP_GUARD) != 0)
		docow |= MAP_CREATE_GUARD;

	if (fitit) {
		if ((flags & MAP_ALIGNMENT_MASK) == MAP_ALIGNED_SUPER)
			findspace = VMFS_SUPER_SPACE;
		else if ((flags & MAP_ALIGNMENT_MASK) != 0)
			findspace = VMFS_ALIGNED_SPACE(flags >>
			    MAP_ALIGNMENT_SHIFT);
		else
			findspace = VMFS_OPTIMAL_SPACE;
		max_addr = 0;
#ifdef MAP_32BIT
		if ((flags & MAP_32BIT) != 0)
			max_addr = MAP_32BIT_MAX_ADDR;
#endif
		if (curmap) {
			rv = vm_map_find_min(map, object, foff, addr, size,
			    round_page((vm_offset_t)td->td_proc->p_vmspace->
			    vm_daddr + lim_max(td, RLIMIT_DATA)), max_addr,
			    findspace, prot, maxprot, docow);
		} else {
			rv = vm_map_find(map, object, foff, addr, size,
			    max_addr, findspace, prot, maxprot, docow);
		}
	} else {
		rv = vm_map_fixed(map, object, foff, *addr, size,
		    prot, maxprot, docow);
	}

	if (rv == KERN_SUCCESS) {
		/*
		 * If the process has requested that all future mappings
		 * be wired, then heed this.
		 */
		if ((map->flags & MAP_WIREFUTURE) != 0) {
			vm_map_lock(map);
			if ((map->flags & MAP_WIREFUTURE) != 0)
				(void)vm_map_wire_locked(map, *addr,
				    *addr + size, VM_MAP_WIRE_USER |
				    ((flags & MAP_STACK) ? VM_MAP_WIRE_HOLESOK :
				    VM_MAP_WIRE_NOHOLES));
			vm_map_unlock(map);
		}
	}
	return (vm_mmap_to_errno(rv));
}