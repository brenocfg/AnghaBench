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
 int MT7621_CLKSEL_20MHZ ; 
 int MT7621_CLKSEL_20MHZ_VAL ; 
 int MT7621_CLKSEL_25MHZ ; 
 int MT7621_CLKSEL_25MHZ_VAL ; 
 int MT7621_CLKSEL_MSK ; 
 int MT7621_CLKSEL_OFF ; 
 int MT7621_CLK_STS_BASE ; 
 int MT7621_CLK_STS_DIV_OFF ; 
 int MT7621_CLK_STS_MSK ; 
 scalar_t__ MT7621_MEMDIV_BASE ; 
 int MT7621_MEMDIV_MSK ; 
 int MT7621_MEMDIV_OFF ; 
 int MT7621_USES_MEMDIV ; 
 int MTK_MHZ (int) ; 
 int /*<<< orphan*/  MTK_MT7621_CLKDIV_REG ; 
 int /*<<< orphan*/  SYSCTL_CLKCFG0 ; 
 int /*<<< orphan*/  SYSCTL_CUR_CLK_STS ; 
 int /*<<< orphan*/  SYSCTL_SYSCFG ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
mtk_detect_cpuclk_mt7621(bus_space_tag_t bst, bus_space_handle_t bsh)
{
	uint32_t val, div, res;

	val = bus_space_read_4(bst, bsh, SYSCTL_CLKCFG0);
	if (val & MT7621_USES_MEMDIV) {
		div = bus_space_read_4(bst, bsh, MTK_MT7621_CLKDIV_REG);
		div >>= MT7621_MEMDIV_OFF;
		div &= MT7621_MEMDIV_MSK;
		div += MT7621_MEMDIV_BASE;

		val = bus_space_read_4(bst, bsh, SYSCTL_SYSCFG);
		val >>= MT7621_CLKSEL_OFF;
		val &= MT7621_CLKSEL_MSK;

		if (val >= MT7621_CLKSEL_25MHZ_VAL)
			res = div * MT7621_CLKSEL_25MHZ;
		else if (val >= MT7621_CLKSEL_20MHZ_VAL)
			res = div * MT7621_CLKSEL_20MHZ;
		else
			res = div * 0; /* XXX: not sure about this */
	} else {
		val = bus_space_read_4(bst, bsh, SYSCTL_CUR_CLK_STS);
		div = (val >> MT7621_CLK_STS_DIV_OFF) & MT7621_CLK_STS_MSK;
		val &= MT7621_CLK_STS_MSK;

		res = (MT7621_CLK_STS_BASE * val) / div;
	}

	return (MTK_MHZ(res));
}