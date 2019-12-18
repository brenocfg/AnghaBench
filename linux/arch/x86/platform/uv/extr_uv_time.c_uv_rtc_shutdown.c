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
struct clock_event_device {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_rtc_unset_timer (int,int) ; 

__attribute__((used)) static int uv_rtc_shutdown(struct clock_event_device *evt)
{
	int ced_cpu = cpumask_first(evt->cpumask);

	uv_rtc_unset_timer(ced_cpu, 1);
	return 0;
}