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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ data; } ;
struct idt77252_dev {TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IDT77252_PRV_PADDR (struct sk_buff*) ; 
 int /*<<< orphan*/  IDT77252_PRV_POOL (struct sk_buff*) ; 
 int /*<<< orphan*/  POOL_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int push_rx_skb (struct idt77252_dev*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_pool_remove (struct idt77252_dev*,struct sk_buff*) ; 
 scalar_t__ skb_end_pointer (struct sk_buff*) ; 

__attribute__((used)) static void
recycle_rx_skb(struct idt77252_dev *card, struct sk_buff *skb)
{
	u32 handle = IDT77252_PRV_POOL(skb);
	int err;

	dma_sync_single_for_device(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				   skb_end_pointer(skb) - skb->data,
				   DMA_FROM_DEVICE);

	err = push_rx_skb(card, skb, POOL_QUEUE(handle));
	if (err) {
		dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				 skb_end_pointer(skb) - skb->data,
				 DMA_FROM_DEVICE);
		sb_pool_remove(card, skb);
		dev_kfree_skb(skb);
	}
}