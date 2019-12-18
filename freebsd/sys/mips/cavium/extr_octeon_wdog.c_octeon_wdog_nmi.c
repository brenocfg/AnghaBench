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
 int cvmx_get_core_num () ; 
 int mips_rd_cause () ; 
 scalar_t__ mips_rd_excpc () ; 
 int mips_rd_status () ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

void
octeon_wdog_nmi(void)
{
	int core;

	core = cvmx_get_core_num();

	printf("cpu%u: NMI detected\n", core);
	printf("cpu%u: Exception PC: %p\n", core, (void *)mips_rd_excpc());
	printf("cpu%u: status %#x cause %#x\n", core, mips_rd_status(), mips_rd_cause());

	/*
	 * This is the end
	 * Beautiful friend
	 *
	 * Just wait for Soft Reset to come and take us
	 */
	for (;;)
		continue;
}