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
struct clock_event_device {unsigned int rating; int /*<<< orphan*/  set_state_periodic; int /*<<< orphan*/  features; int /*<<< orphan*/  set_state_shutdown; int /*<<< orphan*/  set_next_event; int /*<<< orphan*/  set_state_oneshot; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct hpet_channel {int boot_cfg; int /*<<< orphan*/  cpu; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; struct clock_event_device evt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_FEAT_ONESHOT ; 
 int /*<<< orphan*/  CLOCK_EVT_FEAT_PERIODIC ; 
 int HPET_TN_PERIODIC ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_clkevt_set_next_event ; 
 int /*<<< orphan*/  hpet_clkevt_set_state_oneshot ; 
 int /*<<< orphan*/  hpet_clkevt_set_state_periodic ; 
 int /*<<< orphan*/  hpet_clkevt_set_state_shutdown ; 

__attribute__((used)) static void hpet_init_clockevent(struct hpet_channel *hc, unsigned int rating)
{
	struct clock_event_device *evt = &hc->evt;

	evt->rating		= rating;
	evt->irq		= hc->irq;
	evt->name		= hc->name;
	evt->cpumask		= cpumask_of(hc->cpu);
	evt->set_state_oneshot	= hpet_clkevt_set_state_oneshot;
	evt->set_next_event	= hpet_clkevt_set_next_event;
	evt->set_state_shutdown	= hpet_clkevt_set_state_shutdown;

	evt->features = CLOCK_EVT_FEAT_ONESHOT;
	if (hc->boot_cfg & HPET_TN_PERIODIC) {
		evt->features		|= CLOCK_EVT_FEAT_PERIODIC;
		evt->set_state_periodic	= hpet_clkevt_set_state_periodic;
	}
}