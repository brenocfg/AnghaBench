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
struct cpudata {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int EINVAL ; 
 int HWP_EPP_BALANCE_PERFORMANCE ; 
 int HWP_EPP_BALANCE_POWERSAVE ; 
 int HWP_EPP_PERFORMANCE ; 
 int /*<<< orphan*/  X86_FEATURE_EPB ; 
 int /*<<< orphan*/  X86_FEATURE_HWP_EPP ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int intel_pstate_get_epp (struct cpudata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pstate_get_energy_pref_index(struct cpudata *cpu_data)
{
	s16 epp;
	int index = -EINVAL;

	epp = intel_pstate_get_epp(cpu_data, 0);
	if (epp < 0)
		return epp;

	if (boot_cpu_has(X86_FEATURE_HWP_EPP)) {
		if (epp == HWP_EPP_PERFORMANCE)
			return 1;
		if (epp <= HWP_EPP_BALANCE_PERFORMANCE)
			return 2;
		if (epp <= HWP_EPP_BALANCE_POWERSAVE)
			return 3;
		else
			return 4;
	} else if (boot_cpu_has(X86_FEATURE_EPB)) {
		/*
		 * Range:
		 *	0x00-0x03	:	Performance
		 *	0x04-0x07	:	Balance performance
		 *	0x08-0x0B	:	Balance power
		 *	0x0C-0x0F	:	Power
		 * The EPB is a 4 bit value, but our ranges restrict the
		 * value which can be set. Here only using top two bits
		 * effectively.
		 */
		index = (epp >> 2) + 1;
	}

	return index;
}