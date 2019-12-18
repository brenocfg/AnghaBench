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
struct drm_gem_object {struct drm_device* dev; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* gem_free_object ) (struct drm_gem_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_LOCK_ASSERT (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_gem_object*) ; 

void
drm_gem_object_free(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;

	DRM_LOCK_ASSERT(dev);
	if (dev->driver->gem_free_object != NULL)
		dev->driver->gem_free_object(obj);
}