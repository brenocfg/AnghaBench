#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;
struct vdc_port {TYPE_1__ vio; TYPE_2__* disk; int /*<<< orphan*/  ldc_reset_timer_work; int /*<<< orphan*/  ldc_reset_work; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_stop_hw_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct vdc_port* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vdc_port*) ; 
 int /*<<< orphan*/  put_disk (TYPE_2__*) ; 
 int /*<<< orphan*/  vdc_free_tx_ring (struct vdc_port*) ; 
 int /*<<< orphan*/  vio_ldc_free (TYPE_1__*) ; 

__attribute__((used)) static int vdc_port_remove(struct vio_dev *vdev)
{
	struct vdc_port *port = dev_get_drvdata(&vdev->dev);

	if (port) {
		blk_mq_stop_hw_queues(port->disk->queue);

		flush_work(&port->ldc_reset_work);
		cancel_delayed_work_sync(&port->ldc_reset_timer_work);
		del_timer_sync(&port->vio.timer);

		del_gendisk(port->disk);
		cleanup_queue(port->disk->queue);
		put_disk(port->disk);
		port->disk = NULL;

		vdc_free_tx_ring(port);
		vio_ldc_free(&port->vio);

		dev_set_drvdata(&vdev->dev, NULL);

		kfree(port);
	}
	return 0;
}