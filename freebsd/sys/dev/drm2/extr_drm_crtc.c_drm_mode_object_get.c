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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_mode_object {int id; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc_names; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int drm_gem_name_create (int /*<<< orphan*/ *,struct drm_mode_object*,int*) ; 

__attribute__((used)) static int drm_mode_object_get(struct drm_device *dev,
			       struct drm_mode_object *obj, uint32_t obj_type)
{
	int new_id = 0;
	int ret;

	ret = drm_gem_name_create(&dev->mode_config.crtc_names, obj, &new_id);
	if (ret)
		return ret;

	obj->id = new_id;
	obj->type = obj_type;
	return 0;
}