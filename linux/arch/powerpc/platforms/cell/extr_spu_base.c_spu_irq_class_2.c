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
struct TYPE_2__ {int /*<<< orphan*/  class2_intr; } ;
struct spu {int /*<<< orphan*/  register_lock; TYPE_1__ stats; int /*<<< orphan*/  (* wbox_callback ) (struct spu*) ;int /*<<< orphan*/  (* mfc_callback ) (struct spu*) ;int /*<<< orphan*/  (* stop_callback ) (struct spu*,int) ;int /*<<< orphan*/  (* ibox_callback ) (struct spu*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned long CLASS2_MAILBOX_INTR ; 
 unsigned long CLASS2_MAILBOX_THRESHOLD_INTR ; 
 unsigned long CLASS2_SPU_DMA_TAG_GROUP_COMPLETE_INTR ; 
 unsigned long CLASS2_SPU_HALT_INTR ; 
 unsigned long CLASS2_SPU_STOP_INTR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_int_mask_and (struct spu*,int,unsigned long) ; 
 unsigned long spu_int_mask_get (struct spu*,int) ; 
 int /*<<< orphan*/  spu_int_stat_clear (struct spu*,int,unsigned long) ; 
 unsigned long spu_int_stat_get (struct spu*,int) ; 
 int /*<<< orphan*/  stub1 (struct spu*) ; 
 int /*<<< orphan*/  stub2 (struct spu*,int) ; 
 int /*<<< orphan*/  stub3 (struct spu*,int) ; 
 int /*<<< orphan*/  stub4 (struct spu*) ; 
 int /*<<< orphan*/  stub5 (struct spu*) ; 

__attribute__((used)) static irqreturn_t
spu_irq_class_2(int irq, void *data)
{
	struct spu *spu;
	unsigned long stat;
	unsigned long mask;
	const int mailbox_intrs =
		CLASS2_MAILBOX_THRESHOLD_INTR | CLASS2_MAILBOX_INTR;

	spu = data;
	spin_lock(&spu->register_lock);
	stat = spu_int_stat_get(spu, 2);
	mask = spu_int_mask_get(spu, 2);
	/* ignore interrupts we're not waiting for */
	stat &= mask;
	/* mailbox interrupts are level triggered. mask them now before
	 * acknowledging */
	if (stat & mailbox_intrs)
		spu_int_mask_and(spu, 2, ~(stat & mailbox_intrs));
	/* acknowledge all interrupts before the callbacks */
	spu_int_stat_clear(spu, 2, stat);

	pr_debug("class 2 interrupt %d, %lx, %lx\n", irq, stat, mask);

	if (stat & CLASS2_MAILBOX_INTR)
		spu->ibox_callback(spu);

	if (stat & CLASS2_SPU_STOP_INTR)
		spu->stop_callback(spu, 2);

	if (stat & CLASS2_SPU_HALT_INTR)
		spu->stop_callback(spu, 2);

	if (stat & CLASS2_SPU_DMA_TAG_GROUP_COMPLETE_INTR)
		spu->mfc_callback(spu);

	if (stat & CLASS2_MAILBOX_THRESHOLD_INTR)
		spu->wbox_callback(spu);

	spu->stats.class2_intr++;

	spin_unlock(&spu->register_lock);

	return stat ? IRQ_HANDLED : IRQ_NONE;
}