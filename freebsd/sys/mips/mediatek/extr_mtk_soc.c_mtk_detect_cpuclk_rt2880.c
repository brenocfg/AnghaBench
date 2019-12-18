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
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int MTK_CPU_CLK_250MHZ ; 
 int MTK_CPU_CLK_266MHZ ; 
 int MTK_CPU_CLK_280MHZ ; 
 int MTK_CPU_CLK_300MHZ ; 
 int RT2880_CPU_CLKSEL_MSK ; 
 int RT2880_CPU_CLKSEL_OFF ; 
 int /*<<< orphan*/  SYSCTL_SYSCFG ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
mtk_detect_cpuclk_rt2880(bus_space_tag_t bst, bus_space_handle_t bsh)
{
	uint32_t val;

	val = bus_space_read_4(bst, bsh, SYSCTL_SYSCFG);
	val >>= RT2880_CPU_CLKSEL_OFF;
	val &= RT2880_CPU_CLKSEL_MSK;

	switch (val) {
	case 0:
		return (MTK_CPU_CLK_250MHZ);
	case 1:
		return (MTK_CPU_CLK_266MHZ);
	case 2:
		return (MTK_CPU_CLK_280MHZ);
	case 3:
		return (MTK_CPU_CLK_300MHZ);
	}

	/* Never reached */
	return (0);
}