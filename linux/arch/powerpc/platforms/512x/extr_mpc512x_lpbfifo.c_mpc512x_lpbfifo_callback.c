#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mpc512x_lpbfifo_request {scalar_t__ dir; int /*<<< orphan*/  (* callback ) (struct mpc512x_lpbfifo_request*) ;int /*<<< orphan*/  size; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_6__ {int wait_lpbfifo_callback; int /*<<< orphan*/  lock; struct mpc512x_lpbfifo_request* req; int /*<<< orphan*/  wait_lpbfifo_irq; int /*<<< orphan*/  ram_bus_addr; TYPE_2__* chan; int /*<<< orphan*/  regs; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 scalar_t__ MPC512X_LPBFIFO_REQ_DIR_WRITE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ lpbfifo ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mpc512x_lpbfifo_request*) ; 

__attribute__((used)) static void mpc512x_lpbfifo_callback(void *param)
{
	unsigned long flags;
	struct mpc512x_lpbfifo_request *req = NULL;
	enum dma_data_direction dir;

	spin_lock_irqsave(&lpbfifo.lock, flags);

	if (!lpbfifo.regs) {
		spin_unlock_irqrestore(&lpbfifo.lock, flags);
		return;
	}

	req = lpbfifo.req;
	if (!req) {
		pr_err("bogus LPBFIFO callback\n");
		spin_unlock_irqrestore(&lpbfifo.lock, flags);
		return;
	}

	/* Release the mapping */
	if (req->dir == MPC512X_LPBFIFO_REQ_DIR_WRITE)
		dir = DMA_TO_DEVICE;
	else
		dir = DMA_FROM_DEVICE;
	dma_unmap_single(lpbfifo.chan->device->dev,
			lpbfifo.ram_bus_addr, req->size, dir);

	lpbfifo.wait_lpbfifo_callback = false;

	if (!lpbfifo.wait_lpbfifo_irq) {
		/* Transfer is finished, set the FIFO as idle */
		lpbfifo.req = NULL;

		spin_unlock_irqrestore(&lpbfifo.lock, flags);

		if (req->callback)
			req->callback(req);
	} else {
		spin_unlock_irqrestore(&lpbfifo.lock, flags);
	}
}