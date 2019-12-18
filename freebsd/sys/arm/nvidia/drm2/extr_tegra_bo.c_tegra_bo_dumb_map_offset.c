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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
struct drm_gem_object {TYPE_1__ map_list; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_GEM_MAPPING_KEY ; 
 int DRM_GEM_MAPPING_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int drm_gem_create_mmap_offset (struct drm_gem_object*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (struct drm_gem_object*) ; 

__attribute__((used)) static int
tegra_bo_dumb_map_offset(struct drm_file *file_priv,
    struct drm_device *drm_dev, uint32_t handle, uint64_t *offset)
{
	struct drm_gem_object *gem_obj;
	int rv;

	DRM_LOCK(drm_dev);
	gem_obj = drm_gem_object_lookup(drm_dev, file_priv, handle);
	if (gem_obj == NULL) {
		device_printf(drm_dev->dev, "Object not found\n");
		DRM_UNLOCK(drm_dev);
		return (-EINVAL);
	}
	rv = drm_gem_create_mmap_offset(gem_obj);
	if (rv != 0)
		goto fail;

	*offset = DRM_GEM_MAPPING_OFF(gem_obj->map_list.key) |
	    DRM_GEM_MAPPING_KEY;

	drm_gem_object_unreference(gem_obj);
	DRM_UNLOCK(drm_dev);
	return (0);

fail:
	drm_gem_object_unreference(gem_obj);
	DRM_UNLOCK(drm_dev);
	return (rv);
}