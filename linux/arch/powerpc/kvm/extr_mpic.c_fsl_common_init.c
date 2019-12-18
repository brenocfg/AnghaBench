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
struct openpic {int vector_mask; int idr_reset; int max_irq; int irq_ipi0; int irq_tim0; int irq_msi; TYPE_2__* src; TYPE_1__* fsl; int /*<<< orphan*/  ivpr_reset; scalar_t__ tfrr_reset; int /*<<< orphan*/  vir; int /*<<< orphan*/  vid; } ;
struct TYPE_4__ {int level; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int max_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IRQ_TYPE_FSLINT ; 
 int /*<<< orphan*/  IRQ_TYPE_FSLSPECIAL ; 
 int /*<<< orphan*/  IVPR_MASK_MASK ; 
 scalar_t__ MAX_IPI ; 
 int MAX_IRQ ; 
 int MAX_SRC ; 
 scalar_t__ MAX_TMR ; 
 int /*<<< orphan*/  VID_REVISION_1_2 ; 
 int /*<<< orphan*/  VIR_GENERIC ; 
 int /*<<< orphan*/  add_mmio_region (struct openpic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openpic_msi_mmio ; 
 int /*<<< orphan*/  openpic_summary_mmio ; 

__attribute__((used)) static void fsl_common_init(struct openpic *opp)
{
	int i;
	int virq = MAX_SRC;

	add_mmio_region(opp, &openpic_msi_mmio);
	add_mmio_region(opp, &openpic_summary_mmio);

	opp->vid = VID_REVISION_1_2;
	opp->vir = VIR_GENERIC;
	opp->vector_mask = 0xFFFF;
	opp->tfrr_reset = 0;
	opp->ivpr_reset = IVPR_MASK_MASK;
	opp->idr_reset = 1 << 0;
	opp->max_irq = MAX_IRQ;

	opp->irq_ipi0 = virq;
	virq += MAX_IPI;
	opp->irq_tim0 = virq;
	virq += MAX_TMR;

	BUG_ON(virq > MAX_IRQ);

	opp->irq_msi = 224;

	for (i = 0; i < opp->fsl->max_ext; i++)
		opp->src[i].level = false;

	/* Internal interrupts, including message and MSI */
	for (i = 16; i < MAX_SRC; i++) {
		opp->src[i].type = IRQ_TYPE_FSLINT;
		opp->src[i].level = true;
	}

	/* timers and IPIs */
	for (i = MAX_SRC; i < virq; i++) {
		opp->src[i].type = IRQ_TYPE_FSLSPECIAL;
		opp->src[i].level = false;
	}
}