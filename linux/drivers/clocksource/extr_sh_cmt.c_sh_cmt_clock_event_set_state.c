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
struct sh_cmt_channel {int /*<<< orphan*/  index; TYPE_2__* cmt; } ;
struct clock_event_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_CLOCKEVENT ; 
 struct sh_cmt_channel* ced_to_sh_cmt (struct clock_event_device*) ; 
 scalar_t__ clockevent_state_oneshot (struct clock_event_device*) ; 
 scalar_t__ clockevent_state_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sh_cmt_clock_event_start (struct sh_cmt_channel*,int) ; 
 int /*<<< orphan*/  sh_cmt_stop (struct sh_cmt_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_cmt_clock_event_set_state(struct clock_event_device *ced,
					int periodic)
{
	struct sh_cmt_channel *ch = ced_to_sh_cmt(ced);

	/* deal with old setting first */
	if (clockevent_state_oneshot(ced) || clockevent_state_periodic(ced))
		sh_cmt_stop(ch, FLAG_CLOCKEVENT);

	dev_info(&ch->cmt->pdev->dev, "ch%u: used for %s clock events\n",
		 ch->index, periodic ? "periodic" : "oneshot");
	sh_cmt_clock_event_start(ch, periodic);
	return 0;
}