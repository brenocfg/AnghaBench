#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  done_work; int /*<<< orphan*/  creg_wq; } ;
struct rsxx_cardinfo {unsigned int isr_mask; int n_targets; int ier_mask; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  event_work; int /*<<< orphan*/  event_wq; TYPE_2__ creg_ctrl; TYPE_1__* ctrl; scalar_t__ regmap; int /*<<< orphan*/  eeh_state; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  dma_done_work; int /*<<< orphan*/  done_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 unsigned int CR_INTR_CREG ; 
 int CR_INTR_DMA (int) ; 
 unsigned int CR_INTR_EVENT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ ISR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsxx_disable_ier (struct rsxx_cardinfo*,int) ; 
 int /*<<< orphan*/  rsxx_disable_ier_and_isr (struct rsxx_cardinfo*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rsxx_isr(int irq, void *pdata)
{
	struct rsxx_cardinfo *card = pdata;
	unsigned int isr;
	int handled = 0;
	int reread_isr;
	int i;

	spin_lock(&card->irq_lock);

	do {
		reread_isr = 0;

		if (unlikely(card->eeh_state))
			break;

		isr = ioread32(card->regmap + ISR);
		if (isr == 0xffffffff) {
			/*
			 * A few systems seem to have an intermittent issue
			 * where PCI reads return all Fs, but retrying the read
			 * a little later will return as expected.
			 */
			dev_info(CARD_TO_DEV(card),
				"ISR = 0xFFFFFFFF, retrying later\n");
			break;
		}

		isr &= card->isr_mask;
		if (!isr)
			break;

		for (i = 0; i < card->n_targets; i++) {
			if (isr & CR_INTR_DMA(i)) {
				if (card->ier_mask & CR_INTR_DMA(i)) {
					rsxx_disable_ier(card, CR_INTR_DMA(i));
					reread_isr = 1;
				}
				queue_work(card->ctrl[i].done_wq,
					   &card->ctrl[i].dma_done_work);
				handled++;
			}
		}

		if (isr & CR_INTR_CREG) {
			queue_work(card->creg_ctrl.creg_wq,
				   &card->creg_ctrl.done_work);
			handled++;
		}

		if (isr & CR_INTR_EVENT) {
			queue_work(card->event_wq, &card->event_work);
			rsxx_disable_ier_and_isr(card, CR_INTR_EVENT);
			handled++;
		}
	} while (reread_isr);

	spin_unlock(&card->irq_lock);

	return handled ? IRQ_HANDLED : IRQ_NONE;
}