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
typedef  scalar_t__ uint32_t ;
struct drm_mode_object {scalar_t__ type; scalar_t__ id; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc_names; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 struct drm_mode_object* drm_gem_name_ref (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

struct drm_mode_object *drm_mode_object_find(struct drm_device *dev,
		uint32_t id, uint32_t type)
{
	struct drm_mode_object *obj = NULL;

	obj = drm_gem_name_ref(&dev->mode_config.crtc_names, id, NULL);
	if (!obj || (obj->type != type) || (obj->id != id))
		obj = NULL;

	return obj;
}