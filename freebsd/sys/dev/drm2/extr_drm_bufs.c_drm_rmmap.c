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
struct drm_local_map {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int drm_rmmap_locked (struct drm_device*,struct drm_local_map*) ; 

int drm_rmmap(struct drm_device *dev, struct drm_local_map *map)
{
	int ret;

	DRM_LOCK(dev);
	ret = drm_rmmap_locked(dev, map);
	DRM_UNLOCK(dev);

	return ret;
}