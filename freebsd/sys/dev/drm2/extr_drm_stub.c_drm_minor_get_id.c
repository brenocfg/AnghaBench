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
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_MINOR_CONTROL ; 
 int DRM_MINOR_RENDER ; 
 int EINVAL ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_minor_get_id(struct drm_device *dev, int type)
{
	int new_id;

	new_id = device_get_unit(dev->dev);

	if (new_id >= 64)
		return -EINVAL;

	if (type == DRM_MINOR_CONTROL) {
		new_id += 64;
	} else if (type == DRM_MINOR_RENDER) {
		new_id += 128;
	}

	return new_id;
}