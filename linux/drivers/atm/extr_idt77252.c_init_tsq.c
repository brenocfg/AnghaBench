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
struct tsq_entry {int /*<<< orphan*/  word_2; } ;
struct TYPE_4__ {unsigned long paddr; struct tsq_entry* base; struct tsq_entry* next; struct tsq_entry* last; } ;
struct idt77252_dev {TYPE_2__ tsq; int /*<<< orphan*/  name; TYPE_1__* pcidev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RSQSIZE ; 
 int /*<<< orphan*/  SAR_REG_TSQB ; 
 int /*<<< orphan*/  SAR_REG_TSQH ; 
 int /*<<< orphan*/  SAR_TSQE_INVALID ; 
 int TSQ_NUM_ENTRIES ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct tsq_entry* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_tsq(struct idt77252_dev *card)
{
	struct tsq_entry *tsqe;

	card->tsq.base = dma_alloc_coherent(&card->pcidev->dev, RSQSIZE,
					    &card->tsq.paddr, GFP_KERNEL);
	if (card->tsq.base == NULL) {
		printk("%s: can't allocate TSQ.\n", card->name);
		return -1;
	}

	card->tsq.last = card->tsq.base + TSQ_NUM_ENTRIES - 1;
	card->tsq.next = card->tsq.last;
	for (tsqe = card->tsq.base; tsqe <= card->tsq.last; tsqe++)
		tsqe->word_2 = cpu_to_le32(SAR_TSQE_INVALID);

	writel(card->tsq.paddr, SAR_REG_TSQB);
	writel((unsigned long) card->tsq.next - (unsigned long) card->tsq.base,
	       SAR_REG_TSQH);

	return 0;
}