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
 int AR5315_COLD_AHB ; 
 int AR5315_COLD_APB ; 
 int AR5315_COLD_CPU ; 
 scalar_t__ AR5315_SYSREG_BASE ; 
 scalar_t__ AR5315_SYSREG_COLDRESET ; 
 int /*<<< orphan*/  ATH_WRITE_REG (scalar_t__,int) ; 

__attribute__((used)) static void
ar5315_chip_device_reset(void)
{
	ATH_WRITE_REG(AR5315_SYSREG_BASE + AR5315_SYSREG_COLDRESET,
		AR5315_COLD_AHB | AR5315_COLD_APB | AR5315_COLD_CPU);
}