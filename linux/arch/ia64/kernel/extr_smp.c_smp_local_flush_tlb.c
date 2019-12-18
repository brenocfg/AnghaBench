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
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  acq ; 
 int /*<<< orphan*/  ia64_fetchadd (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 TYPE_1__* local_tlb_flush_counts ; 
 size_t smp_processor_id () ; 

void
smp_local_flush_tlb(void)
{
	/*
	 * Use atomic ops. Otherwise, the load/increment/store sequence from
	 * a "++" operation can have the line stolen between the load & store.
	 * The overhead of the atomic op in negligible in this case & offers
	 * significant benefit for the brief periods where lots of cpus
	 * are simultaneously flushing TLBs.
	 */
	ia64_fetchadd(1, &local_tlb_flush_counts[smp_processor_id()].count, acq);
	local_flush_tlb_all();
}