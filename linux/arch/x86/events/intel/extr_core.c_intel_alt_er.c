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
typedef  int u64 ;
struct TYPE_4__ {int flags; TYPE_1__* extra_regs; } ;
struct TYPE_3__ {int valid_mask; } ;

/* Variables and functions */
 int EXTRA_REG_RSP_0 ; 
 int EXTRA_REG_RSP_1 ; 
 int PMU_FL_HAS_RSP_1 ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static int intel_alt_er(int idx, u64 config)
{
	int alt_idx = idx;

	if (!(x86_pmu.flags & PMU_FL_HAS_RSP_1))
		return idx;

	if (idx == EXTRA_REG_RSP_0)
		alt_idx = EXTRA_REG_RSP_1;

	if (idx == EXTRA_REG_RSP_1)
		alt_idx = EXTRA_REG_RSP_0;

	if (config & ~x86_pmu.extra_regs[alt_idx].valid_mask)
		return idx;

	return alt_idx;
}