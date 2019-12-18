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
 int /*<<< orphan*/  BRIDGE_IRQ_MASK ; 
 int CPU_TIMER2_AUTO ; 
 int CPU_TIMER2_EN ; 
 int IRQ_TIMER_WD_CLR ; 
 int IRQ_TIMER_WD_MASK ; 
 int /*<<< orphan*/  RSTOUTn_MASK ; 
 int WD_RST_OUT_EN ; 
 int mv_get_timer_control () ; 
 int /*<<< orphan*/  mv_set_timer_control (int) ; 
 int read_cpu_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cpu_ctrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mv_wdt_disable_armv5(void)
{
	uint32_t val, irq_cause, irq_mask;

	val = mv_get_timer_control();
	val &= ~(CPU_TIMER2_EN | CPU_TIMER2_AUTO);
	mv_set_timer_control(val);

	val = read_cpu_ctrl(RSTOUTn_MASK);
	val &= ~WD_RST_OUT_EN;
	write_cpu_ctrl(RSTOUTn_MASK, val);

	irq_mask = read_cpu_ctrl(BRIDGE_IRQ_MASK);
	irq_mask &= ~(IRQ_TIMER_WD_MASK);
	write_cpu_ctrl(BRIDGE_IRQ_MASK, irq_mask);

	irq_cause = read_cpu_ctrl(BRIDGE_IRQ_CAUSE);
	irq_cause &= IRQ_TIMER_WD_CLR;
	write_cpu_ctrl(BRIDGE_IRQ_CAUSE, irq_cause);
}