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
typedef  int uint32_t ;
struct TYPE_4__ {TYPE_1__* config; } ;
struct TYPE_3__ {int irq_timer_wd_clr; int /*<<< orphan*/  bridge_irq_cause; } ;

/* Variables and functions */
 int CPU_TIMER2_AUTO ; 
 int CPU_TIMER2_EN ; 
 int CPU_TIMER_WD_25MHZ_EN ; 
 int /*<<< orphan*/  RSTOUTn_MASK_ARMV7 ; 
 int RSTOUTn_MASK_WD ; 
 int WD_CPU0_MASK ; 
 int WD_GLOBAL_MASK ; 
 int /*<<< orphan*/  WD_RSTOUTn_MASK ; 
 int mv_get_timer_control () ; 
 int /*<<< orphan*/  mv_set_timer_control (int) ; 
 int read_cpu_ctrl (int /*<<< orphan*/ ) ; 
 int read_cpu_misc (int /*<<< orphan*/ ) ; 
 int read_cpu_mp_clocks (int /*<<< orphan*/ ) ; 
 TYPE_2__* timer_softc ; 
 int /*<<< orphan*/  write_cpu_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_cpu_misc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_cpu_mp_clocks (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mv_watchdog_enable_armadaxp(void)
{
	uint32_t irq_cause, val;

	irq_cause = read_cpu_ctrl(timer_softc->config->bridge_irq_cause);
	irq_cause &= timer_softc->config->irq_timer_wd_clr;
	write_cpu_ctrl(timer_softc->config->bridge_irq_cause, irq_cause);

	val = read_cpu_mp_clocks(WD_RSTOUTn_MASK);
	val |= (WD_GLOBAL_MASK | WD_CPU0_MASK);
	write_cpu_mp_clocks(WD_RSTOUTn_MASK, val);

	val = read_cpu_misc(RSTOUTn_MASK_ARMV7);
	val &= ~RSTOUTn_MASK_WD;
	write_cpu_misc(RSTOUTn_MASK_ARMV7, val);

	val = mv_get_timer_control();
	val |= CPU_TIMER2_EN | CPU_TIMER2_AUTO | CPU_TIMER_WD_25MHZ_EN;
	mv_set_timer_control(val);
}