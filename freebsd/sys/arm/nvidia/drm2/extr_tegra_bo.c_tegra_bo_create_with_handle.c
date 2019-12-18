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
typedef  int /*<<< orphan*/  uint32_t ;
struct tegra_bo {int /*<<< orphan*/  gem_obj; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (int /*<<< orphan*/ *) ; 
 int tegra_bo_create (struct drm_device*,size_t,struct tegra_bo**) ; 
 int /*<<< orphan*/  tegra_bo_free_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tegra_bo_create_with_handle(struct drm_file *file, struct drm_device *drm,
    size_t size, uint32_t *handle, struct tegra_bo **res_bo)
{
	int rv;
	struct tegra_bo *bo;

	rv = tegra_bo_create(drm, size, &bo);
	if (rv != 0)
		return (rv);

	rv = drm_gem_handle_create(file, &bo->gem_obj, handle);
	if (rv != 0) {
		tegra_bo_free_object(&bo->gem_obj);
		drm_gem_object_release(&bo->gem_obj);
		return (rv);
	}

	drm_gem_object_unreference_unlocked(&bo->gem_obj);

	*res_bo = bo;
	return (0);
}