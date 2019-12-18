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
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct clock_event_device evt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ccount_timer ; 
 int /*<<< orphan*/  get_linux_timer () ; 
 int /*<<< orphan*/  platform_heartbeat () ; 
 int /*<<< orphan*/  set_linux_timer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 TYPE_1__* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *evt = &this_cpu_ptr(&ccount_timer)->evt;

	set_linux_timer(get_linux_timer());
	evt->event_handler(evt);

	/* Allow platform to do something useful (Wdog). */
	platform_heartbeat();

	return IRQ_HANDLED;
}