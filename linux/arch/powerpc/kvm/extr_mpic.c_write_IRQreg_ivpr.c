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
typedef  int uint32_t ;
struct openpic {int vector_mask; TYPE_1__* src; } ;
struct TYPE_2__ {int ivpr; int type; int level; } ;

/* Variables and functions */
#define  IRQ_TYPE_FSLINT 130 
#define  IRQ_TYPE_FSLSPECIAL 129 
#define  IRQ_TYPE_NORMAL 128 
 int IVPR_ACTIVITY_MASK ; 
 int IVPR_MASK_MASK ; 
 int IVPR_POLARITY_MASK ; 
 int IVPR_PRIORITY_MASK ; 
 int IVPR_SENSE_MASK ; 
 int /*<<< orphan*/  openpic_update_irq (struct openpic*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 

__attribute__((used)) static inline void write_IRQreg_ivpr(struct openpic *opp, int n_IRQ,
				     uint32_t val)
{
	uint32_t mask;

	/* NOTE when implementing newer FSL MPIC models: starting with v4.0,
	 * the polarity bit is read-only on internal interrupts.
	 */
	mask = IVPR_MASK_MASK | IVPR_PRIORITY_MASK | IVPR_SENSE_MASK |
	    IVPR_POLARITY_MASK | opp->vector_mask;

	/* ACTIVITY bit is read-only */
	opp->src[n_IRQ].ivpr =
	    (opp->src[n_IRQ].ivpr & IVPR_ACTIVITY_MASK) | (val & mask);

	/* For FSL internal interrupts, The sense bit is reserved and zero,
	 * and the interrupt is always level-triggered.  Timers and IPIs
	 * have no sense or polarity bits, and are edge-triggered.
	 */
	switch (opp->src[n_IRQ].type) {
	case IRQ_TYPE_NORMAL:
		opp->src[n_IRQ].level =
		    !!(opp->src[n_IRQ].ivpr & IVPR_SENSE_MASK);
		break;

	case IRQ_TYPE_FSLINT:
		opp->src[n_IRQ].ivpr &= ~IVPR_SENSE_MASK;
		break;

	case IRQ_TYPE_FSLSPECIAL:
		opp->src[n_IRQ].ivpr &= ~(IVPR_POLARITY_MASK | IVPR_SENSE_MASK);
		break;
	}

	openpic_update_irq(opp, n_IRQ);
	pr_debug("Set IVPR %d to 0x%08x -> 0x%08x\n", n_IRQ, val,
		opp->src[n_IRQ].ivpr);
}