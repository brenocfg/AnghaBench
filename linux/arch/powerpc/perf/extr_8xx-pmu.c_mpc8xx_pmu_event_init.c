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
struct perf_event {int dummy; } ;

/* Variables and functions */
 int event_type (struct perf_event*) ; 

__attribute__((used)) static int mpc8xx_pmu_event_init(struct perf_event *event)
{
	int type = event_type(event);

	if (type < 0)
		return type;
	return 0;
}