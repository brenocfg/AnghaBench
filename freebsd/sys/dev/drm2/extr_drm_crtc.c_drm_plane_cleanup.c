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
struct drm_plane {int /*<<< orphan*/  head; int /*<<< orphan*/  base; int /*<<< orphan*/  format_types; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  num_plane; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_KMS ; 
 int /*<<< orphan*/  drm_mode_object_put (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void drm_plane_cleanup(struct drm_plane *plane)
{
	struct drm_device *dev = plane->dev;

	sx_xlock(&dev->mode_config.mutex);
	free(plane->format_types, DRM_MEM_KMS);
	drm_mode_object_put(dev, &plane->base);
	/* if not added to a list, it must be a private plane */
	if (!list_empty(&plane->head)) {
		list_del(&plane->head);
		dev->mode_config.num_plane--;
	}
	sx_xunlock(&dev->mode_config.mutex);
}