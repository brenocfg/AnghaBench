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
struct drm_driver {int /*<<< orphan*/  dumb_destroy; int /*<<< orphan*/  dumb_map_offset; int /*<<< orphan*/  dumb_create; int /*<<< orphan*/ * gem_pager_ops; int /*<<< orphan*/  gem_free_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_bo_dumb_create ; 
 int /*<<< orphan*/  tegra_bo_dumb_destroy ; 
 int /*<<< orphan*/  tegra_bo_dumb_map_offset ; 
 int /*<<< orphan*/  tegra_bo_free_object ; 
 int /*<<< orphan*/  tegra_gem_pager_ops ; 

void
tegra_bo_driver_register(struct drm_driver *drm_drv)
{
	drm_drv->gem_free_object = tegra_bo_free_object;
	drm_drv->gem_pager_ops = &tegra_gem_pager_ops;
	drm_drv->dumb_create = tegra_bo_dumb_create;
	drm_drv->dumb_map_offset = tegra_bo_dumb_map_offset;
	drm_drv->dumb_destroy = tegra_bo_dumb_destroy;
}