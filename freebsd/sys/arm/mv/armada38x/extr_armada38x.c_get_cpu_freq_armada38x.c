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
 int A38X_CPU_DDR_CLK_MASK ; 
 int A38X_CPU_DDR_CLK_SHIFT ; 
 scalar_t__ get_sar_value_armada38x () ; 
 int hw_clockrate ; 
 int nitems (int const*) ; 

uint32_t
get_cpu_freq_armada38x(void)
{
	uint32_t sar;

	static const uint32_t cpu_frequencies[] = {
		0, 0, 0, 0,
		1066, 0, 0, 0,
		1332, 0, 0, 0,
		1600, 0, 0, 0,
		1866, 0, 0, 2000
	};

	sar = (uint32_t)get_sar_value_armada38x();
	sar = (sar & A38X_CPU_DDR_CLK_MASK) >> A38X_CPU_DDR_CLK_SHIFT;
	if (sar >= nitems(cpu_frequencies))
		return (0);

	hw_clockrate = cpu_frequencies[sar];

	return (hw_clockrate * 1000 * 1000);
}