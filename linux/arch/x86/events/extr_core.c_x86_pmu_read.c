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
struct perf_event {int dummy; } ;
struct TYPE_2__ {void (* read ) (struct perf_event*) ;} ;

/* Variables and functions */
 void stub1 (struct perf_event*) ; 
 int /*<<< orphan*/  x86_perf_event_update (struct perf_event*) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static inline void x86_pmu_read(struct perf_event *event)
{
	if (x86_pmu.read)
		return x86_pmu.read(event);
	x86_perf_event_update(event);
}