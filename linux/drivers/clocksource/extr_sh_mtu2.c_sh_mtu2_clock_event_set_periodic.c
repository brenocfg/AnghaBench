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
struct sh_mtu2_channel {int /*<<< orphan*/  index; TYPE_2__* mtu; } ;
struct clock_event_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct sh_mtu2_channel* ced_to_sh_mtu2 (struct clock_event_device*) ; 
 scalar_t__ clockevent_state_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mtu2_disable (struct sh_mtu2_channel*) ; 
 int /*<<< orphan*/  sh_mtu2_enable (struct sh_mtu2_channel*) ; 

__attribute__((used)) static int sh_mtu2_clock_event_set_periodic(struct clock_event_device *ced)
{
	struct sh_mtu2_channel *ch = ced_to_sh_mtu2(ced);

	if (clockevent_state_periodic(ced))
		sh_mtu2_disable(ch);

	dev_info(&ch->mtu->pdev->dev, "ch%u: used for periodic clock events\n",
		 ch->index);
	sh_mtu2_enable(ch);
	return 0;
}