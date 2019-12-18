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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct scq_info {int /*<<< orphan*/  pending; int /*<<< orphan*/  transmit; int /*<<< orphan*/  paddr; int /*<<< orphan*/  base; } ;
struct idt77252_dev {TYPE_1__* pcidev; } ;
struct atm_vcc {int /*<<< orphan*/  (* pop ) (struct atm_vcc*,struct sk_buff*) ;} ;
struct TYPE_4__ {struct atm_vcc* vcc; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_2__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IDT77252_PRV_PADDR (struct sk_buff*) ; 
 int /*<<< orphan*/  SCQ_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scq_info*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct atm_vcc*,struct sk_buff*) ; 

__attribute__((used)) static void
free_scq(struct idt77252_dev *card, struct scq_info *scq)
{
	struct sk_buff *skb;
	struct atm_vcc *vcc;

	dma_free_coherent(&card->pcidev->dev, SCQ_SIZE,
			  scq->base, scq->paddr);

	while ((skb = skb_dequeue(&scq->transmit))) {
		dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				 skb->len, DMA_TO_DEVICE);

		vcc = ATM_SKB(skb)->vcc;
		if (vcc->pop)
			vcc->pop(vcc, skb);
		else
			dev_kfree_skb(skb);
	}

	while ((skb = skb_dequeue(&scq->pending))) {
		dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				 skb->len, DMA_TO_DEVICE);

		vcc = ATM_SKB(skb)->vcc;
		if (vcc->pop)
			vcc->pop(vcc, skb);
		else
			dev_kfree_skb(skb);
	}

	kfree(scq);
}