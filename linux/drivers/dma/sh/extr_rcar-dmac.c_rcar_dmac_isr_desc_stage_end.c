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
struct rcar_dmac_desc {int /*<<< orphan*/  cyclic; } ;
struct TYPE_2__ {struct rcar_dmac_desc* running; } ;
struct rcar_dmac_chan {TYPE_1__ desc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  RCAR_DMACHCRB ; 
 unsigned int RCAR_DMACHCRB_DPTR_MASK ; 
 unsigned int RCAR_DMACHCRB_DPTR_SHIFT ; 
 int /*<<< orphan*/  RCAR_DMADPCR ; 
 int /*<<< orphan*/  RCAR_DMADPCR_DIPT (unsigned int) ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int rcar_dmac_chan_read (struct rcar_dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_dmac_chan_write (struct rcar_dmac_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rcar_dmac_isr_desc_stage_end(struct rcar_dmac_chan *chan)
{
	struct rcar_dmac_desc *desc = chan->desc.running;
	unsigned int stage;

	if (WARN_ON(!desc || !desc->cyclic)) {
		/*
		 * This should never happen, there should always be a running
		 * cyclic descriptor when a descriptor stage end interrupt is
		 * triggered. Warn and return.
		 */
		return IRQ_NONE;
	}

	/* Program the interrupt pointer to the next stage. */
	stage = (rcar_dmac_chan_read(chan, RCAR_DMACHCRB) &
		 RCAR_DMACHCRB_DPTR_MASK) >> RCAR_DMACHCRB_DPTR_SHIFT;
	rcar_dmac_chan_write(chan, RCAR_DMADPCR, RCAR_DMADPCR_DIPT(stage));

	return IRQ_WAKE_THREAD;
}