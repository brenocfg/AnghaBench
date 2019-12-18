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
typedef  int /*<<< orphan*/  platform_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MODIFY_AUX_CORE_0 ; 
 int /*<<< orphan*/  WRITE_AUX_CORE_1 ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  dcache_wbinv_poc_all () ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 scalar_t__ mpentry ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sev () ; 
 int /*<<< orphan*/  ti_smc0 (int,int,int /*<<< orphan*/ ) ; 

void    
omap4_mp_start_ap(platform_t plat)
{
	bus_addr_t scu_addr;

	if (bus_space_map(fdtbus_bs_tag, 0x48240000, 0x1000, 0, &scu_addr) != 0)
		panic("Couldn't map the SCU\n");
	/* Enable the SCU */
	*(volatile unsigned int *)scu_addr |= 1;
	//*(volatile unsigned int *)(scu_addr + 0x30) |= 1;
	dcache_wbinv_poc_all();

	ti_smc0(0x200, 0xfffffdff, MODIFY_AUX_CORE_0);
	ti_smc0(pmap_kextract((vm_offset_t)mpentry), 0, WRITE_AUX_CORE_1);
	dsb();
	sev();
	bus_space_unmap(fdtbus_bs_tag, scu_addr, 0x1000);
}