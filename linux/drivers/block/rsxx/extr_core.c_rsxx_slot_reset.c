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
struct rsxx_cardinfo {int n_targets; TYPE_3__* ctrl; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_lock; scalar_t__ eeh_state; scalar_t__ regmap; scalar_t__ config_valid; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
struct TYPE_5__ {int /*<<< orphan*/  dma_addr; scalar_t__ buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma_addr; scalar_t__ buf; } ;
struct TYPE_6__ {TYPE_2__ cmd; TYPE_1__ status; int /*<<< orphan*/  issue_dma_work; int /*<<< orphan*/  issue_wq; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_BUFFER_SIZE8 ; 
 int /*<<< orphan*/  CR_INTR_ALL_C ; 
 int /*<<< orphan*/  CR_INTR_ALL_G ; 
 scalar_t__ ISR ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int RSXX_MAX_TARGETS ; 
 int /*<<< orphan*/  STATUS_BUFFER_SIZE8 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int ioread32 (scalar_t__) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rsxx_cardinfo* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsxx_dma_configure (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_dma_queue_reset (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_eeh_failure (struct pci_dev*) ; 
 int rsxx_eeh_fifo_flush_poll (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_enable_ier_and_isr (struct rsxx_cardinfo*,int /*<<< orphan*/ ) ; 
 int rsxx_hw_buffers_init (struct pci_dev*,TYPE_3__*) ; 
 int /*<<< orphan*/  rsxx_kick_creg_queue (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static pci_ers_result_t rsxx_slot_reset(struct pci_dev *dev)
{
	struct rsxx_cardinfo *card = pci_get_drvdata(dev);
	unsigned long flags;
	int i;
	int st;

	dev_warn(&dev->dev,
		"IBM Flash Adapter PCI: recovering from slot reset.\n");

	st = pci_enable_device(dev);
	if (st)
		goto failed_hw_setup;

	pci_set_master(dev);

	st = rsxx_eeh_fifo_flush_poll(card);
	if (st)
		goto failed_hw_setup;

	rsxx_dma_queue_reset(card);

	for (i = 0; i < card->n_targets; i++) {
		st = rsxx_hw_buffers_init(dev, &card->ctrl[i]);
		if (st)
			goto failed_hw_buffers_init;
	}

	if (card->config_valid)
		rsxx_dma_configure(card);

	/* Clears the ISR register from spurious interrupts */
	st = ioread32(card->regmap + ISR);

	card->eeh_state = 0;

	spin_lock_irqsave(&card->irq_lock, flags);
	if (card->n_targets & RSXX_MAX_TARGETS)
		rsxx_enable_ier_and_isr(card, CR_INTR_ALL_G);
	else
		rsxx_enable_ier_and_isr(card, CR_INTR_ALL_C);
	spin_unlock_irqrestore(&card->irq_lock, flags);

	rsxx_kick_creg_queue(card);

	for (i = 0; i < card->n_targets; i++) {
		spin_lock(&card->ctrl[i].queue_lock);
		if (list_empty(&card->ctrl[i].queue)) {
			spin_unlock(&card->ctrl[i].queue_lock);
			continue;
		}
		spin_unlock(&card->ctrl[i].queue_lock);

		queue_work(card->ctrl[i].issue_wq,
				&card->ctrl[i].issue_dma_work);
	}

	dev_info(&dev->dev, "IBM Flash Adapter PCI: recovery complete.\n");

	return PCI_ERS_RESULT_RECOVERED;

failed_hw_buffers_init:
	for (i = 0; i < card->n_targets; i++) {
		if (card->ctrl[i].status.buf)
			pci_free_consistent(card->dev,
					STATUS_BUFFER_SIZE8,
					card->ctrl[i].status.buf,
					card->ctrl[i].status.dma_addr);
		if (card->ctrl[i].cmd.buf)
			pci_free_consistent(card->dev,
					COMMAND_BUFFER_SIZE8,
					card->ctrl[i].cmd.buf,
					card->ctrl[i].cmd.dma_addr);
	}
failed_hw_setup:
	rsxx_eeh_failure(dev);
	return PCI_ERS_RESULT_DISCONNECT;

}