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
typedef  int uint32_t ;

/* Variables and functions */
 int AR5312_ENABLE_ENET0 ; 
 int AR5312_ENABLE_ENET1 ; 
 int /*<<< orphan*/  AR5312_MEM_CFG1_BANK0 ; 
 int /*<<< orphan*/  AR5312_MEM_CFG1_BANK1 ; 
 scalar_t__ AR5312_SDRAMCTL_BASE ; 
 scalar_t__ AR5312_SDRAMCTL_MEM_CFG0 ; 
 scalar_t__ AR5312_SDRAMCTL_MEM_CFG1 ; 
 scalar_t__ AR5312_SYSREG_AHBDMAE ; 
 scalar_t__ AR5312_SYSREG_AHBPERR ; 
 scalar_t__ AR5312_SYSREG_BASE ; 
 scalar_t__ AR5312_SYSREG_ENABLE ; 
 int ATH_READ_REG (scalar_t__) ; 
 int /*<<< orphan*/  ATH_WRITE_REG (scalar_t__,int) ; 
 int __SHIFTOUT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

__attribute__((used)) static void
ar5312_chip_device_start(void)
{
	uint32_t cfg0, cfg1;
	uint32_t bank0, bank1;
	uint32_t size0, size1;

	cfg0 = ATH_READ_REG(AR5312_SDRAMCTL_BASE + AR5312_SDRAMCTL_MEM_CFG0);
	cfg1 = ATH_READ_REG(AR5312_SDRAMCTL_BASE + AR5312_SDRAMCTL_MEM_CFG1);

	bank0 = __SHIFTOUT(cfg1, AR5312_MEM_CFG1_BANK0);
	bank1 = __SHIFTOUT(cfg1, AR5312_MEM_CFG1_BANK1);

	size0 = bank0 ? (1 << (bank0 + 1)) : 0;
	size1 = bank1 ? (1 << (bank1 + 1)) : 0;

	size0 <<= 20;
	size1 <<= 20;

	printf("SDRMCTL %x %x %x %x\n", cfg0, cfg1, size0, size1);

	ATH_READ_REG(AR5312_SYSREG_BASE + AR5312_SYSREG_AHBPERR);
	ATH_READ_REG(AR5312_SYSREG_BASE + AR5312_SYSREG_AHBDMAE);
//	ATH_WRITE_REG(AR5312_SYSREG_BASE + AR5312_SYSREG_WDOG_CTL, 0);
	ATH_WRITE_REG(AR5312_SYSREG_BASE + AR5312_SYSREG_ENABLE, 0);

	ATH_WRITE_REG(AR5312_SYSREG_BASE+AR5312_SYSREG_ENABLE,
		ATH_READ_REG(AR5312_SYSREG_BASE+AR5312_SYSREG_ENABLE) |
		AR5312_ENABLE_ENET0 | AR5312_ENABLE_ENET1);

}