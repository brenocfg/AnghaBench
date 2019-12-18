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
typedef  unsigned long vm_paddr_t ;
typedef  unsigned long u_long ;

/* Variables and functions */
 int /*<<< orphan*/  AA_DMMU_PWPR ; 
 int /*<<< orphan*/  ASI_DMMU ; 
 int /*<<< orphan*/  ASI_LSU_CTL_REG ; 
 unsigned long LSU_PM_MASK ; 
 unsigned long LSU_PM_SHIFT ; 
 unsigned long LSU_PW ; 
 unsigned long ldxa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stxa_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

int
watch_phys_set_mask(vm_paddr_t pa, u_long mask)
{
	u_long lsucr;

	stxa_sync(AA_DMMU_PWPR, ASI_DMMU, pa & (((2UL << 38) - 1) << 3));
	lsucr = ldxa(0, ASI_LSU_CTL_REG);
	lsucr = ((lsucr | LSU_PW) & ~LSU_PM_MASK) |
	    (mask << LSU_PM_SHIFT);
	stxa_sync(0, ASI_LSU_CTL_REG, lsucr);
	return (0);
}