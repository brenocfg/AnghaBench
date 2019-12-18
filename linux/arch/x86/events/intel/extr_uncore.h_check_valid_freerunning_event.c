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
struct TYPE_2__ {int /*<<< orphan*/  config; } ;
struct perf_event {TYPE_1__ hw; } ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 unsigned int uncore_freerunning_idx (int /*<<< orphan*/ ) ; 
 unsigned int uncore_freerunning_type (int /*<<< orphan*/ ) ; 
 unsigned int uncore_num_freerunning (struct intel_uncore_box*,struct perf_event*) ; 
 unsigned int uncore_num_freerunning_types (struct intel_uncore_box*,struct perf_event*) ; 

__attribute__((used)) static inline bool check_valid_freerunning_event(struct intel_uncore_box *box,
						 struct perf_event *event)
{
	unsigned int type = uncore_freerunning_type(event->hw.config);
	unsigned int idx = uncore_freerunning_idx(event->hw.config);

	return (type < uncore_num_freerunning_types(box, event)) &&
	       (idx < uncore_num_freerunning(box, event));
}