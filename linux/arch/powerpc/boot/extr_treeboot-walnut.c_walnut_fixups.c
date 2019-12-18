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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ WALNUT_OPENBIOS_MAC_OFF ; 
 int /*<<< orphan*/  dt_fixup_mac_address_by_alias (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibm405gp_fixup_clocks (int,int) ; 
 int /*<<< orphan*/  ibm4xx_fixup_ebc_ranges (char*) ; 
 int /*<<< orphan*/  ibm4xx_quiesce_eth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibm4xx_sdram_fixup_memsize () ; 
 int /*<<< orphan*/  walnut_flashsel_fixup () ; 

__attribute__((used)) static void walnut_fixups(void)
{
	ibm4xx_sdram_fixup_memsize();
	ibm405gp_fixup_clocks(33330000, 0xa8c000);
	ibm4xx_quiesce_eth((u32 *)0xef600800, NULL);
	ibm4xx_fixup_ebc_ranges("/plb/ebc");
	walnut_flashsel_fixup();
	dt_fixup_mac_address_by_alias("ethernet0", (u8 *) WALNUT_OPENBIOS_MAC_OFF);
}