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
struct mpc52xx_lpbfifo_request {scalar_t__ pos; scalar_t__ buffer_not_done_cnt; scalar_t__ irq_ticks; scalar_t__ irq_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct mpc52xx_lpbfifo_request* req; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 TYPE_1__ lpbfifo ; 
 int /*<<< orphan*/  mpc52xx_lpbfifo_kick (struct mpc52xx_lpbfifo_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mpc52xx_lpbfifo_submit(struct mpc52xx_lpbfifo_request *req)
{
	unsigned long flags;

	if (!lpbfifo.regs)
		return -ENODEV;

	spin_lock_irqsave(&lpbfifo.lock, flags);

	/* If the req pointer is already set, then a transfer is in progress */
	if (lpbfifo.req) {
		spin_unlock_irqrestore(&lpbfifo.lock, flags);
		return -EBUSY;
	}

	/* Setup the transfer */
	lpbfifo.req = req;
	req->irq_count = 0;
	req->irq_ticks = 0;
	req->buffer_not_done_cnt = 0;
	req->pos = 0;

	mpc52xx_lpbfifo_kick(req);
	spin_unlock_irqrestore(&lpbfifo.lock, flags);
	return 0;
}