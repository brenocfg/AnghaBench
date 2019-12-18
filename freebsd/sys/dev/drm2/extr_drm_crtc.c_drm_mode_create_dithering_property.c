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
struct drm_property {int dummy; } ;
struct TYPE_2__ {struct drm_property* dithering_mode_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dithering_mode_enum_list ; 
 struct drm_property* drm_property_create_enum (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_mode_create_dithering_property(struct drm_device *dev)
{
	struct drm_property *dithering_mode;

	if (dev->mode_config.dithering_mode_property)
		return 0;

	dithering_mode =
		drm_property_create_enum(dev, 0, "dithering",
				drm_dithering_mode_enum_list,
				    ARRAY_SIZE(drm_dithering_mode_enum_list));
	dev->mode_config.dithering_mode_property = dithering_mode;

	return 0;
}