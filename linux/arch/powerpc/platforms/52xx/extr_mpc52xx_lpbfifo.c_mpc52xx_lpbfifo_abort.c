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
struct mpc52xx_lpbfifo_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct mpc52xx_lpbfifo_request* req; scalar_t__ regs; int /*<<< orphan*/  bcom_tx_task; int /*<<< orphan*/  bcom_rx_task; } ;

/* Variables and functions */
 scalar_t__ LPBFIFO_REG_ENABLE ; 
 int /*<<< orphan*/  bcom_gen_bd_rx_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_gen_bd_tx_reset (int /*<<< orphan*/ ) ; 
 TYPE_1__ lpbfifo ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mpc52xx_lpbfifo_abort(struct mpc52xx_lpbfifo_request *req)
{
	unsigned long flags;

	spin_lock_irqsave(&lpbfifo.lock, flags);
	if (lpbfifo.req == req) {
		/* Put it into reset and clear the state */
		bcom_gen_bd_rx_reset(lpbfifo.bcom_rx_task);
		bcom_gen_bd_tx_reset(lpbfifo.bcom_tx_task);
		out_be32(lpbfifo.regs + LPBFIFO_REG_ENABLE, 0x01010000);
		lpbfifo.req = NULL;
	}
	spin_unlock_irqrestore(&lpbfifo.lock, flags);
}