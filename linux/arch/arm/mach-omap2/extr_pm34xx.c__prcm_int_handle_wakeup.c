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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_MOD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  OMAP3430ES2_USBHOST_MOD ; 
 int /*<<< orphan*/  OMAP3430_PER_MOD ; 
 scalar_t__ OMAP3430_REV_ES1_0 ; 
 int OMAP3430_ST_IO_CHAIN_MASK ; 
 int OMAP3430_ST_IO_MASK ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 int omap_prm_clear_mod_irqs (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ omap_rev () ; 

__attribute__((used)) static irqreturn_t _prcm_int_handle_wakeup(int irq, void *unused)
{
	int c;

	/*
	 * Clear all except ST_IO and ST_IO_CHAIN for wkup module,
	 * these are handled in a separate handler to avoid acking
	 * IO events before parsing in mux code
	 */
	c = omap_prm_clear_mod_irqs(WKUP_MOD, 1, ~(OMAP3430_ST_IO_MASK |
						   OMAP3430_ST_IO_CHAIN_MASK));
	c += omap_prm_clear_mod_irqs(CORE_MOD, 1, ~0);
	c += omap_prm_clear_mod_irqs(OMAP3430_PER_MOD, 1, ~0);
	if (omap_rev() > OMAP3430_REV_ES1_0) {
		c += omap_prm_clear_mod_irqs(CORE_MOD, 3, ~0);
		c += omap_prm_clear_mod_irqs(OMAP3430ES2_USBHOST_MOD, 1, ~0);
	}

	return c ? IRQ_HANDLED : IRQ_NONE;
}