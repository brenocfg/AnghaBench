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
struct mpc52xx_lpbfifo_request {scalar_t__ defer_xfer_start; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ regs; struct mpc52xx_lpbfifo_request* req; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ LPBFIFO_REG_PACKET_SIZE ; 
 TYPE_1__ lpbfifo ; 
 int /*<<< orphan*/  out_8 (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mpc52xx_lpbfifo_start_xfer(struct mpc52xx_lpbfifo_request *req)
{
	unsigned long flags;

	if (!lpbfifo.regs)
		return -ENODEV;

	spin_lock_irqsave(&lpbfifo.lock, flags);

	/*
	 * If the req pointer is already set and a transfer was
	 * started on submit, then this transfer is in progress
	 */
	if (lpbfifo.req && !lpbfifo.req->defer_xfer_start) {
		spin_unlock_irqrestore(&lpbfifo.lock, flags);
		return -EBUSY;
	}

	/*
	 * If the req was previously submitted but not
	 * started, start it now
	 */
	if (lpbfifo.req && lpbfifo.req == req &&
	    lpbfifo.req->defer_xfer_start) {
		out_8(lpbfifo.regs + LPBFIFO_REG_PACKET_SIZE, 0x01);
	}

	spin_unlock_irqrestore(&lpbfifo.lock, flags);
	return 0;
}