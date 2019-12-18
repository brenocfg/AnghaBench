#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tnetd7300_clock {int /*<<< orphan*/  pll; int /*<<< orphan*/  ctrl; } ;
struct TYPE_4__ {int rate; } ;
struct TYPE_3__ {int rate; } ;

/* Variables and functions */
 int AR7_REF_CLOCK ; 
 int AR7_XTAL_CLOCK ; 
#define  BOOT_PLL_SOURCE_BUS 131 
#define  BOOT_PLL_SOURCE_CPU 130 
 int BOOT_PLL_SOURCE_MASK ; 
#define  BOOT_PLL_SOURCE_REF 129 
#define  BOOT_PLL_SOURCE_XTAL 128 
 int MUL_SHIFT ; 
 int PLL_STATUS ; 
 int PREDIV_SHIFT ; 
 TYPE_2__ bus_clk ; 
 int /*<<< orphan*/  calculate (int,int,int*,int*,int*) ; 
 TYPE_1__ cpu_clk ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tnetd7300_set_clock(u32 shift, struct tnetd7300_clock *clock,
	u32 *bootcr, u32 frequency)
{
	int prediv, postdiv, mul;
	int base_clock = bus_clk.rate;

	switch ((*bootcr & (BOOT_PLL_SOURCE_MASK << shift)) >> shift) {
	case BOOT_PLL_SOURCE_BUS:
		base_clock = bus_clk.rate;
		break;
	case BOOT_PLL_SOURCE_REF:
		base_clock = AR7_REF_CLOCK;
		break;
	case BOOT_PLL_SOURCE_XTAL:
		base_clock = AR7_XTAL_CLOCK;
		break;
	case BOOT_PLL_SOURCE_CPU:
		base_clock = cpu_clk.rate;
		break;
	}

	calculate(base_clock, frequency, &prediv, &postdiv, &mul);

	writel(((prediv - 1) << PREDIV_SHIFT) | (postdiv - 1), &clock->ctrl);
	mdelay(1);
	writel(4, &clock->pll);
	while (readl(&clock->pll) & PLL_STATUS)
		;
	writel(((mul - 1) << MUL_SHIFT) | (0xff << 3) | 0x0e, &clock->pll);
	mdelay(75);
}