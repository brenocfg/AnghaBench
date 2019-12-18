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
struct vio_driver {int (* probe ) (struct vio_dev*,struct vio_device_id const*) ;int /*<<< orphan*/  no_irq; int /*<<< orphan*/  id_table; } ;
struct vio_device_id {int dummy; } ;
struct vio_dev {scalar_t__ tx_irq; unsigned long tx_ino; scalar_t__ rx_irq; unsigned long rx_ino; int /*<<< orphan*/  cdev_handle; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct vio_dev*,struct vio_device_id const*) ; 
 void* sun4v_build_virq (int /*<<< orphan*/ ,unsigned long) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 
 struct vio_driver* to_vio_driver (int /*<<< orphan*/ ) ; 
 struct vio_device_id* vio_match_device (int /*<<< orphan*/ ,struct vio_dev*) ; 

__attribute__((used)) static int vio_device_probe(struct device *dev)
{
	struct vio_dev *vdev = to_vio_dev(dev);
	struct vio_driver *drv = to_vio_driver(dev->driver);
	const struct vio_device_id *id;

	if (!drv->probe)
		return -ENODEV;

	id = vio_match_device(drv->id_table, vdev);
	if (!id)
		return -ENODEV;

	/* alloc irqs (unless the driver specified not to) */
	if (!drv->no_irq) {
		if (vdev->tx_irq == 0 && vdev->tx_ino != ~0UL)
			vdev->tx_irq = sun4v_build_virq(vdev->cdev_handle,
							vdev->tx_ino);

		if (vdev->rx_irq == 0 && vdev->rx_ino != ~0UL)
			vdev->rx_irq = sun4v_build_virq(vdev->cdev_handle,
							vdev->rx_ino);
	}

	return drv->probe(vdev, id);
}