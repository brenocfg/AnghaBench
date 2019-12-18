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
struct TYPE_2__ {void* callback_param; int /*<<< orphan*/  (* callback ) (void*) ;} ;
struct xilinx_dma_tx_descriptor {TYPE_1__ async_tx; } ;
struct xilinx_dma_chan {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  (* dma_async_tx_callback ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void xilinx_dma_chan_handle_cyclic(struct xilinx_dma_chan *chan,
					  struct xilinx_dma_tx_descriptor *desc,
					  unsigned long *flags)
{
	dma_async_tx_callback callback;
	void *callback_param;

	callback = desc->async_tx.callback;
	callback_param = desc->async_tx.callback_param;
	if (callback) {
		spin_unlock_irqrestore(&chan->lock, *flags);
		callback(callback_param);
		spin_lock_irqsave(&chan->lock, *flags);
	}
}