#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
struct vnode {struct mount* v_mount; } ;
struct thread {int dummy; } ;
struct pmckern_map_in {uintptr_t pm_address; struct vnode* pm_file; } ;
struct mount {int mnt_flag; } ;
struct file {int f_flag; struct vnode* f_vnode; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 scalar_t__ FALSE ; 
 int FPOSIXSHM ; 
 int FREAD ; 
 int FWRITE ; 
 int MAP_NOSYNC ; 
 int MAP_SHARED ; 
 int MNT_NOEXEC ; 
 scalar_t__ OFF_MAX ; 
 int /*<<< orphan*/  PMC_CALL_HOOK_UNLOCKED (struct thread*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  PMC_FN_MMAP ; 
 scalar_t__ PMC_HOOK_INSTALLED (int /*<<< orphan*/ ) ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int vm_mmap_object (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int,int,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct thread*) ; 
 int vm_mmap_vnode (struct thread*,scalar_t__,int,int*,int*,struct vnode*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_pager_release_writecount (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
vn_mmap(struct file *fp, vm_map_t map, vm_offset_t *addr, vm_size_t size,
    vm_prot_t prot, vm_prot_t cap_maxprot, int flags, vm_ooffset_t foff,
    struct thread *td)
{
#ifdef HWPMC_HOOKS
	struct pmckern_map_in pkm;
#endif
	struct mount *mp;
	struct vnode *vp;
	vm_object_t object;
	vm_prot_t maxprot;
	boolean_t writecounted;
	int error;

#if defined(COMPAT_FREEBSD7) || defined(COMPAT_FREEBSD6) || \
    defined(COMPAT_FREEBSD5) || defined(COMPAT_FREEBSD4)
	/*
	 * POSIX shared-memory objects are defined to have
	 * kernel persistence, and are not defined to support
	 * read(2)/write(2) -- or even open(2).  Thus, we can
	 * use MAP_ASYNC to trade on-disk coherence for speed.
	 * The shm_open(3) library routine turns on the FPOSIXSHM
	 * flag to request this behavior.
	 */
	if ((fp->f_flag & FPOSIXSHM) != 0)
		flags |= MAP_NOSYNC;
#endif
	vp = fp->f_vnode;

	/*
	 * Ensure that file and memory protections are
	 * compatible.  Note that we only worry about
	 * writability if mapping is shared; in this case,
	 * current and max prot are dictated by the open file.
	 * XXX use the vnode instead?  Problem is: what
	 * credentials do we use for determination? What if
	 * proc does a setuid?
	 */
	mp = vp->v_mount;
	if (mp != NULL && (mp->mnt_flag & MNT_NOEXEC) != 0) {
		maxprot = VM_PROT_NONE;
		if ((prot & VM_PROT_EXECUTE) != 0)
			return (EACCES);
	} else
		maxprot = VM_PROT_EXECUTE;
	if ((fp->f_flag & FREAD) != 0)
		maxprot |= VM_PROT_READ;
	else if ((prot & VM_PROT_READ) != 0)
		return (EACCES);

	/*
	 * If we are sharing potential changes via MAP_SHARED and we
	 * are trying to get write permission although we opened it
	 * without asking for it, bail out.
	 */
	if ((flags & MAP_SHARED) != 0) {
		if ((fp->f_flag & FWRITE) != 0)
			maxprot |= VM_PROT_WRITE;
		else if ((prot & VM_PROT_WRITE) != 0)
			return (EACCES);
	} else {
		maxprot |= VM_PROT_WRITE;
		cap_maxprot |= VM_PROT_WRITE;
	}
	maxprot &= cap_maxprot;

	/*
	 * For regular files and shared memory, POSIX requires that
	 * the value of foff be a legitimate offset within the data
	 * object.  In particular, negative offsets are invalid.
	 * Blocking negative offsets and overflows here avoids
	 * possible wraparound or user-level access into reserved
	 * ranges of the data object later.  In contrast, POSIX does
	 * not dictate how offsets are used by device drivers, so in
	 * the case of a device mapping a negative offset is passed
	 * on.
	 */
	if (
#ifdef _LP64
	    size > OFF_MAX ||
#endif
	    foff < 0 || foff > OFF_MAX - size)
		return (EINVAL);

	writecounted = FALSE;
	error = vm_mmap_vnode(td, size, prot, &maxprot, &flags, vp,
	    &foff, &object, &writecounted);
	if (error != 0)
		return (error);
	error = vm_mmap_object(map, addr, size, prot, maxprot, flags, object,
	    foff, writecounted, td);
	if (error != 0) {
		/*
		 * If this mapping was accounted for in the vnode's
		 * writecount, then undo that now.
		 */
		if (writecounted)
			vm_pager_release_writecount(object, 0, size);
		vm_object_deallocate(object);
	}
#ifdef HWPMC_HOOKS
	/* Inform hwpmc(4) if an executable is being mapped. */
	if (PMC_HOOK_INSTALLED(PMC_FN_MMAP)) {
		if ((prot & VM_PROT_EXECUTE) != 0 && error == 0) {
			pkm.pm_file = vp;
			pkm.pm_address = (uintptr_t) *addr;
			PMC_CALL_HOOK_UNLOCKED(td, PMC_FN_MMAP, (void *) &pkm);
		}
	}
#endif
	return (error);
}