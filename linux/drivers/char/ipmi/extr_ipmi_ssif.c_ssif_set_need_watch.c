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
struct ssif_info {long watch_timeout; int /*<<< orphan*/  watch_timer; } ;

/* Variables and functions */
 unsigned int IPMI_WATCH_MASK_CHECK_MESSAGES ; 
 long SSIF_WATCH_MSG_TIMEOUT ; 
 long SSIF_WATCH_WATCHDOG_TIMEOUT ; 
 unsigned long* ipmi_ssif_lock_cond (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  ipmi_ssif_unlock_cond (struct ssif_info*,unsigned long*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void ssif_set_need_watch(void *send_info, unsigned int watch_mask)
{
	struct ssif_info *ssif_info = (struct ssif_info *) send_info;
	unsigned long oflags, *flags;
	long timeout = 0;

	if (watch_mask & IPMI_WATCH_MASK_CHECK_MESSAGES)
		timeout = SSIF_WATCH_MSG_TIMEOUT;
	else if (watch_mask)
		timeout = SSIF_WATCH_WATCHDOG_TIMEOUT;

	flags = ipmi_ssif_lock_cond(ssif_info, &oflags);
	if (timeout != ssif_info->watch_timeout) {
		ssif_info->watch_timeout = timeout;
		if (ssif_info->watch_timeout)
			mod_timer(&ssif_info->watch_timer,
				  jiffies + ssif_info->watch_timeout);
	}
	ipmi_ssif_unlock_cond(ssif_info, flags);
}