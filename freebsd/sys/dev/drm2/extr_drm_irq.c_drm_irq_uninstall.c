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
struct drm_device {int irq_enabled; int num_crtcs; TYPE_2__* driver; int /*<<< orphan*/  irqh; int /*<<< orphan*/  irqr; int /*<<< orphan*/  dev; int /*<<< orphan*/  vbl_lock; int /*<<< orphan*/ * last_vblank; scalar_t__* vblank_enabled; int /*<<< orphan*/ * _vblank_count; } ;
struct TYPE_4__ {TYPE_1__* bus; int /*<<< orphan*/  (* irq_uninstall ) (struct drm_device*) ;int /*<<< orphan*/  (* get_vblank_counter ) (struct drm_device*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* free_irq ) (struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_HAVE_IRQ ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_WAKEUP (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_to_irq (struct drm_device*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct drm_device*) ; 
 int /*<<< orphan*/  stub3 (struct drm_device*) ; 

int drm_irq_uninstall(struct drm_device *dev)
{
	int irq_enabled, i;

	if (!drm_core_check_feature(dev, DRIVER_HAVE_IRQ))
		return -EINVAL;

	DRM_LOCK(dev);
	irq_enabled = dev->irq_enabled;
	dev->irq_enabled = 0;
	DRM_UNLOCK(dev);

	/*
	 * Wake up any waiters so they don't hang.
	 */
	if (dev->num_crtcs) {
		mtx_lock(&dev->vbl_lock);
		for (i = 0; i < dev->num_crtcs; i++) {
			DRM_WAKEUP(&dev->_vblank_count[i]);
			dev->vblank_enabled[i] = 0;
			dev->last_vblank[i] =
				dev->driver->get_vblank_counter(dev, i);
		}
		mtx_unlock(&dev->vbl_lock);
	}

	if (!irq_enabled)
		return -EINVAL;

	DRM_DEBUG("irq=%d\n", drm_dev_to_irq(dev));

	if (dev->driver->irq_uninstall)
		dev->driver->irq_uninstall(dev);

	bus_teardown_intr(dev->dev, dev->irqr, dev->irqh);
	dev->driver->bus->free_irq(dev);

	return 0;
}