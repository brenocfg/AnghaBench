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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
struct vnode {struct mount* v_mount; } ;
struct thread {struct file* td_fpop; } ;
struct mount {int mnt_flag; } ;
struct file {int f_flag; struct vnode* f_vnode; } ;
struct cdevsw {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  FALSE ; 
 int FREAD ; 
 int FWRITE ; 
 int MAP_SHARED ; 
 int MNT_NOEXEC ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 int devfs_fp_check (struct file*,struct cdev**,struct cdevsw**,int*) ; 
 int vm_mmap_cdev (struct thread*,int /*<<< orphan*/ ,int,int*,int*,struct cdev*,struct cdevsw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vm_mmap_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devfs_mmap_f(struct file *fp, vm_map_t map, vm_offset_t *addr, vm_size_t size,
    vm_prot_t prot, vm_prot_t cap_maxprot, int flags, vm_ooffset_t foff,
    struct thread *td)
{
	struct cdev *dev;
	struct cdevsw *dsw;
	struct mount *mp;
	struct vnode *vp;
	struct file *fpop;
	vm_object_t object;
	vm_prot_t maxprot;
	int error, ref;

	vp = fp->f_vnode;

	/*
	 * Ensure that file and memory protections are
	 * compatible.
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
	 *
	 * Note that most character devices always share mappings.
	 * The one exception is that D_MMAP_ANON devices
	 * (i.e. /dev/zero) permit private writable mappings.
	 *
	 * Rely on vm_mmap_cdev() to fail invalid MAP_PRIVATE requests
	 * as well as updating maxprot to permit writing for
	 * D_MMAP_ANON devices rather than doing that here.
	 */
	if ((flags & MAP_SHARED) != 0) {
		if ((fp->f_flag & FWRITE) != 0)
			maxprot |= VM_PROT_WRITE;
		else if ((prot & VM_PROT_WRITE) != 0)
			return (EACCES);
	}
	maxprot &= cap_maxprot;

	fpop = td->td_fpop;
	error = devfs_fp_check(fp, &dev, &dsw, &ref);
	if (error != 0)
		return (error);

	error = vm_mmap_cdev(td, size, prot, &maxprot, &flags, dev, dsw, &foff,
	    &object);
	td->td_fpop = fpop;
	dev_relthread(dev, ref);
	if (error != 0)
		return (error);

	error = vm_mmap_object(map, addr, size, prot, maxprot, flags, object,
	    foff, FALSE, td);
	if (error != 0)
		vm_object_deallocate(object);
	return (error);
}