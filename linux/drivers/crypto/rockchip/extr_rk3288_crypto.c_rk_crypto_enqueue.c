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
struct rk_crypto_info {int busy; int /*<<< orphan*/  queue_task; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rk_crypto_enqueue(struct rk_crypto_info *dev,
			      struct crypto_async_request *async_req)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&dev->lock, flags);
	ret = crypto_enqueue_request(&dev->queue, async_req);
	if (dev->busy) {
		spin_unlock_irqrestore(&dev->lock, flags);
		return ret;
	}
	dev->busy = true;
	spin_unlock_irqrestore(&dev->lock, flags);
	tasklet_schedule(&dev->queue_task);

	return ret;
}