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
typedef  int __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_LEVEL ; 
 int THERM_LOG_THRESHOLD0 ; 
 int THERM_LOG_THRESHOLD1 ; 
 int /*<<< orphan*/  platform_thermal_notify (int) ; 
 scalar_t__ thresh_event_valid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void notify_thresholds(__u64 msr_val)
{
	/* check whether the interrupt handler is defined;
	 * otherwise simply return
	 */
	if (!platform_thermal_notify)
		return;

	/* lower threshold reached */
	if ((msr_val & THERM_LOG_THRESHOLD0) &&
			thresh_event_valid(CORE_LEVEL, 0))
		platform_thermal_notify(msr_val);
	/* higher threshold reached */
	if ((msr_val & THERM_LOG_THRESHOLD1) &&
			thresh_event_valid(CORE_LEVEL, 1))
		platform_thermal_notify(msr_val);
}