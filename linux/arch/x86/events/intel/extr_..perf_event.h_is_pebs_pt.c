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
struct TYPE_2__ {int flags; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int PERF_X86_EVENT_PEBS_VIA_PT ; 

__attribute__((used)) static inline int is_pebs_pt(struct perf_event *event)
{
	return !!(event->hw.flags & PERF_X86_EVENT_PEBS_VIA_PT);
}