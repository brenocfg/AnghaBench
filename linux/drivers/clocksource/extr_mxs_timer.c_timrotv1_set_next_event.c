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
 scalar_t__ HW_TIMROT_TIMCOUNTn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 scalar_t__ mxs_timrot_base ; 

__attribute__((used)) static int timrotv1_set_next_event(unsigned long evt,
					struct clock_event_device *dev)
{
	/* timrot decrements the count */
	__raw_writel(evt, mxs_timrot_base + HW_TIMROT_TIMCOUNTn(0));

	return 0;
}