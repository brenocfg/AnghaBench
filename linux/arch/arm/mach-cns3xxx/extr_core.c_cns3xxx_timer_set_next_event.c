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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TIMER1_2_CONTROL_OFFSET ; 
 scalar_t__ TIMER1_AUTO_RELOAD_OFFSET ; 
 scalar_t__ cns3xxx_tmr1 ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int cns3xxx_timer_set_next_event(unsigned long evt,
					struct clock_event_device *unused)
{
	unsigned long ctrl = readl(cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);

	writel(evt, cns3xxx_tmr1 + TIMER1_AUTO_RELOAD_OFFSET);
	writel(ctrl | (1 << 0), cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);

	return 0;
}