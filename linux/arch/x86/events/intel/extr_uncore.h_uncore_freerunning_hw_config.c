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
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ is_freerunning_event (struct perf_event*) ; 

__attribute__((used)) static inline int uncore_freerunning_hw_config(struct intel_uncore_box *box,
					       struct perf_event *event)
{
	if (is_freerunning_event(event))
		return 0;

	return -EINVAL;
}