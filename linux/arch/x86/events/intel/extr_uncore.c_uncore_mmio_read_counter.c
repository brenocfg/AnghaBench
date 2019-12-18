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
struct intel_uncore_box {scalar_t__ io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  readq (scalar_t__) ; 

u64 uncore_mmio_read_counter(struct intel_uncore_box *box,
			     struct perf_event *event)
{
	if (!box->io_addr)
		return 0;

	return readq(box->io_addr + event->hw.event_base);
}