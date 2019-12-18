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
 int MT7628_CPU_CLKSEL_MSK ; 
 int MT7628_CPU_CLKSEL_OFF ; 
 int MTK_CPU_CLK_575MHZ ; 
 int MTK_CPU_CLK_580MHZ ; 
 int /*<<< orphan*/  SYSCTL_SYSCFG ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
mtk_detect_cpuclk_mt7628(bus_space_tag_t bst, bus_space_handle_t bsh)
{
	uint32_t val;

	val = bus_space_read_4(bst, bsh, SYSCTL_SYSCFG);
	val >>= MT7628_CPU_CLKSEL_OFF;
	val &= MT7628_CPU_CLKSEL_MSK;

	if (val)
		return (MTK_CPU_CLK_580MHZ);

	return (MTK_CPU_CLK_575MHZ);
}