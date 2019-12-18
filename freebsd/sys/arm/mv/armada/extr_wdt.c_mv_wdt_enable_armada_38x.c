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
 int CPU_TIMER_WD_25MHZ_EN ; 
 int CPU_TIMER_WD_AUTO ; 
 int CPU_TIMER_WD_EN ; 
 int IRQ_TIMER_WD_CLR ; 
 int mv_get_timer_control () ; 
 int /*<<< orphan*/  mv_set_timer_control (int) ; 
 int /*<<< orphan*/  mv_wdt_enable_armada_38x_xp_helper () ; 
 int read_cpu_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cpu_ctrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mv_wdt_enable_armada_38x(void)
{
	uint32_t val, irq_cause;

	irq_cause = read_cpu_ctrl(BRIDGE_IRQ_CAUSE);
	irq_cause &= IRQ_TIMER_WD_CLR;
	write_cpu_ctrl(BRIDGE_IRQ_CAUSE, irq_cause);

	mv_wdt_enable_armada_38x_xp_helper();

	val = mv_get_timer_control();
	val |= CPU_TIMER_WD_EN | CPU_TIMER_WD_AUTO | CPU_TIMER_WD_25MHZ_EN;
	mv_set_timer_control(val);
}