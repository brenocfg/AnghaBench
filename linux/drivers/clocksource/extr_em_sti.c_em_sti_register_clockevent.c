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
struct clock_event_device {int rating; int /*<<< orphan*/  set_state_oneshot; int /*<<< orphan*/  set_state_shutdown; int /*<<< orphan*/  set_next_event; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  features; int /*<<< orphan*/  name; } ;
struct em_sti_priv {int /*<<< orphan*/  rate; TYPE_1__* pdev; struct clock_event_device ced; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_FEAT_ONESHOT ; 
 int /*<<< orphan*/  clockevents_config_and_register (struct clock_event_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  em_sti_clock_event_next ; 
 int /*<<< orphan*/  em_sti_clock_event_set_oneshot ; 
 int /*<<< orphan*/  em_sti_clock_event_shutdown ; 

__attribute__((used)) static void em_sti_register_clockevent(struct em_sti_priv *p)
{
	struct clock_event_device *ced = &p->ced;

	ced->name = dev_name(&p->pdev->dev);
	ced->features = CLOCK_EVT_FEAT_ONESHOT;
	ced->rating = 200;
	ced->cpumask = cpu_possible_mask;
	ced->set_next_event = em_sti_clock_event_next;
	ced->set_state_shutdown = em_sti_clock_event_shutdown;
	ced->set_state_oneshot = em_sti_clock_event_set_oneshot;

	dev_info(&p->pdev->dev, "used for clock events\n");

	clockevents_config_and_register(ced, p->rate, 2, 0xffffffff);
}