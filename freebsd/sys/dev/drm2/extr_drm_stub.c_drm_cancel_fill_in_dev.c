#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_driver {int driver_features; } ;
struct drm_device {int /*<<< orphan*/  pcir_lock; int /*<<< orphan*/  ctxlist_mutex; int /*<<< orphan*/  dev_struct_lock; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  count_lock; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  map_hash; TYPE_2__* agp; struct drm_driver* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  ai_aperture_size; int /*<<< orphan*/  ai_aperture_base; } ;
struct TYPE_4__ {scalar_t__ agp_mtrr; TYPE_1__ agp_info; } ;

/* Variables and functions */
 int DRIVER_GEM ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  DRM_MEM_AGPLISTS ; 
 int /*<<< orphan*/  DRM_MTRR_WC ; 
 scalar_t__ drm_core_has_AGP (struct drm_device*) ; 
 scalar_t__ drm_core_has_MTRR (struct drm_device*) ; 
 int /*<<< orphan*/  drm_ctxbitmap_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_gem_destroy (struct drm_device*) ; 
 int /*<<< orphan*/  drm_ht_remove (int /*<<< orphan*/ *) ; 
 int drm_mtrr_del (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sysctl_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

void drm_cancel_fill_in_dev(struct drm_device *dev)
{
	struct drm_driver *driver;

	driver = dev->driver;

	drm_sysctl_cleanup(dev);
	if (driver->driver_features & DRIVER_GEM)
		drm_gem_destroy(dev);
	drm_ctxbitmap_cleanup(dev);

	if (drm_core_has_MTRR(dev) && drm_core_has_AGP(dev) &&
	    dev->agp && dev->agp->agp_mtrr >= 0) {
		int retval;
		retval = drm_mtrr_del(dev->agp->agp_mtrr,
				  dev->agp->agp_info.ai_aperture_base,
				  dev->agp->agp_info.ai_aperture_size,
				  DRM_MTRR_WC);
		DRM_DEBUG("mtrr_del=%d\n", retval);
	}
	free(dev->agp, DRM_MEM_AGPLISTS);
	dev->agp = NULL;

	drm_ht_remove(&dev->map_hash);

	mtx_destroy(&dev->irq_lock);
	mtx_destroy(&dev->count_lock);
	mtx_destroy(&dev->event_lock);
	sx_destroy(&dev->dev_struct_lock);
	mtx_destroy(&dev->ctxlist_mutex);
	mtx_destroy(&dev->pcir_lock);
}