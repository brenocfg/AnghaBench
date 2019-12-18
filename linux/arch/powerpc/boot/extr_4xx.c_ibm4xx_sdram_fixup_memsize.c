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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned long SDRAM0_READ (int /*<<< orphan*/ ) ; 
 unsigned long SDRAM_CONFIG_BANK_ENABLE ; 
 scalar_t__ SDRAM_CONFIG_BANK_SIZE (unsigned long) ; 
 unsigned long chip_11_errata (unsigned long) ; 
 int /*<<< orphan*/  dt_fixup_memory (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * sdram_bxcr ; 

void ibm4xx_sdram_fixup_memsize(void)
{
	int i;
	unsigned long memsize, bank_config;

	memsize = 0;
	for (i = 0; i < ARRAY_SIZE(sdram_bxcr); i++) {
		bank_config = SDRAM0_READ(sdram_bxcr[i]);
		if (bank_config & SDRAM_CONFIG_BANK_ENABLE)
			memsize += SDRAM_CONFIG_BANK_SIZE(bank_config);
	}

	memsize = chip_11_errata(memsize);
	dt_fixup_memory(0, memsize);
}