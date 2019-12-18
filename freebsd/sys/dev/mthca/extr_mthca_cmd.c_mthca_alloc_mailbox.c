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
struct mthca_mailbox {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;
struct mthca_dev {TYPE_1__ cmd; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mthca_mailbox* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mthca_mailbox*) ; 
 struct mthca_mailbox* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct mthca_mailbox *mthca_alloc_mailbox(struct mthca_dev *dev,
					  gfp_t gfp_mask)
{
	struct mthca_mailbox *mailbox;

	mailbox = kmalloc(sizeof *mailbox, gfp_mask);
	if (!mailbox)
		return ERR_PTR(-ENOMEM);

	mailbox->buf = pci_pool_alloc(dev->cmd.pool, gfp_mask, &mailbox->dma);
	if (!mailbox->buf) {
		kfree(mailbox);
		return ERR_PTR(-ENOMEM);
	}

	return mailbox;
}