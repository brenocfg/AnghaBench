#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct drm_gem_object {int refcount; size_t size; scalar_t__ handle_count; int /*<<< orphan*/  vm_obj; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  OBJT_DEFAULT ; 
 int PAGE_SIZE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  vm_pager_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_gem_object_init(struct drm_device *dev,
			struct drm_gem_object *obj, size_t size)
{
	KASSERT((size & (PAGE_SIZE - 1)) == 0,
	    ("Bad size %ju", (uintmax_t)size));

	obj->dev = dev;
	obj->vm_obj = vm_pager_allocate(OBJT_DEFAULT, NULL, size,
	    VM_PROT_READ | VM_PROT_WRITE, 0, curthread->td_ucred);

	obj->refcount = 1;
	obj->handle_count = 0;
	obj->size = size;

	return 0;
}