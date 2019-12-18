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
typedef  int u32 ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int GT_READ (int /*<<< orphan*/ ) ; 
 int GT_TC_CONTROL_ENTC0_MSK ; 
 int /*<<< orphan*/  GT_TC_CONTROL_OFS ; 
 int GT_TC_CONTROL_SELTC0_MSK ; 
 int /*<<< orphan*/  GT_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gt641xx_timer_lock ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gt641xx_timer0_set_periodic(struct clock_event_device *evt)
{
	u32 ctrl;

	raw_spin_lock(&gt641xx_timer_lock);

	ctrl = GT_READ(GT_TC_CONTROL_OFS);
	ctrl |= GT_TC_CONTROL_ENTC0_MSK | GT_TC_CONTROL_SELTC0_MSK;
	GT_WRITE(GT_TC_CONTROL_OFS, ctrl);

	raw_spin_unlock(&gt641xx_timer_lock);
	return 0;
}