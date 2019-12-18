#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
struct vm_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_3__ {int /*<<< orphan*/  gem_pager_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_GEM_MAPPING_MAPOFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  OBJT_MGTDEVICE ; 
 struct vm_object* cdev_pager_allocate (struct drm_gem_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* curthread ; 
 struct drm_gem_object* drm_gem_object_from_offset (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_reference (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 

int
drm_gem_mmap_single(struct drm_device *dev, vm_ooffset_t *offset, vm_size_t size,
    struct vm_object **obj_res, int nprot)
{
	struct drm_gem_object *gem_obj;
	struct vm_object *vm_obj;

	DRM_LOCK(dev);
	gem_obj = drm_gem_object_from_offset(dev, *offset);
	if (gem_obj == NULL) {
		DRM_UNLOCK(dev);
		return (-ENODEV);
	}
	drm_gem_object_reference(gem_obj);
	DRM_UNLOCK(dev);
	vm_obj = cdev_pager_allocate(gem_obj, OBJT_MGTDEVICE,
	    dev->driver->gem_pager_ops, size, nprot,
	    DRM_GEM_MAPPING_MAPOFF(*offset), curthread->td_ucred);
	if (vm_obj == NULL) {
		drm_gem_object_unreference_unlocked(gem_obj);
		return (-EINVAL);
	}
	*offset = DRM_GEM_MAPPING_MAPOFF(*offset);
	*obj_res = vm_obj;
	return (0);
}