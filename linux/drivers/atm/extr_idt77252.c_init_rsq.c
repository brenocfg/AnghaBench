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
struct rsq_entry {scalar_t__ word_4; } ;
struct TYPE_4__ {unsigned long paddr; struct rsq_entry* base; struct rsq_entry* last; struct rsq_entry* next; } ;
struct idt77252_dev {int /*<<< orphan*/  name; TYPE_2__ rsq; TYPE_1__* pcidev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPRINTK (char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  RSQSIZE ; 
 int RSQ_NUM_ENTRIES ; 
 int /*<<< orphan*/  SAR_REG_RSQB ; 
 int /*<<< orphan*/  SAR_REG_RSQH ; 
 int /*<<< orphan*/  SAR_REG_RSQT ; 
 struct rsq_entry* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_rsq(struct idt77252_dev *card)
{
	struct rsq_entry *rsqe;

	card->rsq.base = dma_alloc_coherent(&card->pcidev->dev, RSQSIZE,
					    &card->rsq.paddr, GFP_KERNEL);
	if (card->rsq.base == NULL) {
		printk("%s: can't allocate RSQ.\n", card->name);
		return -1;
	}

	card->rsq.last = card->rsq.base + RSQ_NUM_ENTRIES - 1;
	card->rsq.next = card->rsq.last;
	for (rsqe = card->rsq.base; rsqe <= card->rsq.last; rsqe++)
		rsqe->word_4 = 0;

	writel((unsigned long) card->rsq.last - (unsigned long) card->rsq.base,
	       SAR_REG_RSQH);
	writel(card->rsq.paddr, SAR_REG_RSQB);

	IPRINTK("%s: RSQ base at 0x%lx (0x%x).\n", card->name,
		(unsigned long) card->rsq.base,
		readl(SAR_REG_RSQB));
	IPRINTK("%s: RSQ head = 0x%x, base = 0x%x, tail = 0x%x.\n",
		card->name,
		readl(SAR_REG_RSQH),
		readl(SAR_REG_RSQB),
		readl(SAR_REG_RSQT));

	return 0;
}