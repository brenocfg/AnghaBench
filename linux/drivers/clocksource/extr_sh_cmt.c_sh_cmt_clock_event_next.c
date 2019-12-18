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
struct sh_cmt_channel {int flags; unsigned long next_match_value; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FLAG_IRQCONTEXT ; 
 struct sh_cmt_channel* ced_to_sh_cmt (struct clock_event_device*) ; 
 int /*<<< orphan*/  clockevent_state_oneshot (struct clock_event_device*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sh_cmt_set_next (struct sh_cmt_channel*,unsigned long) ; 

__attribute__((used)) static int sh_cmt_clock_event_next(unsigned long delta,
				   struct clock_event_device *ced)
{
	struct sh_cmt_channel *ch = ced_to_sh_cmt(ced);

	BUG_ON(!clockevent_state_oneshot(ced));
	if (likely(ch->flags & FLAG_IRQCONTEXT))
		ch->next_match_value = delta - 1;
	else
		sh_cmt_set_next(ch, delta - 1);

	return 0;
}