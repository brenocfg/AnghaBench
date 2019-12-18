#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
struct TYPE_13__ {int flags; scalar_t__ size; int /*<<< orphan*/  pmap; } ;
struct vmspace {int /*<<< orphan*/  vm_dsize; scalar_t__ vm_daddr; TYPE_1__ vm_map; } ;
struct thread {TYPE_8__* td_proc; } ;
typedef  scalar_t__ rlim_t ;
struct TYPE_14__ {struct vmspace* p_vmspace; } ;

/* Variables and functions */
 int ENOMEM ; 
 int KERN_SUCCESS ; 
 int MAP_WIREFUTURE ; 
 int /*<<< orphan*/  PROC_LOCK (TYPE_8__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_8__*) ; 
 int /*<<< orphan*/  RACCT_DATA ; 
 int /*<<< orphan*/  RACCT_MEMLOCK ; 
 int /*<<< orphan*/  RACCT_VMEM ; 
 int /*<<< orphan*/  RLIMIT_DATA ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIMIT_VMEM ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int VM_MAP_WIRE_NOHOLES ; 
 int VM_MAP_WIRE_USER ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_RW ; 
 scalar_t__ btoc (scalar_t__) ; 
 scalar_t__ ctob (int /*<<< orphan*/ ) ; 
 scalar_t__ i386_read_exec ; 
 scalar_t__ lim_cur (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_mlock ; 
 int /*<<< orphan*/  pmap_wired_count (int /*<<< orphan*/ ) ; 
 scalar_t__ ptoa (int /*<<< orphan*/ ) ; 
 scalar_t__ racct_enable ; 
 int racct_set (TYPE_8__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  racct_set_force (TYPE_8__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ round_page (scalar_t__) ; 
 int vm_map_delete (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int vm_map_insert (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_1__*) ; 
 scalar_t__ vm_map_max (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_1__*) ; 
 int vm_map_wire_locked (TYPE_1__*,scalar_t__,scalar_t__,int) ; 

int
kern_break(struct thread *td, uintptr_t *addr)
{
	struct vmspace *vm = td->td_proc->p_vmspace;
	vm_map_t map = &vm->vm_map;
	vm_offset_t new, old, base;
	rlim_t datalim, lmemlim, vmemlim;
	int prot, rv;
	int error = 0;

	datalim = lim_cur(td, RLIMIT_DATA);
	lmemlim = lim_cur(td, RLIMIT_MEMLOCK);
	vmemlim = lim_cur(td, RLIMIT_VMEM);

	new = round_page(*addr);
	vm_map_lock(map);

	base = round_page((vm_offset_t) vm->vm_daddr);
	old = base + ctob(vm->vm_dsize);
	if (new > base) {
		/*
		 * Check the resource limit, but allow a process to reduce
		 * its usage, even if it remains over the limit.
		 */
		if (new - base > datalim && new > old) {
			error = ENOMEM;
			goto done;
		}
		if (new > vm_map_max(map)) {
			error = ENOMEM;
			goto done;
		}
	} else if (new < base) {
		/*
		 * Simply return the current break address without
		 * modifying any state.  This is an ad-hoc interface
		 * used by libc to determine the initial break address,
		 * avoiding a dependency on magic features in the system
		 * linker.
		 */
		new = old;
		goto done;
	}

	if (new > old) {
		if (!old_mlock && map->flags & MAP_WIREFUTURE) {
			if (ptoa(pmap_wired_count(map->pmap)) +
			    (new - old) > lmemlim) {
				error = ENOMEM;
				goto done;
			}
		}
		if (map->size + (new - old) > vmemlim) {
			error = ENOMEM;
			goto done;
		}
#ifdef RACCT
		if (racct_enable) {
			PROC_LOCK(td->td_proc);
			error = racct_set(td->td_proc, RACCT_DATA, new - base);
			if (error != 0) {
				PROC_UNLOCK(td->td_proc);
				error = ENOMEM;
				goto done;
			}
			error = racct_set(td->td_proc, RACCT_VMEM,
			    map->size + (new - old));
			if (error != 0) {
				racct_set_force(td->td_proc, RACCT_DATA,
				    old - base);
				PROC_UNLOCK(td->td_proc);
				error = ENOMEM;
				goto done;
			}
			if (!old_mlock && map->flags & MAP_WIREFUTURE) {
				error = racct_set(td->td_proc, RACCT_MEMLOCK,
				    ptoa(pmap_wired_count(map->pmap)) +
				    (new - old));
				if (error != 0) {
					racct_set_force(td->td_proc, RACCT_DATA,
					    old - base);
					racct_set_force(td->td_proc, RACCT_VMEM,
					    map->size);
					PROC_UNLOCK(td->td_proc);
					error = ENOMEM;
					goto done;
				}
			}
			PROC_UNLOCK(td->td_proc);
		}
#endif
		prot = VM_PROT_RW;
#if (defined(COMPAT_FREEBSD32) && defined(__amd64__)) || defined(__i386__)
		if (i386_read_exec && SV_PROC_FLAG(td->td_proc, SV_ILP32))
			prot |= VM_PROT_EXECUTE;
#endif
		rv = vm_map_insert(map, NULL, 0, old, new, prot, VM_PROT_ALL,
		    0);
		if (rv == KERN_SUCCESS && (map->flags & MAP_WIREFUTURE) != 0) {
			rv = vm_map_wire_locked(map, old, new,
			    VM_MAP_WIRE_USER | VM_MAP_WIRE_NOHOLES);
			if (rv != KERN_SUCCESS)
				vm_map_delete(map, old, new);
		}
		if (rv != KERN_SUCCESS) {
#ifdef RACCT
			if (racct_enable) {
				PROC_LOCK(td->td_proc);
				racct_set_force(td->td_proc,
				    RACCT_DATA, old - base);
				racct_set_force(td->td_proc,
				    RACCT_VMEM, map->size);
				if (!old_mlock && map->flags & MAP_WIREFUTURE) {
					racct_set_force(td->td_proc,
					    RACCT_MEMLOCK,
					    ptoa(pmap_wired_count(map->pmap)));
				}
				PROC_UNLOCK(td->td_proc);
			}
#endif
			error = ENOMEM;
			goto done;
		}
		vm->vm_dsize += btoc(new - old);
	} else if (new < old) {
		rv = vm_map_delete(map, new, old);
		if (rv != KERN_SUCCESS) {
			error = ENOMEM;
			goto done;
		}
		vm->vm_dsize -= btoc(old - new);
#ifdef RACCT
		if (racct_enable) {
			PROC_LOCK(td->td_proc);
			racct_set_force(td->td_proc, RACCT_DATA, new - base);
			racct_set_force(td->td_proc, RACCT_VMEM, map->size);
			if (!old_mlock && map->flags & MAP_WIREFUTURE) {
				racct_set_force(td->td_proc, RACCT_MEMLOCK,
				    ptoa(pmap_wired_count(map->pmap)));
			}
			PROC_UNLOCK(td->td_proc);
		}
#endif
	}
done:
	vm_map_unlock(map);

	if (error == 0)
		*addr = new;

	return (error);
}