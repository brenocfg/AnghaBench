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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
struct thread {int dummy; } ;
struct cdevsw {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int objtype_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ FALSE ; 
#define  OBJT_DEFAULT 130 
#define  OBJT_DEVICE 129 
#define  OBJT_VNODE 128 
 struct thread* curthread ; 
 struct cdevsw* dev_refthread (struct cdev*,int*) ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 scalar_t__ round_page (scalar_t__) ; 
 int vm_mmap_cdev (struct thread*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,struct cdev*,struct cdevsw*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int vm_mmap_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,struct thread*) ; 
 int vm_mmap_vnode (struct thread*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pager_release_writecount (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

int
vm_mmap(vm_map_t map, vm_offset_t *addr, vm_size_t size, vm_prot_t prot,
	vm_prot_t maxprot, int flags,
	objtype_t handle_type, void *handle,
	vm_ooffset_t foff)
{
	vm_object_t object;
	struct thread *td = curthread;
	int error;
	boolean_t writecounted;

	if (size == 0)
		return (EINVAL);

	size = round_page(size);
	object = NULL;
	writecounted = FALSE;

	/*
	 * Lookup/allocate object.
	 */
	switch (handle_type) {
	case OBJT_DEVICE: {
		struct cdevsw *dsw;
		struct cdev *cdev;
		int ref;

		cdev = handle;
		dsw = dev_refthread(cdev, &ref);
		if (dsw == NULL)
			return (ENXIO);
		error = vm_mmap_cdev(td, size, prot, &maxprot, &flags, cdev,
		    dsw, &foff, &object);
		dev_relthread(cdev, ref);
		break;
	}
	case OBJT_VNODE:
		error = vm_mmap_vnode(td, size, prot, &maxprot, &flags,
		    handle, &foff, &object, &writecounted);
		break;
	case OBJT_DEFAULT:
		if (handle == NULL) {
			error = 0;
			break;
		}
		/* FALLTHROUGH */
	default:
		error = EINVAL;
		break;
	}
	if (error)
		return (error);

	error = vm_mmap_object(map, addr, size, prot, maxprot, flags, object,
	    foff, writecounted, td);
	if (error != 0 && object != NULL) {
		/*
		 * If this mapping was accounted for in the vnode's
		 * writecount, then undo that now.
		 */
		if (writecounted)
			vm_pager_release_writecount(object, 0, size);
		vm_object_deallocate(object);
	}
	return (error);
}