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
 scalar_t__ cns3xxx_tmr1 ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int cns3xxx_shutdown(struct clock_event_device *clk)
{
	writel(0, cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);
	return 0;
}