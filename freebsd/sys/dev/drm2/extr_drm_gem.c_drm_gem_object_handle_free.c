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
struct drm_gem_object {int /*<<< orphan*/  name; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  object_names; } ;

/* Variables and functions */
 struct drm_gem_object* drm_gem_names_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (struct drm_gem_object*) ; 

void drm_gem_object_handle_free(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	struct drm_gem_object *obj1;

	if (obj->name) {
		obj1 = drm_gem_names_remove(&dev->object_names, obj->name);
		obj->name = 0;
		drm_gem_object_unreference(obj1);
	}
}