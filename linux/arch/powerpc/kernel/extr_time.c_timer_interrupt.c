#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct pt_regs {int dummy; } ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  timer_irqs_others; int /*<<< orphan*/  timer_irqs_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PPC_WATCHDOG ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_irq_work_pending () ; 
 int /*<<< orphan*/  cpu_online (int /*<<< orphan*/ ) ; 
 int decrementer_max ; 
 int /*<<< orphan*/  decrementers ; 
 int /*<<< orphan*/  decrementers_next_tb ; 
 int /*<<< orphan*/  do_IRQ (struct pt_regs*) ; 
 int get_tb_or_rtc () ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 TYPE_1__ irq_stat ; 
 int /*<<< orphan*/  irq_work_run () ; 
 int /*<<< orphan*/  may_hard_irq_enable () ; 
 int /*<<< orphan*/  ppc_n_lost_interrupts ; 
 int /*<<< orphan*/  set_dec (int) ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 scalar_t__ test_irq_work_pending () ; 
 void* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_timer_interrupt_entry (struct pt_regs*) ; 
 int /*<<< orphan*/  trace_timer_interrupt_exit (struct pt_regs*) ; 
 scalar_t__ unlikely (int) ; 

void timer_interrupt(struct pt_regs *regs)
{
	struct clock_event_device *evt = this_cpu_ptr(&decrementers);
	u64 *next_tb = this_cpu_ptr(&decrementers_next_tb);
	struct pt_regs *old_regs;
	u64 now;

	/* Some implementations of hotplug will get timer interrupts while
	 * offline, just ignore these and we also need to set
	 * decrementers_next_tb as MAX to make sure __check_irq_replay
	 * don't replay timer interrupt when return, otherwise we'll trap
	 * here infinitely :(
	 */
	if (unlikely(!cpu_online(smp_processor_id()))) {
		*next_tb = ~(u64)0;
		set_dec(decrementer_max);
		return;
	}

	/* Ensure a positive value is written to the decrementer, or else
	 * some CPUs will continue to take decrementer exceptions. When the
	 * PPC_WATCHDOG (decrementer based) is configured, keep this at most
	 * 31 bits, which is about 4 seconds on most systems, which gives
	 * the watchdog a chance of catching timer interrupt hard lockups.
	 */
	if (IS_ENABLED(CONFIG_PPC_WATCHDOG))
		set_dec(0x7fffffff);
	else
		set_dec(decrementer_max);

	/* Conditionally hard-enable interrupts now that the DEC has been
	 * bumped to its maximum value
	 */
	may_hard_irq_enable();


#if defined(CONFIG_PPC32) && defined(CONFIG_PPC_PMAC)
	if (atomic_read(&ppc_n_lost_interrupts) != 0)
		do_IRQ(regs);
#endif

	old_regs = set_irq_regs(regs);
	irq_enter();
	trace_timer_interrupt_entry(regs);

	if (test_irq_work_pending()) {
		clear_irq_work_pending();
		irq_work_run();
	}

	now = get_tb_or_rtc();
	if (now >= *next_tb) {
		*next_tb = ~(u64)0;
		if (evt->event_handler)
			evt->event_handler(evt);
		__this_cpu_inc(irq_stat.timer_irqs_event);
	} else {
		now = *next_tb - now;
		if (now <= decrementer_max)
			set_dec(now);
		/* We may have raced with new irq work */
		if (test_irq_work_pending())
			set_dec(1);
		__this_cpu_inc(irq_stat.timer_irqs_others);
	}

	trace_timer_interrupt_exit(regs);
	irq_exit();
	set_irq_regs(old_regs);
}