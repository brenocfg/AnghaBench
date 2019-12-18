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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int volatile WDOG_CR_SRS ; 
 int volatile WDOG_CR_WDA ; 
 int volatile WDOG_CR_WDT ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int* devmap_ptov (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
imx_wdog_cpu_reset(vm_offset_t wdcr_physaddr)
{
	volatile uint16_t cr, *pcr;

	if ((pcr = devmap_ptov(wdcr_physaddr, sizeof(*pcr))) == NULL) {
		printf("imx_wdog_cpu_reset(): "
		    "cannot find control register... locking up now.");
		for (;;)
			cpu_spinwait();
	}
	cr = *pcr;

	/*
	 * If the watchdog hardware has been set up to trigger an external reset
	 * signal on watchdog timeout, then we do software-requested rebooting
	 * the same way, by asserting the external reset signal.
	 *
	 * Asserting external reset is supposed to result in some external
	 * component asserting the POR pin on the SoC, possibly after adjusting
	 * and stabilizing system voltages, or taking other system-wide reset
	 * actions.  Just in case there is some kind of misconfiguration, we
	 * hang out and do nothing for a full second, then continue on into
	 * the code to assert a software reset as well.
	 */
	if (cr & WDOG_CR_WDT) {
		cr &= ~WDOG_CR_WDA; /* Assert active-low ext reset bit. */
		*pcr = cr;
		DELAY(1000000);
		printf("imx_wdog_cpu_reset(): "
		    "External reset failed, trying internal cpu-reset\n");
		DELAY(10000); /* Time for printf to appear */
	}

	/*
	 * Imx6 erratum ERR004346 says the SRS bit has to be cleared twice
	 * within the same cycle of the 32khz clock to reliably trigger the
	 * reset.  Writing it 3 times in a row ensures at least 2 of the writes
	 * happen in the same 32k clock cycle.
	 */
	cr &= ~WDOG_CR_SRS; /* Assert active-low software reset bit. */
	*pcr = cr;
	*pcr = cr;
	*pcr = cr;

	/* Reset happens on the next tick of the 32khz clock, wait for it. */
	for (;;)
		cpu_spinwait();
}