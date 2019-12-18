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
struct ipmi_smi {unsigned int last_watch_mask; int /*<<< orphan*/  watch_lock; int /*<<< orphan*/  send_info; TYPE_1__* handlers; scalar_t__ command_waiters; scalar_t__ watchdog_waiters; scalar_t__ response_waiters; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_need_watch ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 unsigned int IPMI_WATCH_MASK_CHECK_COMMANDS ; 
 unsigned int IPMI_WATCH_MASK_CHECK_MESSAGES ; 
 unsigned int IPMI_WATCH_MASK_CHECK_WATCHDOG ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void smi_remove_watch(struct ipmi_smi *intf, unsigned int flags)
{
	unsigned long iflags;

	if (!intf->handlers->set_need_watch)
		return;

	spin_lock_irqsave(&intf->watch_lock, iflags);
	if (flags & IPMI_WATCH_MASK_CHECK_MESSAGES)
		intf->response_waiters--;

	if (flags & IPMI_WATCH_MASK_CHECK_WATCHDOG)
		intf->watchdog_waiters--;

	if (flags & IPMI_WATCH_MASK_CHECK_COMMANDS)
		intf->command_waiters--;

	flags = 0;
	if (intf->response_waiters)
		flags |= IPMI_WATCH_MASK_CHECK_MESSAGES;
	if (intf->watchdog_waiters)
		flags |= IPMI_WATCH_MASK_CHECK_WATCHDOG;
	if (intf->command_waiters)
		flags |= IPMI_WATCH_MASK_CHECK_COMMANDS;

	if (intf->last_watch_mask != flags) {
		intf->last_watch_mask = flags;
		intf->handlers->set_need_watch(intf->send_info,
					       intf->last_watch_mask);
	}
	spin_unlock_irqrestore(&intf->watch_lock, iflags);
}