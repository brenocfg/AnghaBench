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
 int AML_WDT_CTRL_CPU_WDRESET_MASK ; 
 int AML_WDT_CTRL_EN ; 
 int /*<<< orphan*/  AML_WDT_CTRL_REG ; 
 int AML_WDT_CTRL_TERMINAL_CNT_SHIFT ; 
 int /*<<< orphan*/  AML_WDT_RESET_REG ; 
 int /*<<< orphan*/  CSR_WRITE_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * aml8726_wdt_sc ; 
 int /*<<< orphan*/  printf (char*) ; 

void
cpu_reset(void)
{

	/* Watchdog has not yet been initialized */
	if (aml8726_wdt_sc == NULL)
		printf("Reset hardware has not yet been initialized.\n");
	else {
		CSR_WRITE_4(aml8726_wdt_sc, AML_WDT_RESET_REG, 0);
		CSR_WRITE_4(aml8726_wdt_sc, AML_WDT_CTRL_REG,
		    (AML_WDT_CTRL_CPU_WDRESET_MASK | AML_WDT_CTRL_EN |
		    (10 << AML_WDT_CTRL_TERMINAL_CNT_SHIFT)));
	}

	while (1);
}