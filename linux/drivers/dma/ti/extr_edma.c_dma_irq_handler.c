#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct edma_cc {int id; int /*<<< orphan*/ * slave_chans; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SH_ICR ; 
 int /*<<< orphan*/  SH_IER ; 
 int /*<<< orphan*/  SH_IEVAL ; 
 int /*<<< orphan*/  SH_IPR ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edma_completion_handler (int /*<<< orphan*/ *) ; 
 int edma_shadow0_read_array (struct edma_cc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edma_shadow0_write (struct edma_cc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edma_shadow0_write_array (struct edma_cc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t dma_irq_handler(int irq, void *data)
{
	struct edma_cc *ecc = data;
	int ctlr;
	u32 sh_ier;
	u32 sh_ipr;
	u32 bank;

	ctlr = ecc->id;
	if (ctlr < 0)
		return IRQ_NONE;

	dev_vdbg(ecc->dev, "dma_irq_handler\n");

	sh_ipr = edma_shadow0_read_array(ecc, SH_IPR, 0);
	if (!sh_ipr) {
		sh_ipr = edma_shadow0_read_array(ecc, SH_IPR, 1);
		if (!sh_ipr)
			return IRQ_NONE;
		sh_ier = edma_shadow0_read_array(ecc, SH_IER, 1);
		bank = 1;
	} else {
		sh_ier = edma_shadow0_read_array(ecc, SH_IER, 0);
		bank = 0;
	}

	do {
		u32 slot;
		u32 channel;

		slot = __ffs(sh_ipr);
		sh_ipr &= ~(BIT(slot));

		if (sh_ier & BIT(slot)) {
			channel = (bank << 5) | slot;
			/* Clear the corresponding IPR bits */
			edma_shadow0_write_array(ecc, SH_ICR, bank, BIT(slot));
			edma_completion_handler(&ecc->slave_chans[channel]);
		}
	} while (sh_ipr);

	edma_shadow0_write(ecc, SH_IEVAL, 1);
	return IRQ_HANDLED;
}