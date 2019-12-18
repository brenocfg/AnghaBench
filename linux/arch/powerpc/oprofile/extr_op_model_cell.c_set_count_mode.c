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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  count_mode; } ;
struct TYPE_4__ {TYPE_1__ pm_cntrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBE_COUNT_ALL_MODES ; 
 int /*<<< orphan*/  CBE_COUNT_HYPERVISOR_MODE ; 
 int /*<<< orphan*/  CBE_COUNT_PROBLEM_MODE ; 
 int /*<<< orphan*/  CBE_COUNT_SUPERVISOR_MODE ; 
 TYPE_2__ pm_regs ; 

__attribute__((used)) static inline void
set_count_mode(u32 kernel, u32 user)
{
	/*
	 * The user must specify user and kernel if they want them. If
	 *  neither is specified, OProfile will count in hypervisor mode.
	 *  pm_regs.pm_cntrl is a global
	 */
	if (kernel) {
		if (user)
			pm_regs.pm_cntrl.count_mode = CBE_COUNT_ALL_MODES;
		else
			pm_regs.pm_cntrl.count_mode =
				CBE_COUNT_SUPERVISOR_MODE;
	} else {
		if (user)
			pm_regs.pm_cntrl.count_mode = CBE_COUNT_PROBLEM_MODE;
		else
			pm_regs.pm_cntrl.count_mode =
				CBE_COUNT_HYPERVISOR_MODE;
	}
}