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
struct tegra_bo {int /*<<< orphan*/  gem_obj; int /*<<< orphan*/  cdev_pager; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  gem_pager_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_DRIVER ; 
 int EINVAL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OBJT_MGTDEVICE ; 
 int /*<<< orphan*/  cdev_pager_allocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_gem_create_mmap_offset (int /*<<< orphan*/ *) ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  drm_gem_object_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct tegra_bo*,int /*<<< orphan*/ ) ; 
 struct tegra_bo* malloc (int,int /*<<< orphan*/ ,int) ; 
 size_t round_page (size_t) ; 
 int tegra_bo_alloc (struct drm_device*,struct tegra_bo*) ; 
 int /*<<< orphan*/  tegra_bo_free_object (int /*<<< orphan*/ *) ; 

int
tegra_bo_create(struct drm_device *drm, size_t size, struct tegra_bo **res_bo)
{
	struct tegra_bo *bo;
	int rv;

	if (size <= 0)
		return (-EINVAL);

	bo = malloc(sizeof(*bo), DRM_MEM_DRIVER, M_WAITOK | M_ZERO);

	size = round_page(size);
	rv = drm_gem_object_init(drm, &bo->gem_obj, size);
	if (rv != 0) {
		free(bo, DRM_MEM_DRIVER);
		return (rv);
	}
	rv = drm_gem_create_mmap_offset(&bo->gem_obj);
	if (rv != 0) {
		drm_gem_object_release(&bo->gem_obj);
		free(bo, DRM_MEM_DRIVER);
		return (rv);
	}

	bo->cdev_pager = cdev_pager_allocate(&bo->gem_obj, OBJT_MGTDEVICE,
	    drm->driver->gem_pager_ops, size, 0, 0, NULL);
	rv = tegra_bo_alloc(drm, bo);
	if (rv != 0) {
		tegra_bo_free_object(&bo->gem_obj);
		return (rv);
	}

	*res_bo = bo;
	return (0);
}