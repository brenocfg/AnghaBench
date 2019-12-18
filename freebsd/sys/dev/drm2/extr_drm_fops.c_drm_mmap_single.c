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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
struct vm_object {int dummy; } ;
struct drm_device {TYPE_1__* driver; int /*<<< orphan*/ * drm_ttm_bdev; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int driver_features; } ;

/* Variables and functions */
 int DRIVER_GEM ; 
 int ENODEV ; 
 int drm_gem_mmap_single (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vm_object**,int) ; 
 struct drm_device* drm_get_device_from_kdev (struct cdev*) ; 
 int ttm_bo_mmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vm_object**,int) ; 

int
drm_mmap_single(struct cdev *kdev, vm_ooffset_t *offset, vm_size_t size,
    struct vm_object **obj_res, int nprot)
{
	struct drm_device *dev;

	dev = drm_get_device_from_kdev(kdev);
	if (dev->drm_ttm_bdev != NULL) {
		return (-ttm_bo_mmap_single(dev->drm_ttm_bdev, offset, size,
		    obj_res, nprot));
	} else if ((dev->driver->driver_features & DRIVER_GEM) != 0) {
		return (-drm_gem_mmap_single(dev, offset, size, obj_res, nprot));
	} else {
		return (ENODEV);
	}
}