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
typedef  scalar_t__ vm_ooffset_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct cdevsw {int d_flags; int (* d_mmap_single ) (struct cdev*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ;} ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int D_MMAP_ANON ; 
 int EACCES ; 
 int EINVAL ; 
 int ENODEV ; 
 int MAP_ANON ; 
 int MAP_COPY ; 
 int MAP_PRIVATE ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  OBJT_DEVICE ; 
 int VM_PROT_ALL ; 
 int VM_PROT_WRITE ; 
 int mac_cdev_check_mmap (int /*<<< orphan*/ ,struct cdev*,int) ; 
 int stub1 (struct cdev*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * vm_pager_allocate (int /*<<< orphan*/ ,struct cdev*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

int
vm_mmap_cdev(struct thread *td, vm_size_t objsize, vm_prot_t prot,
    vm_prot_t *maxprotp, int *flagsp, struct cdev *cdev, struct cdevsw *dsw,
    vm_ooffset_t *foff, vm_object_t *objp)
{
	vm_object_t obj;
	int error, flags;

	flags = *flagsp;

	if (dsw->d_flags & D_MMAP_ANON) {
		*objp = NULL;
		*foff = 0;
		*maxprotp = VM_PROT_ALL;
		*flagsp |= MAP_ANON;
		return (0);
	}
	/*
	 * cdevs do not provide private mappings of any kind.
	 */
	if ((*maxprotp & VM_PROT_WRITE) == 0 &&
	    (prot & VM_PROT_WRITE) != 0)
		return (EACCES);
	if (flags & (MAP_PRIVATE|MAP_COPY))
		return (EINVAL);
	/*
	 * Force device mappings to be shared.
	 */
	flags |= MAP_SHARED;
#ifdef MAC_XXX
	error = mac_cdev_check_mmap(td->td_ucred, cdev, (int)prot);
	if (error != 0)
		return (error);
#endif
	/*
	 * First, try d_mmap_single().  If that is not implemented
	 * (returns ENODEV), fall back to using the device pager.
	 * Note that d_mmap_single() must return a reference to the
	 * object (it needs to bump the reference count of the object
	 * it returns somehow).
	 *
	 * XXX assumes VM_PROT_* == PROT_*
	 */
	error = dsw->d_mmap_single(cdev, foff, objsize, objp, (int)prot);
	if (error != ENODEV)
		return (error);
	obj = vm_pager_allocate(OBJT_DEVICE, cdev, objsize, prot, *foff,
	    td->td_ucred);
	if (obj == NULL)
		return (EINVAL);
	*objp = obj;
	*flagsp = flags;
	return (0);
}