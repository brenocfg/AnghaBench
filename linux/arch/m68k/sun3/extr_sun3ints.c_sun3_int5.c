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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  intersil_clear () ; 
 unsigned int kstat_irqs_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * led_pattern ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sun3_disable_irq (int) ; 
 int /*<<< orphan*/  sun3_enable_irq (int) ; 
 int /*<<< orphan*/  sun3_leds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_process_times (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtime_update (int) ; 

__attribute__((used)) static irqreturn_t sun3_int5(int irq, void *dev_id)
{
	unsigned long flags;
	unsigned int cnt;

	local_irq_save(flags);
#ifdef CONFIG_SUN3
	intersil_clear();
#endif
	sun3_disable_irq(5);
	sun3_enable_irq(5);
#ifdef CONFIG_SUN3
	intersil_clear();
#endif
	xtime_update(1);
	update_process_times(user_mode(get_irq_regs()));
	cnt = kstat_irqs_cpu(irq, 0);
	if (!(cnt % 20))
		sun3_leds(led_pattern[cnt % 160 / 20]);
	local_irq_restore(flags);
	return IRQ_HANDLED;
}