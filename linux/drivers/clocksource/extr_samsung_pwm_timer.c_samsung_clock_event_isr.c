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
typedef  int u32 ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {scalar_t__ has_tint_cstat; } ;
struct TYPE_4__ {int event_id; scalar_t__ base; TYPE_1__ variant; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ REG_TINT_CSTAT ; 
 TYPE_2__ pwm ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t samsung_clock_event_isr(int irq, void *dev_id)
{
	struct clock_event_device *evt = dev_id;

	if (pwm.variant.has_tint_cstat) {
		u32 mask = (1 << pwm.event_id);
		writel(mask | (mask << 5), pwm.base + REG_TINT_CSTAT);
	}

	evt->event_handler(evt);

	return IRQ_HANDLED;
}