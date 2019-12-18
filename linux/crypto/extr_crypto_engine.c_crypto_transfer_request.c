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
struct crypto_engine {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  pump_requests; int /*<<< orphan*/  kworker; int /*<<< orphan*/  busy; int /*<<< orphan*/  queue; int /*<<< orphan*/  running; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int crypto_transfer_request(struct crypto_engine *engine,
				   struct crypto_async_request *req,
				   bool need_pump)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&engine->queue_lock, flags);

	if (!engine->running) {
		spin_unlock_irqrestore(&engine->queue_lock, flags);
		return -ESHUTDOWN;
	}

	ret = crypto_enqueue_request(&engine->queue, req);

	if (!engine->busy && need_pump)
		kthread_queue_work(engine->kworker, &engine->pump_requests);

	spin_unlock_irqrestore(&engine->queue_lock, flags);
	return ret;
}