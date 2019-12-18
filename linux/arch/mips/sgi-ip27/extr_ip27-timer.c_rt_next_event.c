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
 int ETIME ; 
 unsigned long LOCAL_HUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCAL_HUB_S (scalar_t__,unsigned long) ; 
 int PI_COUNT_OFFSET ; 
 scalar_t__ PI_RT_COMPARE_A ; 
 int /*<<< orphan*/  PI_RT_COUNT ; 
 int cputoslice (unsigned int) ; 
 unsigned int smp_processor_id () ; 

__attribute__((used)) static int rt_next_event(unsigned long delta, struct clock_event_device *evt)
{
	unsigned int cpu = smp_processor_id();
	int slice = cputoslice(cpu);
	unsigned long cnt;

	cnt = LOCAL_HUB_L(PI_RT_COUNT);
	cnt += delta;
	LOCAL_HUB_S(PI_RT_COMPARE_A + PI_COUNT_OFFSET * slice, cnt);

	return LOCAL_HUB_L(PI_RT_COUNT) >= cnt ? -ETIME : 0;
}