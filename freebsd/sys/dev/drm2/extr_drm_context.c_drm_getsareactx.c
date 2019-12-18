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
struct drm_local_map {scalar_t__ handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {scalar_t__ max_context; struct drm_local_map** context_sareas; } ;
struct drm_ctx_priv_map {unsigned int ctx_id; void* handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int EINVAL ; 

int drm_getsareactx(struct drm_device *dev, void *data,
		    struct drm_file *file_priv)
{
	struct drm_ctx_priv_map *request = data;
	struct drm_local_map *map;

	DRM_LOCK(dev);
	if (dev->max_context < 0 ||
	    request->ctx_id >= (unsigned) dev->max_context) {
		DRM_UNLOCK(dev);
		return EINVAL;
	}

	map = dev->context_sareas[request->ctx_id];
	DRM_UNLOCK(dev);

	request->handle = (void *)map->handle;

	return 0;
}