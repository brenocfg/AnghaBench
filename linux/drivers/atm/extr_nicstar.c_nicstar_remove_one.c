#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_26__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  org; } ;
struct TYPE_25__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  org; } ;
struct TYPE_23__ {int /*<<< orphan*/  queue; } ;
struct TYPE_22__ {int /*<<< orphan*/  queue; } ;
struct TYPE_21__ {int count; int /*<<< orphan*/  queue; } ;
struct TYPE_20__ {int count; int /*<<< orphan*/  queue; } ;
struct TYPE_17__ {int index; scalar_t__ membase; TYPE_9__* pcidev; TYPE_8__ tsq; TYPE_7__ rsq; int /*<<< orphan*/  idr; TYPE_6__** scd2vc; int /*<<< orphan*/  scq0; TYPE_5__ sbpool; TYPE_4__ lbpool; TYPE_3__ iovpool; TYPE_2__ hbpool; TYPE_11__* atmdev; } ;
typedef  TYPE_10__ ns_dev ;
struct TYPE_27__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_24__ {int /*<<< orphan*/ * tx_vcc; int /*<<< orphan*/  scq; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* stop ) (TYPE_11__*) ;} ;
struct TYPE_18__ {TYPE_1__* phy; } ;

/* Variables and functions */
 scalar_t__ CFG ; 
 int NS_FRSCD_NUM ; 
 scalar_t__ NS_RSQSIZE ; 
 scalar_t__ NS_RSQ_ALIGNMENT ; 
 scalar_t__ NS_TSQSIZE ; 
 scalar_t__ NS_TSQ_ALIGNMENT ; 
 int /*<<< orphan*/  PRINTK (char*,int,int) ; 
 int /*<<< orphan*/  atm_dev_deregister (TYPE_11__*) ; 
 int /*<<< orphan*/ ** cards ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  free_scq (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_10__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 TYPE_10__* pci_get_drvdata (struct pci_dev*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void nicstar_remove_one(struct pci_dev *pcidev)
{
	int i, j;
	ns_dev *card = pci_get_drvdata(pcidev);
	struct sk_buff *hb;
	struct sk_buff *iovb;
	struct sk_buff *lb;
	struct sk_buff *sb;

	i = card->index;

	if (cards[i] == NULL)
		return;

	if (card->atmdev->phy && card->atmdev->phy->stop)
		card->atmdev->phy->stop(card->atmdev);

	/* Stop everything */
	writel(0x00000000, card->membase + CFG);

	/* De-register device */
	atm_dev_deregister(card->atmdev);

	/* Disable PCI device */
	pci_disable_device(pcidev);

	/* Free up resources */
	j = 0;
	PRINTK("nicstar%d: freeing %d huge buffers.\n", i, card->hbpool.count);
	while ((hb = skb_dequeue(&card->hbpool.queue)) != NULL) {
		dev_kfree_skb_any(hb);
		j++;
	}
	PRINTK("nicstar%d: %d huge buffers freed.\n", i, j);
	j = 0;
	PRINTK("nicstar%d: freeing %d iovec buffers.\n", i,
	       card->iovpool.count);
	while ((iovb = skb_dequeue(&card->iovpool.queue)) != NULL) {
		dev_kfree_skb_any(iovb);
		j++;
	}
	PRINTK("nicstar%d: %d iovec buffers freed.\n", i, j);
	while ((lb = skb_dequeue(&card->lbpool.queue)) != NULL)
		dev_kfree_skb_any(lb);
	while ((sb = skb_dequeue(&card->sbpool.queue)) != NULL)
		dev_kfree_skb_any(sb);
	free_scq(card, card->scq0, NULL);
	for (j = 0; j < NS_FRSCD_NUM; j++) {
		if (card->scd2vc[j] != NULL)
			free_scq(card, card->scd2vc[j]->scq, card->scd2vc[j]->tx_vcc);
	}
	idr_destroy(&card->idr);
	dma_free_coherent(&card->pcidev->dev, NS_RSQSIZE + NS_RSQ_ALIGNMENT,
			  card->rsq.org, card->rsq.dma);
	dma_free_coherent(&card->pcidev->dev, NS_TSQSIZE + NS_TSQ_ALIGNMENT,
			  card->tsq.org, card->tsq.dma);
	free_irq(card->pcidev->irq, card);
	iounmap(card->membase);
	kfree(card);
}