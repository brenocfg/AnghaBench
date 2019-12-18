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
union hv_stimer_config {int enable; int auto_enable; int direct_mode; scalar_t__ as_uint64; int /*<<< orphan*/  sintx; int /*<<< orphan*/  apic_vector; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ direct_mode_enabled ; 
 int /*<<< orphan*/  hv_enable_stimer0_percpu_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_init_timer_config (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stimer0_irq ; 
 int /*<<< orphan*/  stimer0_message_sint ; 
 int /*<<< orphan*/  stimer0_vector ; 

__attribute__((used)) static int hv_ce_set_oneshot(struct clock_event_device *evt)
{
	union hv_stimer_config timer_cfg;

	timer_cfg.as_uint64 = 0;
	timer_cfg.enable = 1;
	timer_cfg.auto_enable = 1;
	if (direct_mode_enabled) {
		/*
		 * When it expires, the timer will directly interrupt
		 * on the specified hardware vector/IRQ.
		 */
		timer_cfg.direct_mode = 1;
		timer_cfg.apic_vector = stimer0_vector;
		hv_enable_stimer0_percpu_irq(stimer0_irq);
	} else {
		/*
		 * When it expires, the timer will generate a VMbus message,
		 * to be handled by the normal VMbus interrupt handler.
		 */
		timer_cfg.direct_mode = 0;
		timer_cfg.sintx = stimer0_message_sint;
	}
	hv_init_timer_config(0, timer_cfg.as_uint64);
	return 0;
}