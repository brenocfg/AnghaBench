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
struct timespec {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct smi_info {int /*<<< orphan*/  need_watch; scalar_t__ in_maintenance_mode; int /*<<< orphan*/  si_lock; int /*<<< orphan*/  timer_running; } ;
typedef  enum si_sm_result { ____Placeholder_si_sm_result } si_sm_result ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NICE ; 
 int SI_SM_CALL_WITHOUT_DELAY ; 
 int SI_SM_CALL_WITH_DELAY ; 
 int SI_SM_IDLE ; 
 scalar_t__ SI_TIMEOUT_JIFFIES ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ipmi_si_set_not_busy (struct timespec*) ; 
 int ipmi_thread_busy_wait (int,struct smi_info*,struct timespec*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smi_event_handler (struct smi_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_mod_timer (struct smi_info*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ipmi_thread(void *data)
{
	struct smi_info *smi_info = data;
	unsigned long flags;
	enum si_sm_result smi_result;
	struct timespec busy_until = { 0, 0 };

	ipmi_si_set_not_busy(&busy_until);
	set_user_nice(current, MAX_NICE);
	while (!kthread_should_stop()) {
		int busy_wait;

		spin_lock_irqsave(&(smi_info->si_lock), flags);
		smi_result = smi_event_handler(smi_info, 0);

		/*
		 * If the driver is doing something, there is a possible
		 * race with the timer.  If the timer handler see idle,
		 * and the thread here sees something else, the timer
		 * handler won't restart the timer even though it is
		 * required.  So start it here if necessary.
		 */
		if (smi_result != SI_SM_IDLE && !smi_info->timer_running)
			smi_mod_timer(smi_info, jiffies + SI_TIMEOUT_JIFFIES);

		spin_unlock_irqrestore(&(smi_info->si_lock), flags);
		busy_wait = ipmi_thread_busy_wait(smi_result, smi_info,
						  &busy_until);
		if (smi_result == SI_SM_CALL_WITHOUT_DELAY) {
			; /* do nothing */
		} else if (smi_result == SI_SM_CALL_WITH_DELAY && busy_wait) {
			/*
			 * In maintenance mode we run as fast as
			 * possible to allow firmware updates to
			 * complete as fast as possible, but normally
			 * don't bang on the scheduler.
			 */
			if (smi_info->in_maintenance_mode)
				schedule();
			else
				usleep_range(100, 200);
		} else if (smi_result == SI_SM_IDLE) {
			if (atomic_read(&smi_info->need_watch)) {
				schedule_timeout_interruptible(100);
			} else {
				/* Wait to be woken up when we are needed. */
				__set_current_state(TASK_INTERRUPTIBLE);
				schedule();
			}
		} else {
			schedule_timeout_interruptible(1);
		}
	}
	return 0;
}