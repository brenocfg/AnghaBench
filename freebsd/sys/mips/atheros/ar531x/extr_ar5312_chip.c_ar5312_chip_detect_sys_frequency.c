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
 int /*<<< orphan*/  AR2313_CLOCKCTL_MULTIPLIER ; 
 int /*<<< orphan*/  AR2313_CLOCKCTL_PREDIVIDE ; 
 int /*<<< orphan*/  AR5312_CLOCKCTL_MULTIPLIER ; 
 int /*<<< orphan*/  AR5312_CLOCKCTL_PREDIVIDE ; 
 scalar_t__ AR5312_SYSREG_BASE ; 
 scalar_t__ AR5312_SYSREG_CLOCKCTL ; 
 scalar_t__ AR531X_SOC_AR5313 ; 
 int ATH_READ_REG (scalar_t__) ; 
 int __SHIFTOUT (int const,int /*<<< orphan*/ ) ; 
 scalar_t__ ar531x_soc ; 
 int u_ar531x_ahb_freq ; 
 int u_ar531x_cpu_freq ; 
 scalar_t__ u_ar531x_ddr_freq ; 

__attribute__((used)) static void
ar5312_chip_detect_sys_frequency(void)
{
	uint32_t	predivisor;
	uint32_t	multiplier;


	const uint32_t clockctl = ATH_READ_REG(AR5312_SYSREG_BASE + AR5312_SYSREG_CLOCKCTL);
	if(ar531x_soc == AR531X_SOC_AR5313) {
		predivisor = __SHIFTOUT(clockctl, AR2313_CLOCKCTL_PREDIVIDE);
		multiplier = __SHIFTOUT(clockctl, AR2313_CLOCKCTL_MULTIPLIER);
	} else {
		predivisor = __SHIFTOUT(clockctl, AR5312_CLOCKCTL_PREDIVIDE);
		multiplier = __SHIFTOUT(clockctl, AR5312_CLOCKCTL_MULTIPLIER);
	}

	const uint32_t divisor = (0x5421 >> (predivisor * 4)) & 15;

	const uint32_t cpufreq = (40000000 / divisor) * multiplier;

	u_ar531x_cpu_freq = cpufreq;
	u_ar531x_ahb_freq = cpufreq / 4;
	u_ar531x_ddr_freq = 0;
}