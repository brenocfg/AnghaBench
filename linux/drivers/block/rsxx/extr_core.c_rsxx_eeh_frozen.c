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
struct rsxx_cardinfo {int eeh_state; int n_targets; TYPE_3__* ctrl; int /*<<< orphan*/  dev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_addr; scalar_t__ buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma_addr; scalar_t__ buf; } ;
struct TYPE_6__ {TYPE_2__ cmd; TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_BUFFER_SIZE8 ; 
 int /*<<< orphan*/  STATUS_BUFFER_SIZE8 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rsxx_cardinfo* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rsxx_eeh_save_issued_creg (struct rsxx_cardinfo*) ; 
 int rsxx_eeh_save_issued_dmas (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_mask_interrupts (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int rsxx_eeh_frozen(struct pci_dev *dev)
{
	struct rsxx_cardinfo *card = pci_get_drvdata(dev);
	int i;
	int st;

	dev_warn(&dev->dev, "IBM Flash Adapter PCI: preparing for slot reset.\n");

	card->eeh_state = 1;
	rsxx_mask_interrupts(card);

	/*
	 * We need to guarantee that the write for eeh_state and masking
	 * interrupts does not become reordered. This will prevent a possible
	 * race condition with the EEH code.
	 */
	wmb();

	pci_disable_device(dev);

	st = rsxx_eeh_save_issued_dmas(card);
	if (st)
		return st;

	rsxx_eeh_save_issued_creg(card);

	for (i = 0; i < card->n_targets; i++) {
		if (card->ctrl[i].status.buf)
			pci_free_consistent(card->dev, STATUS_BUFFER_SIZE8,
					    card->ctrl[i].status.buf,
					    card->ctrl[i].status.dma_addr);
		if (card->ctrl[i].cmd.buf)
			pci_free_consistent(card->dev, COMMAND_BUFFER_SIZE8,
					    card->ctrl[i].cmd.buf,
					    card->ctrl[i].cmd.dma_addr);
	}

	return 0;
}