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
 int AR5315_AHB_ERROR_DET ; 
 int AR5315_ARB_ENET ; 
 scalar_t__ AR5315_SYSREG_AHB_ARB_CTL ; 
 scalar_t__ AR5315_SYSREG_AHB_ERR0 ; 
 scalar_t__ AR5315_SYSREG_AHB_ERR1 ; 
 scalar_t__ AR5315_SYSREG_BASE ; 
 scalar_t__ AR5315_SYSREG_ENDIAN ; 
 scalar_t__ AR5315_SYSREG_GPIO_INT ; 
 scalar_t__ AR5315_SYSREG_WDOG_CTL ; 
 int AR5315_WDOG_CTL_IGNORE ; 
 int ATH_READ_REG (scalar_t__) ; 
 int /*<<< orphan*/  ATH_WRITE_REG (scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
ar5315_chip_device_start(void)
{
	ATH_WRITE_REG(AR5315_SYSREG_BASE+AR5315_SYSREG_AHB_ERR0,
		AR5315_AHB_ERROR_DET);
	ATH_READ_REG(AR5315_SYSREG_BASE+AR5315_SYSREG_AHB_ERR1);
	ATH_WRITE_REG(AR5315_SYSREG_BASE+AR5315_SYSREG_WDOG_CTL, 
		AR5315_WDOG_CTL_IGNORE);

	// set Ethernet AHB master arbitration control
	// Maybe RedBoot was enabled. But to make sure.
	ATH_WRITE_REG(AR5315_SYSREG_BASE+AR5315_SYSREG_AHB_ARB_CTL,
		ATH_READ_REG(AR5315_SYSREG_BASE+AR5315_SYSREG_AHB_ARB_CTL) |
		AR5315_ARB_ENET);
	
	// set Ethernet controller byteswap control
/*
	ATH_WRITE_REG(AR5315_SYSREG_BASE+AR5315_SYSREG_ENDIAN,
		ATH_READ_REG(AR5315_SYSREG_BASE+AR5315_SYSREG_ENDIAN) |
		AR5315_ENDIAN_ENET);
*/
	/* Disable interrupts for all gpio pins. */
	ATH_WRITE_REG(AR5315_SYSREG_BASE+AR5315_SYSREG_GPIO_INT, 0);

	printf("AHB Master Arbitration Control %08x\n",
		ATH_READ_REG(AR5315_SYSREG_BASE+AR5315_SYSREG_AHB_ARB_CTL));
	printf("Byteswap Control %08x\n",
		ATH_READ_REG(AR5315_SYSREG_BASE+AR5315_SYSREG_ENDIAN));
}