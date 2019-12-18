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
 int /*<<< orphan*/  BRIDGE_IRQ_CAUSE ; 
 int IRQ_TIMER_WD_CLR ; 
 int /*<<< orphan*/  RSTOUTn_MASK_ARMV7 ; 
 int RSTOUTn_MASK_WD ; 
 int WD_CPU0_MASK ; 
 int WD_GLOBAL_MASK ; 
 int /*<<< orphan*/  WD_RSTOUTn_MASK ; 
 int read_cpu_ctrl (int /*<<< orphan*/ ) ; 
 int read_cpu_misc (int /*<<< orphan*/ ) ; 
 int read_cpu_mp_clocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cpu_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_cpu_misc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_cpu_mp_clocks (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
mv_wdt_enable_armada_38x_xp_helper()
{
	uint32_t val, irq_cause;

	irq_cause = read_cpu_ctrl(BRIDGE_IRQ_CAUSE);
	irq_cause &= IRQ_TIMER_WD_CLR;
	write_cpu_ctrl(BRIDGE_IRQ_CAUSE, irq_cause);

	val = read_cpu_mp_clocks(WD_RSTOUTn_MASK);
	val |= (WD_GLOBAL_MASK | WD_CPU0_MASK);
	write_cpu_mp_clocks(WD_RSTOUTn_MASK, val);

	val = read_cpu_misc(RSTOUTn_MASK_ARMV7);
	val &= ~RSTOUTn_MASK_WD;
	write_cpu_misc(RSTOUTn_MASK_ARMV7, val);
}