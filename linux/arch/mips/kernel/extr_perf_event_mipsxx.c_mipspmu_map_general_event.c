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
struct mips_perf_event {scalar_t__ cntr_mask; } ;
struct TYPE_2__ {struct mips_perf_event const** general_event_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct mips_perf_event const* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__ mipspmu ; 

__attribute__((used)) static const struct mips_perf_event *mipspmu_map_general_event(int idx)
{

	if ((*mipspmu.general_event_map)[idx].cntr_mask == 0)
		return ERR_PTR(-EOPNOTSUPP);
	return &(*mipspmu.general_event_map)[idx];
}