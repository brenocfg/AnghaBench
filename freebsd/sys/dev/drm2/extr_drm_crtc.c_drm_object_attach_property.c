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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct drm_property {TYPE_2__ base; } ;
struct drm_mode_object {TYPE_1__* properties; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int count; int /*<<< orphan*/ * values; int /*<<< orphan*/ * ids; } ;

/* Variables and functions */
 int DRM_OBJECT_MAX_PROPERTY ; 
 int /*<<< orphan*/  DRM_WARNING (char*,int /*<<< orphan*/ ) ; 

void drm_object_attach_property(struct drm_mode_object *obj,
				struct drm_property *property,
				uint64_t init_val)
{
	int count = obj->properties->count;

	if (count == DRM_OBJECT_MAX_PROPERTY) {
		DRM_WARNING("Failed to attach object property (type: 0x%x). Please "
			"increase DRM_OBJECT_MAX_PROPERTY by 1 for each time "
			"you see this message on the same object type.\n",
			obj->type);
		return;
	}

	obj->properties->ids[count] = property->base.id;
	obj->properties->values[count] = init_val;
	obj->properties->count++;
}