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
struct request_queue {struct ps3_storage_device* queuedata; } ;
struct ps3disk_private {int /*<<< orphan*/  lock; } ;
struct ps3_storage_device {int /*<<< orphan*/  sbd; } ;
struct blk_mq_queue_data {int /*<<< orphan*/  rq; } ;
struct blk_mq_hw_ctx {struct request_queue* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_start_request (int /*<<< orphan*/ ) ; 
 struct ps3disk_private* ps3_system_bus_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps3disk_do_request (struct ps3_storage_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t ps3disk_queue_rq(struct blk_mq_hw_ctx *hctx,
				     const struct blk_mq_queue_data *bd)
{
	struct request_queue *q = hctx->queue;
	struct ps3_storage_device *dev = q->queuedata;
	struct ps3disk_private *priv = ps3_system_bus_get_drvdata(&dev->sbd);
	blk_status_t ret;

	blk_mq_start_request(bd->rq);

	spin_lock_irq(&priv->lock);
	ret = ps3disk_do_request(dev, bd->rq);
	spin_unlock_irq(&priv->lock);

	return ret;
}