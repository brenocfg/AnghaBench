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
typedef  scalar_t__ u64 ;
struct TYPE_3__ {int /*<<< orphan*/  softirq_timer; int /*<<< orphan*/  hardirq_timer; int /*<<< orphan*/  system_timer; int /*<<< orphan*/  guest_timer; int /*<<< orphan*/  user_timer; } ;
struct task_struct {int /*<<< orphan*/  utimescaled; TYPE_1__ thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  steal_timer; int /*<<< orphan*/  softirq_timer; int /*<<< orphan*/  hardirq_timer; int /*<<< orphan*/  system_timer; int /*<<< orphan*/  guest_timer; int /*<<< orphan*/  user_timer; scalar_t__ last_update_timer; scalar_t__ last_update_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUTIME_IRQ ; 
 int /*<<< orphan*/  CPUTIME_SOFTIRQ ; 
 int /*<<< orphan*/  CPUTIME_SYSTEM ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_2__ S390_lowcore ; 
 int /*<<< orphan*/  account_guest_time (struct task_struct*,scalar_t__) ; 
 int /*<<< orphan*/  account_system_index_scaled (struct task_struct*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  account_user_time (struct task_struct*,scalar_t__) ; 
 scalar_t__ cputime_to_nsecs (scalar_t__) ; 
 scalar_t__ hardirq_count () ; 
 int /*<<< orphan*/  jiffies_64 ; 
 int /*<<< orphan*/  mt_scaling_jiffies ; 
 scalar_t__ scale_vtime (scalar_t__) ; 
 scalar_t__ smp_cpu_mtid ; 
 int /*<<< orphan*/  this_cpu_read (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_mt_scaling () ; 
 scalar_t__ update_tsk_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int virt_timer_forward (scalar_t__) ; 

__attribute__((used)) static int do_account_vtime(struct task_struct *tsk)
{
	u64 timer, clock, user, guest, system, hardirq, softirq;

	timer = S390_lowcore.last_update_timer;
	clock = S390_lowcore.last_update_clock;
	asm volatile(
		"	stpt	%0\n"	/* Store current cpu timer value */
#ifdef CONFIG_HAVE_MARCH_Z9_109_FEATURES
		"	stckf	%1"	/* Store current tod clock value */
#else
		"	stck	%1"	/* Store current tod clock value */
#endif
		: "=Q" (S390_lowcore.last_update_timer),
		  "=Q" (S390_lowcore.last_update_clock));
	clock = S390_lowcore.last_update_clock - clock;
	timer -= S390_lowcore.last_update_timer;

	if (hardirq_count())
		S390_lowcore.hardirq_timer += timer;
	else
		S390_lowcore.system_timer += timer;

	/* Update MT utilization calculation */
	if (smp_cpu_mtid &&
	    time_after64(jiffies_64, this_cpu_read(mt_scaling_jiffies)))
		update_mt_scaling();

	/* Calculate cputime delta */
	user = update_tsk_timer(&tsk->thread.user_timer,
				READ_ONCE(S390_lowcore.user_timer));
	guest = update_tsk_timer(&tsk->thread.guest_timer,
				 READ_ONCE(S390_lowcore.guest_timer));
	system = update_tsk_timer(&tsk->thread.system_timer,
				  READ_ONCE(S390_lowcore.system_timer));
	hardirq = update_tsk_timer(&tsk->thread.hardirq_timer,
				   READ_ONCE(S390_lowcore.hardirq_timer));
	softirq = update_tsk_timer(&tsk->thread.softirq_timer,
				   READ_ONCE(S390_lowcore.softirq_timer));
	S390_lowcore.steal_timer +=
		clock - user - guest - system - hardirq - softirq;

	/* Push account value */
	if (user) {
		account_user_time(tsk, cputime_to_nsecs(user));
		tsk->utimescaled += cputime_to_nsecs(scale_vtime(user));
	}

	if (guest) {
		account_guest_time(tsk, cputime_to_nsecs(guest));
		tsk->utimescaled += cputime_to_nsecs(scale_vtime(guest));
	}

	if (system)
		account_system_index_scaled(tsk, system, CPUTIME_SYSTEM);
	if (hardirq)
		account_system_index_scaled(tsk, hardirq, CPUTIME_IRQ);
	if (softirq)
		account_system_index_scaled(tsk, softirq, CPUTIME_SOFTIRQ);

	return virt_timer_forward(user + guest + system + hardirq + softirq);
}