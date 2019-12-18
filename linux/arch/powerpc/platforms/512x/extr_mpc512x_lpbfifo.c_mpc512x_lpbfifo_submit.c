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
struct mpc512x_lpbfifo_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_1__ lpbfifo ; 
 int mpc512x_lpbfifo_submit_locked (struct mpc512x_lpbfifo_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mpc512x_lpbfifo_submit(struct mpc512x_lpbfifo_request *req)
{
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&lpbfifo.lock, flags);
	ret = mpc512x_lpbfifo_submit_locked(req);
	spin_unlock_irqrestore(&lpbfifo.lock, flags);

	return ret;
}