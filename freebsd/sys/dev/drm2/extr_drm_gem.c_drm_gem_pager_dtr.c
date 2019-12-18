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
struct drm_gem_object {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int /*<<< orphan*/  drm_gem_free_mmap_offset (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (struct drm_gem_object*) ; 

void
drm_gem_pager_dtr(void *handle)
{
	struct drm_gem_object *obj;
	struct drm_device *dev;

	obj = handle;
	dev = obj->dev;

	DRM_LOCK(dev);
	drm_gem_free_mmap_offset(obj);
	drm_gem_object_unreference(obj);
	DRM_UNLOCK(dev);
}