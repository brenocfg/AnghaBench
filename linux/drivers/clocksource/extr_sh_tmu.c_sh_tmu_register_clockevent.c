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
struct clock_event_device {char const* name; int rating; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; int /*<<< orphan*/  set_state_oneshot; int /*<<< orphan*/  set_state_periodic; int /*<<< orphan*/  set_state_shutdown; int /*<<< orphan*/  set_next_event; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  features; } ;
struct sh_tmu_channel {int /*<<< orphan*/  irq; int /*<<< orphan*/  index; TYPE_2__* tmu; struct clock_event_device ced; } ;
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_FEAT_ONESHOT ; 
 int /*<<< orphan*/  CLOCK_EVT_FEAT_PERIODIC ; 
 int IRQF_IRQPOLL ; 
 int IRQF_NOBALANCING ; 
 int IRQF_TIMER ; 
 int /*<<< orphan*/  clockevents_config_and_register (struct clock_event_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sh_tmu_channel*) ; 
 int /*<<< orphan*/  sh_tmu_clock_event_next ; 
 int /*<<< orphan*/  sh_tmu_clock_event_resume ; 
 int /*<<< orphan*/  sh_tmu_clock_event_set_oneshot ; 
 int /*<<< orphan*/  sh_tmu_clock_event_set_periodic ; 
 int /*<<< orphan*/  sh_tmu_clock_event_shutdown ; 
 int /*<<< orphan*/  sh_tmu_clock_event_suspend ; 
 int /*<<< orphan*/  sh_tmu_interrupt ; 

__attribute__((used)) static void sh_tmu_register_clockevent(struct sh_tmu_channel *ch,
				       const char *name)
{
	struct clock_event_device *ced = &ch->ced;
	int ret;

	ced->name = name;
	ced->features = CLOCK_EVT_FEAT_PERIODIC;
	ced->features |= CLOCK_EVT_FEAT_ONESHOT;
	ced->rating = 200;
	ced->cpumask = cpu_possible_mask;
	ced->set_next_event = sh_tmu_clock_event_next;
	ced->set_state_shutdown = sh_tmu_clock_event_shutdown;
	ced->set_state_periodic = sh_tmu_clock_event_set_periodic;
	ced->set_state_oneshot = sh_tmu_clock_event_set_oneshot;
	ced->suspend = sh_tmu_clock_event_suspend;
	ced->resume = sh_tmu_clock_event_resume;

	dev_info(&ch->tmu->pdev->dev, "ch%u: used for clock events\n",
		 ch->index);

	clockevents_config_and_register(ced, ch->tmu->rate, 0x300, 0xffffffff);

	ret = request_irq(ch->irq, sh_tmu_interrupt,
			  IRQF_TIMER | IRQF_IRQPOLL | IRQF_NOBALANCING,
			  dev_name(&ch->tmu->pdev->dev), ch);
	if (ret) {
		dev_err(&ch->tmu->pdev->dev, "ch%u: failed to request irq %d\n",
			ch->index, ch->irq);
		return;
	}
}