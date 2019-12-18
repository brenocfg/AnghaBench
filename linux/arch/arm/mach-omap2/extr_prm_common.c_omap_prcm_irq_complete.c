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
struct TYPE_2__ {int suspended; int suspend_save_flag; int /*<<< orphan*/  saved_mask; int /*<<< orphan*/  (* restore_irqen ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* prcm_irq_setup ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void omap_prcm_irq_complete(void)
{
	prcm_irq_setup->suspended = false;

	/* If we have not saved the masks, do not attempt to restore */
	if (!prcm_irq_setup->suspend_save_flag)
		return;

	prcm_irq_setup->suspend_save_flag = false;

	/*
	 * Re-enable all masked PRCM irq sources, this causes the PRCM
	 * interrupt to fire immediately if the events were masked
	 * previously in the chain handler
	 */
	prcm_irq_setup->restore_irqen(prcm_irq_setup->saved_mask);
}