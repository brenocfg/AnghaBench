#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct pmac_i2c_host_kw {scalar_t__ state; int /*<<< orphan*/  lock; TYPE_1__ timeout_timer; } ;

/* Variables and functions */
 scalar_t__ KW_POLL_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct pmac_i2c_host_kw* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct pmac_i2c_host_kw* host ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kw_i2c_handle_interrupt (struct pmac_i2c_host_kw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kw_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_isr ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ state_idle ; 
 int /*<<< orphan*/  timeout_timer ; 
 scalar_t__ timer_pending (TYPE_1__*) ; 

__attribute__((used)) static void kw_i2c_timeout(struct timer_list *t)
{
	struct pmac_i2c_host_kw *host = from_timer(host, t, timeout_timer);
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);

	/*
	 * If the timer is pending, that means we raced with the
	 * irq, in which case we just return
	 */
	if (timer_pending(&host->timeout_timer))
		goto skip;

	kw_i2c_handle_interrupt(host, kw_read_reg(reg_isr));
	if (host->state != state_idle) {
		host->timeout_timer.expires = jiffies + KW_POLL_TIMEOUT;
		add_timer(&host->timeout_timer);
	}
 skip:
	spin_unlock_irqrestore(&host->lock, flags);
}