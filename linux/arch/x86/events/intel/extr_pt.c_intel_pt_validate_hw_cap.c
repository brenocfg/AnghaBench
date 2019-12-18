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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum pt_capabilities { ____Placeholder_pt_capabilities } pt_capabilities ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_validate_cap (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ pt_pmu ; 

u32 intel_pt_validate_hw_cap(enum pt_capabilities cap)
{
	return intel_pt_validate_cap(pt_pmu.caps, cap);
}