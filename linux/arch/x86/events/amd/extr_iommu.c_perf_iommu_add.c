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
struct TYPE_2__ {int state; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int get_next_avail_iommu_bnk_cntr (struct perf_event*) ; 
 int /*<<< orphan*/  perf_iommu_start (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_iommu_add(struct perf_event *event, int flags)
{
	int retval;

	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	/* request an iommu bank/counter */
	retval = get_next_avail_iommu_bnk_cntr(event);
	if (retval)
		return retval;

	if (flags & PERF_EF_START)
		perf_iommu_start(event, PERF_EF_RELOAD);

	return 0;
}