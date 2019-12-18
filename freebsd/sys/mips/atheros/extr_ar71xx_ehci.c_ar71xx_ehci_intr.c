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

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_CPU_DDR_FLUSH_USB ; 
 int /*<<< orphan*/  ar71xx_device_flush_ddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_interrupt (void*) ; 

__attribute__((used)) static void
ar71xx_ehci_intr(void *arg)
{

	/* XXX TODO: should really see if this was our interrupt.. */
	ar71xx_device_flush_ddr(AR71XX_CPU_DDR_FLUSH_USB);
	ehci_interrupt(arg);
}