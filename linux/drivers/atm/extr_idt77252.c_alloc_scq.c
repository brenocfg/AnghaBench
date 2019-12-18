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
struct scq_info {scalar_t__ paddr; int /*<<< orphan*/ * last; int /*<<< orphan*/ * next; int /*<<< orphan*/ * base; int /*<<< orphan*/  pending; int /*<<< orphan*/  transmit; int /*<<< orphan*/  skblock; int /*<<< orphan*/  lock; int /*<<< orphan*/  used; } ;
struct idt77252_dev {TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SCQ_ENTRIES ; 
 int /*<<< orphan*/  SCQ_SIZE ; 
 int /*<<< orphan*/  TXPRINTK (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scq_info*) ; 
 struct scq_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct scq_info *
alloc_scq(struct idt77252_dev *card, int class)
{
	struct scq_info *scq;

	scq = kzalloc(sizeof(struct scq_info), GFP_KERNEL);
	if (!scq)
		return NULL;
	scq->base = dma_alloc_coherent(&card->pcidev->dev, SCQ_SIZE,
				       &scq->paddr, GFP_KERNEL);
	if (scq->base == NULL) {
		kfree(scq);
		return NULL;
	}

	scq->next = scq->base;
	scq->last = scq->base + (SCQ_ENTRIES - 1);
	atomic_set(&scq->used, 0);

	spin_lock_init(&scq->lock);
	spin_lock_init(&scq->skblock);

	skb_queue_head_init(&scq->transmit);
	skb_queue_head_init(&scq->pending);

	TXPRINTK("idt77252: SCQ: base 0x%p, next 0x%p, last 0x%p, paddr %08llx\n",
		 scq->base, scq->next, scq->last, (unsigned long long)scq->paddr);

	return scq;
}