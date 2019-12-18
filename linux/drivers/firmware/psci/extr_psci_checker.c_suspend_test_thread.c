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
struct timer_list {int dummy; } ;
struct sched_param {scalar_t__ sched_priority; } ;
struct cpuidle_state {int /*<<< orphan*/  target_residency; } ;
struct cpuidle_driver {int state_count; struct cpuidle_state* states; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RT_PRIO ; 
 int NUM_SUSPEND_CYCLE ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  SCHED_NORMAL ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ atomic_dec_return_relaxed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuidle_devices ; 
 struct cpuidle_driver* cpuidle_get_cpu_driver (struct cpuidle_device*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer (struct timer_list*) ; 
 int /*<<< orphan*/  destroy_timer_on_stack (struct timer_list*) ; 
 int /*<<< orphan*/  dummy_callback ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kthread_parkme () ; 
 scalar_t__ kthread_should_park () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,scalar_t__) ; 
 int /*<<< orphan*/  nb_active_threads ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 scalar_t__ sched_setscheduler_nocheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int suspend_cpu (struct cpuidle_device*,struct cpuidle_driver*,int) ; 
 int /*<<< orphan*/  suspend_threads_done ; 
 int /*<<< orphan*/  suspend_threads_started ; 
 struct cpuidle_device* this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup_on_stack (struct timer_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int suspend_test_thread(void *arg)
{
	int cpu = (long)arg;
	int i, nb_suspend = 0, nb_shallow_sleep = 0, nb_err = 0;
	struct sched_param sched_priority = { .sched_priority = MAX_RT_PRIO-1 };
	struct cpuidle_device *dev;
	struct cpuidle_driver *drv;
	/* No need for an actual callback, we just want to wake up the CPU. */
	struct timer_list wakeup_timer;

	/* Wait for the main thread to give the start signal. */
	wait_for_completion(&suspend_threads_started);

	/* Set maximum priority to preempt all other threads on this CPU. */
	if (sched_setscheduler_nocheck(current, SCHED_FIFO, &sched_priority))
		pr_warn("Failed to set suspend thread scheduler on CPU %d\n",
			cpu);

	dev = this_cpu_read(cpuidle_devices);
	drv = cpuidle_get_cpu_driver(dev);

	pr_info("CPU %d entering suspend cycles, states 1 through %d\n",
		cpu, drv->state_count - 1);

	timer_setup_on_stack(&wakeup_timer, dummy_callback, 0);
	for (i = 0; i < NUM_SUSPEND_CYCLE; ++i) {
		int index;
		/*
		 * Test all possible states, except 0 (which is usually WFI and
		 * doesn't use PSCI).
		 */
		for (index = 1; index < drv->state_count; ++index) {
			int ret;
			struct cpuidle_state *state = &drv->states[index];

			/*
			 * Set the timer to wake this CPU up in some time (which
			 * should be largely sufficient for entering suspend).
			 * If the local tick is disabled when entering suspend,
			 * suspend_cpu() takes care of switching to a broadcast
			 * tick, so the timer will still wake us up.
			 */
			mod_timer(&wakeup_timer, jiffies +
				  usecs_to_jiffies(state->target_residency));

			/* IRQs must be disabled during suspend operations. */
			local_irq_disable();

			ret = suspend_cpu(dev, drv, index);

			/*
			 * We have woken up. Re-enable IRQs to handle any
			 * pending interrupt, do not wait until the end of the
			 * loop.
			 */
			local_irq_enable();

			if (ret == index) {
				++nb_suspend;
			} else if (ret >= 0) {
				/* We did not enter the expected state. */
				++nb_shallow_sleep;
			} else {
				pr_err("Failed to suspend CPU %d: error %d "
				       "(requested state %d, cycle %d)\n",
				       cpu, ret, index, i);
				++nb_err;
			}
		}
	}

	/*
	 * Disable the timer to make sure that the timer will not trigger
	 * later.
	 */
	del_timer(&wakeup_timer);
	destroy_timer_on_stack(&wakeup_timer);

	if (atomic_dec_return_relaxed(&nb_active_threads) == 0)
		complete(&suspend_threads_done);

	/* Give up on RT scheduling and wait for termination. */
	sched_priority.sched_priority = 0;
	if (sched_setscheduler_nocheck(current, SCHED_NORMAL, &sched_priority))
		pr_warn("Failed to set suspend thread scheduler on CPU %d\n",
			cpu);
	for (;;) {
		/* Needs to be set first to avoid missing a wakeup. */
		set_current_state(TASK_INTERRUPTIBLE);
		if (kthread_should_park())
			break;
		schedule();
	}

	pr_info("CPU %d suspend test results: success %d, shallow states %d, errors %d\n",
		cpu, nb_suspend, nb_shallow_sleep, nb_err);

	kthread_parkme();

	return nb_err;
}