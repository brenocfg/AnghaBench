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
 scalar_t__ uv_read_rtc (int /*<<< orphan*/ *) ; 
 int uv_rtc_set_timer (int,scalar_t__) ; 

__attribute__((used)) static int uv_rtc_next_event(unsigned long delta,
			     struct clock_event_device *ced)
{
	int ced_cpu = cpumask_first(ced->cpumask);

	return uv_rtc_set_timer(ced_cpu, delta + uv_read_rtc(NULL));
}