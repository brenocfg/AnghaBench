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
 int /*<<< orphan*/  AR5312_RESET_SYSTEM ; 
 scalar_t__ AR5312_SYSREG_BASE ; 
 scalar_t__ AR5312_SYSREG_RESETCTL ; 
 int /*<<< orphan*/  ATH_WRITE_REG (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar5312_chip_device_reset(void)
{
	ATH_WRITE_REG(AR5312_SYSREG_BASE + AR5312_SYSREG_RESETCTL,
		AR5312_RESET_SYSTEM);
}