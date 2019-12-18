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
struct lanai_dev {int conf1; int /*<<< orphan*/  timer; int /*<<< orphan*/  backlog_vccs; int /*<<< orphan*/  servicelock; } ;

/* Variables and functions */
 int CONFIG1_POWERDOWN ; 
 scalar_t__ LANAI_POLL_PERIOD ; 
 struct lanai_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_statistics (struct lanai_dev*) ; 
 int /*<<< orphan*/  iter_dequeue ; 
 scalar_t__ jiffies ; 
 struct lanai_dev* lanai ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_service (struct lanai_dev*) ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  vcc_sklist_lock ; 
 int /*<<< orphan*/  vci_bitfield_iterate (struct lanai_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lanai_timed_poll(struct timer_list *t)
{
	struct lanai_dev *lanai = from_timer(lanai, t, timer);
#ifndef DEBUG_RW
	unsigned long flags;
#ifdef USE_POWERDOWN
	if (lanai->conf1 & CONFIG1_POWERDOWN)
		return;
#endif /* USE_POWERDOWN */
	local_irq_save(flags);
	/* If we can grab the spinlock, check if any services need to be run */
	if (spin_trylock(&lanai->servicelock)) {
		run_service(lanai);
		spin_unlock(&lanai->servicelock);
	}
	/* ...and see if any backlogged VCs can make progress */
	/* unfortunately linux has no read_trylock() currently */
	read_lock(&vcc_sklist_lock);
	vci_bitfield_iterate(lanai, lanai->backlog_vccs, iter_dequeue);
	read_unlock(&vcc_sklist_lock);
	local_irq_restore(flags);

	get_statistics(lanai);
#endif /* !DEBUG_RW */
	mod_timer(&lanai->timer, jiffies + LANAI_POLL_PERIOD);
}