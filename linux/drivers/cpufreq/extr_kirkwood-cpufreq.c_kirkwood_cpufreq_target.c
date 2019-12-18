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
struct cpufreq_policy {int dummy; } ;
struct TYPE_4__ {unsigned int driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; int /*<<< orphan*/  ddr_clk; int /*<<< orphan*/  powersave_clk; int /*<<< orphan*/  cpu_clk; } ;

/* Variables and functions */
 unsigned long CPU_SW_INT_BLK ; 
#define  STATE_CPU_FREQ 129 
#define  STATE_DDR_FREQ 128 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 TYPE_2__* kirkwood_freq_table ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 TYPE_1__ priv ; 
 unsigned long readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kirkwood_cpufreq_target(struct cpufreq_policy *policy,
			    unsigned int index)
{
	unsigned int state = kirkwood_freq_table[index].driver_data;
	unsigned long reg;

	local_irq_disable();

	/* Disable interrupts to the CPU */
	reg = readl_relaxed(priv.base);
	reg |= CPU_SW_INT_BLK;
	writel_relaxed(reg, priv.base);

	switch (state) {
	case STATE_CPU_FREQ:
		clk_set_parent(priv.powersave_clk, priv.cpu_clk);
		break;
	case STATE_DDR_FREQ:
		clk_set_parent(priv.powersave_clk, priv.ddr_clk);
		break;
	}

	/* Wait-for-Interrupt, while the hardware changes frequency */
	cpu_do_idle();

	/* Enable interrupts to the CPU */
	reg = readl_relaxed(priv.base);
	reg &= ~CPU_SW_INT_BLK;
	writel_relaxed(reg, priv.base);

	local_irq_enable();

	return 0;
}