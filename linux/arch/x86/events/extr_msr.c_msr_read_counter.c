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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ event_base; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdmsrl (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtsc_ordered () ; 

__attribute__((used)) static inline u64 msr_read_counter(struct perf_event *event)
{
	u64 now;

	if (event->hw.event_base)
		rdmsrl(event->hw.event_base, now);
	else
		now = rdtsc_ordered();

	return now;
}