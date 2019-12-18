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
struct drm_device {scalar_t__ num_crtcs; int /*<<< orphan*/  vblank_time_lock; int /*<<< orphan*/  vbl_lock; int /*<<< orphan*/  _vblank_time; int /*<<< orphan*/  vblank_inmodeset; int /*<<< orphan*/  last_vblank_wait; int /*<<< orphan*/  last_vblank; int /*<<< orphan*/  vblank_enabled; int /*<<< orphan*/  vblank_refcount; int /*<<< orphan*/  _vblank_count; int /*<<< orphan*/  vblank_disable_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_VBLANK ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vblank_disable_fn (struct drm_device*) ; 

void drm_vblank_cleanup(struct drm_device *dev)
{
	/* Bail if the driver didn't call drm_vblank_init() */
	if (dev->num_crtcs == 0)
		return;

	callout_stop(&dev->vblank_disable_callout);

	vblank_disable_fn(dev);

	free(dev->_vblank_count, DRM_MEM_VBLANK);
	free(dev->vblank_refcount, DRM_MEM_VBLANK);
	free(dev->vblank_enabled, DRM_MEM_VBLANK);
	free(dev->last_vblank, DRM_MEM_VBLANK);
	free(dev->last_vblank_wait, DRM_MEM_VBLANK);
	free(dev->vblank_inmodeset, DRM_MEM_VBLANK);
	free(dev->_vblank_time, DRM_MEM_VBLANK);

	mtx_destroy(&dev->vbl_lock);
	mtx_destroy(&dev->vblank_time_lock);

	dev->num_crtcs = 0;
}