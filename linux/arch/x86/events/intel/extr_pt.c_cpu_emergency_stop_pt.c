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
struct TYPE_2__ {scalar_t__ event; } ;
struct pt {TYPE_1__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  pt_ctx ; 
 int /*<<< orphan*/  pt_event_stop (scalar_t__,int /*<<< orphan*/ ) ; 
 struct pt* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void cpu_emergency_stop_pt(void)
{
	struct pt *pt = this_cpu_ptr(&pt_ctx);

	if (pt->handle.event)
		pt_event_stop(pt->handle.event, PERF_EF_UPDATE);
}