#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct pebs_record_nhm {int /*<<< orphan*/  status; } ;
struct pebs_basic {int /*<<< orphan*/  applicable_counters; } ;
struct TYPE_3__ {int pebs_format; } ;
struct TYPE_4__ {TYPE_1__ intel_cap; } ;

/* Variables and functions */
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static inline u64 get_pebs_status(void *n)
{
	if (x86_pmu.intel_cap.pebs_format < 4)
		return ((struct pebs_record_nhm *)n)->status;
	return ((struct pebs_basic *)n)->applicable_counters;
}