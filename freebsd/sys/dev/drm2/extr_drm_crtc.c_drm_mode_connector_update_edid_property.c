#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct edid {int extensions; } ;
struct TYPE_5__ {int /*<<< orphan*/  edid_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_connector {TYPE_3__* edid_blob_ptr; int /*<<< orphan*/  base; struct drm_device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_2__ base; } ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int EINVAL ; 
 int drm_object_property_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* drm_property_create_blob (struct drm_device*,int,struct edid*) ; 
 int /*<<< orphan*/  drm_property_destroy_blob (struct drm_device*,TYPE_3__*) ; 

int drm_mode_connector_update_edid_property(struct drm_connector *connector,
					    struct edid *edid)
{
	struct drm_device *dev = connector->dev;
	int ret, size;

	if (connector->edid_blob_ptr)
		drm_property_destroy_blob(dev, connector->edid_blob_ptr);

	/* Delete edid, when there is none. */
	if (!edid) {
		connector->edid_blob_ptr = NULL;
		ret = drm_object_property_set_value(&connector->base, dev->mode_config.edid_property, 0);
		return ret;
	}

	size = EDID_LENGTH * (1 + edid->extensions);
	connector->edid_blob_ptr = drm_property_create_blob(connector->dev,
							    size, edid);
	if (!connector->edid_blob_ptr)
		return -EINVAL;

	ret = drm_object_property_set_value(&connector->base,
					       dev->mode_config.edid_property,
					       connector->edid_blob_ptr->base.id);

	return ret;
}