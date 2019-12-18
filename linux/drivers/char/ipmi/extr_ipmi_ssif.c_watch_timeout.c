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
struct ssif_info {int req_flags; scalar_t__ watch_timeout; int /*<<< orphan*/  watch_timer; scalar_t__ stopping; } ;

/* Variables and functions */
 scalar_t__ SSIF_IDLE (struct ssif_info*) ; 
 struct ssif_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 unsigned long* ipmi_ssif_lock_cond (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  ipmi_ssif_unlock_cond (struct ssif_info*,unsigned long*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct ssif_info* ssif_info ; 
 int /*<<< orphan*/  start_flag_fetch (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  watch_timer ; 

__attribute__((used)) static void watch_timeout(struct timer_list *t)
{
	struct ssif_info *ssif_info = from_timer(ssif_info, t, watch_timer);
	unsigned long oflags, *flags;

	if (ssif_info->stopping)
		return;

	flags = ipmi_ssif_lock_cond(ssif_info, &oflags);
	if (ssif_info->watch_timeout) {
		mod_timer(&ssif_info->watch_timer,
			  jiffies + ssif_info->watch_timeout);
		if (SSIF_IDLE(ssif_info)) {
			start_flag_fetch(ssif_info, flags); /* Releases lock */
			return;
		}
		ssif_info->req_flags = true;
	}
	ipmi_ssif_unlock_cond(ssif_info, flags);
}