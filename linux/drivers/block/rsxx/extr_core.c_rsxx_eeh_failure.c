#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rsxx_cardinfo {int eeh_state; int halt; int n_targets; TYPE_1__* ctrl; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  COMPLETE_DMA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct rsxx_cardinfo* pci_get_drvdata (struct pci_dev*) ; 
 int rsxx_cleanup_dma_queue (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rsxx_dma_cancel (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rsxx_eeh_failure(struct pci_dev *dev)
{
	struct rsxx_cardinfo *card = pci_get_drvdata(dev);
	int i;
	int cnt = 0;

	dev_err(&dev->dev, "IBM Flash Adapter PCI: disabling failed card.\n");

	card->eeh_state = 1;
	card->halt = 1;

	for (i = 0; i < card->n_targets; i++) {
		spin_lock_bh(&card->ctrl[i].queue_lock);
		cnt = rsxx_cleanup_dma_queue(&card->ctrl[i],
					     &card->ctrl[i].queue,
					     COMPLETE_DMA);
		spin_unlock_bh(&card->ctrl[i].queue_lock);

		cnt += rsxx_dma_cancel(&card->ctrl[i]);

		if (cnt)
			dev_info(CARD_TO_DEV(card),
				"Freed %d queued DMAs on channel %d\n",
				cnt, card->ctrl[i].id);
	}
}