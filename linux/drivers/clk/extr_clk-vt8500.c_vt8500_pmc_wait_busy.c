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
 int VT8500_PMC_BUSY_MASK ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  pmc_base ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vt8500_pmc_wait_busy(void)
{
	while (readl(pmc_base) & VT8500_PMC_BUSY_MASK)
		cpu_relax();
}