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
typedef  int /*<<< orphan*/  u32 ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int /*<<< orphan*/  object_names; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct drm_gem_object* drm_gem_name_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*)) ; 
 scalar_t__ drm_gem_object_reference ; 

struct drm_gem_object *
drm_gem_object_lookup(struct drm_device *dev, struct drm_file *filp,
		      u32 handle)
{
	struct drm_gem_object *obj;

	obj = drm_gem_name_ref(&filp->object_names, handle,
	    (void (*)(void *))drm_gem_object_reference);

	return obj;
}