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
typedef  int u32 ;
struct TYPE_2__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQENABLE_L0 ; 
 int /*<<< orphan*/  IRQSTATUS_L0 ; 
 int /*<<< orphan*/  dma_chan_lock ; 
 scalar_t__ dma_omap1 () ; 
 TYPE_1__* p ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void omap2_enable_irq_lch(int lch)
{
	u32 val;
	unsigned long flags;

	if (dma_omap1())
		return;

	spin_lock_irqsave(&dma_chan_lock, flags);
	/* clear IRQ STATUS */
	p->dma_write(1 << lch, IRQSTATUS_L0, lch);
	/* Enable interrupt */
	val = p->dma_read(IRQENABLE_L0, lch);
	val |= 1 << lch;
	p->dma_write(val, IRQENABLE_L0, lch);
	spin_unlock_irqrestore(&dma_chan_lock, flags);
}