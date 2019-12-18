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
struct d40_interrupt_lookup {int offset; int /*<<< orphan*/  is_error; scalar_t__ clr; scalar_t__ src; } ;
struct d40_chan {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int il_size; struct d40_interrupt_lookup* il; } ;
struct d40_base {int* regs_interrupt; int /*<<< orphan*/  interrupt_lock; int /*<<< orphan*/  dev; scalar_t__ virtbase; struct d40_chan** lookup_log_chans; struct d40_chan** lookup_phy_chans; TYPE_1__ gen_dmac; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int BITS_PER_LONG ; 
 int D40_PHY_CHAN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  d40_err (int /*<<< orphan*/ ,char*,long,int,int) ; 
 int /*<<< orphan*/  dma_tc_handle (struct d40_chan*) ; 
 long find_next_bit (unsigned long*,int,long) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t d40_handle_interrupt(int irq, void *data)
{
	int i;
	u32 idx;
	u32 row;
	long chan = -1;
	struct d40_chan *d40c;
	unsigned long flags;
	struct d40_base *base = data;
	u32 *regs = base->regs_interrupt;
	struct d40_interrupt_lookup *il = base->gen_dmac.il;
	u32 il_size = base->gen_dmac.il_size;

	spin_lock_irqsave(&base->interrupt_lock, flags);

	/* Read interrupt status of both logical and physical channels */
	for (i = 0; i < il_size; i++)
		regs[i] = readl(base->virtbase + il[i].src);

	for (;;) {

		chan = find_next_bit((unsigned long *)regs,
				     BITS_PER_LONG * il_size, chan + 1);

		/* No more set bits found? */
		if (chan == BITS_PER_LONG * il_size)
			break;

		row = chan / BITS_PER_LONG;
		idx = chan & (BITS_PER_LONG - 1);

		if (il[row].offset == D40_PHY_CHAN)
			d40c = base->lookup_phy_chans[idx];
		else
			d40c = base->lookup_log_chans[il[row].offset + idx];

		if (!d40c) {
			/*
			 * No error because this can happen if something else
			 * in the system is using the channel.
			 */
			continue;
		}

		/* ACK interrupt */
		writel(BIT(idx), base->virtbase + il[row].clr);

		spin_lock(&d40c->lock);

		if (!il[row].is_error)
			dma_tc_handle(d40c);
		else
			d40_err(base->dev, "IRQ chan: %ld offset %d idx %d\n",
				chan, il[row].offset, idx);

		spin_unlock(&d40c->lock);
	}

	spin_unlock_irqrestore(&base->interrupt_lock, flags);

	return IRQ_HANDLED;
}