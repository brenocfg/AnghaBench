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
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {unsigned int num; } ;

/* Variables and functions */
 unsigned int HPET_TN_32BIT ; 
 unsigned int HPET_TN_ENABLE ; 
 unsigned int HPET_TN_PERIODIC ; 
 int /*<<< orphan*/  HPET_Tn_CFG (unsigned int) ; 
 TYPE_1__* clockevent_to_channel (struct clock_event_device*) ; 
 unsigned int hpet_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpet_clkevt_set_state_oneshot(struct clock_event_device *evt)
{
	unsigned int channel = clockevent_to_channel(evt)->num;
	unsigned int cfg;

	cfg = hpet_readl(HPET_Tn_CFG(channel));
	cfg &= ~HPET_TN_PERIODIC;
	cfg |= HPET_TN_ENABLE | HPET_TN_32BIT;
	hpet_writel(cfg, HPET_Tn_CFG(channel));

	return 0;
}