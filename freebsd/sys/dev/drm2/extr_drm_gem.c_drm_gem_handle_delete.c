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
typedef  int /*<<< orphan*/  u32 ;
struct drm_gem_object {struct drm_device* dev; } ;
struct drm_file {int /*<<< orphan*/  object_names; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* gem_close_object ) (struct drm_gem_object*,struct drm_file*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct drm_gem_object* drm_gem_names_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_handle_unreference_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_remove_prime_handles (struct drm_gem_object*,struct drm_file*) ; 
 int /*<<< orphan*/  stub1 (struct drm_gem_object*,struct drm_file*) ; 

int
drm_gem_handle_delete(struct drm_file *filp, u32 handle)
{
	struct drm_device *dev;
	struct drm_gem_object *obj;

	obj = drm_gem_names_remove(&filp->object_names, handle);
	if (obj == NULL) {
		return -EINVAL;
	}
	dev = obj->dev;

#if defined(FREEBSD_NOTYET)
	drm_gem_remove_prime_handles(obj, filp);
#endif

	if (dev->driver->gem_close_object)
		dev->driver->gem_close_object(obj, filp);
	drm_gem_object_handle_unreference_unlocked(obj);

	return 0;
}