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
struct mpc52xx_lpbfifo_request {int flags; } ;
struct TYPE_2__ {struct mpc52xx_lpbfifo_request* req; } ;

/* Variables and functions */
 int MPC52XX_LPBFIFO_FLAG_NO_DMA ; 
 int MPC52XX_LPBFIFO_FLAG_WRITE ; 
 TYPE_1__ lpbfifo ; 
 int /*<<< orphan*/  mpc52xx_lpbfifo_bcom_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc52xx_lpbfifo_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mpc52xx_lpbfifo_poll(void)
{
	struct mpc52xx_lpbfifo_request *req = lpbfifo.req;
	int dma = !(req->flags & MPC52XX_LPBFIFO_FLAG_NO_DMA);
	int write = req->flags & MPC52XX_LPBFIFO_FLAG_WRITE;

	/*
	 * For more information, see comments on the "Fat Lady" 
	 */
	if (dma && write)
		mpc52xx_lpbfifo_irq(0, NULL);
	else 
		mpc52xx_lpbfifo_bcom_irq(0, NULL);
}