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
struct clock_event_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ has_tint_cstat; } ;
struct TYPE_4__ {int event_id; scalar_t__ base; TYPE_1__ variant; int /*<<< orphan*/  tdiv; int /*<<< orphan*/  tscaler_div; } ;

/* Variables and functions */
 scalar_t__ REG_TINT_CSTAT ; 
 TYPE_2__ pwm ; 
 int /*<<< orphan*/  samsung_timer_set_divisor (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  samsung_timer_set_prescale (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void samsung_clockevent_resume(struct clock_event_device *cev)
{
	samsung_timer_set_prescale(pwm.event_id, pwm.tscaler_div);
	samsung_timer_set_divisor(pwm.event_id, pwm.tdiv);

	if (pwm.variant.has_tint_cstat) {
		u32 mask = (1 << pwm.event_id);
		writel(mask | (mask << 5), pwm.base + REG_TINT_CSTAT);
	}
}