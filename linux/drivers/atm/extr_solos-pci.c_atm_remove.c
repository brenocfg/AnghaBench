#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct solos_card {int nr_ports; int /*<<< orphan*/ * tx_queue; TYPE_2__* dev; struct sk_buff** tx_skb; struct sk_buff** rx_skb; TYPE_3__** atmdev; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_8__ {int /*<<< orphan*/  dma_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {TYPE_1__ class_dev; int /*<<< orphan*/  number; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  RX_DMA_SIZE ; 
 TYPE_4__* SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  atm_dev_deregister (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  solos_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atm_remove(struct solos_card *card)
{
	int i;

	for (i = 0; i < card->nr_ports; i++) {
		if (card->atmdev[i]) {
			struct sk_buff *skb;

			dev_info(&card->dev->dev, "Unregistering ATM device %d\n", card->atmdev[i]->number);

			sysfs_remove_group(&card->atmdev[i]->class_dev.kobj, &solos_attr_group);
			atm_dev_deregister(card->atmdev[i]);

			skb = card->rx_skb[i];
			if (skb) {
				dma_unmap_single(&card->dev->dev, SKB_CB(skb)->dma_addr,
						 RX_DMA_SIZE, DMA_FROM_DEVICE);
				dev_kfree_skb(skb);
			}
			skb = card->tx_skb[i];
			if (skb) {
				dma_unmap_single(&card->dev->dev, SKB_CB(skb)->dma_addr,
						 skb->len, DMA_TO_DEVICE);
				dev_kfree_skb(skb);
			}
			while ((skb = skb_dequeue(&card->tx_queue[i])))
				dev_kfree_skb(skb);
 
		}
	}
}