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
struct TYPE_3__ {int /*<<< orphan*/  rmid; } ;
struct rdtgroup {TYPE_1__ mon; int /*<<< orphan*/  closid; } ;
struct TYPE_4__ {int /*<<< orphan*/  default_rmid; int /*<<< orphan*/  default_closid; } ;

/* Variables and functions */
 TYPE_2__ pqr_state ; 
 int /*<<< orphan*/  resctrl_sched_in () ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_cpu_closid_rmid(void *info)
{
	struct rdtgroup *r = info;

	if (r) {
		this_cpu_write(pqr_state.default_closid, r->closid);
		this_cpu_write(pqr_state.default_rmid, r->mon.rmid);
	}

	/*
	 * We cannot unconditionally write the MSR because the current
	 * executing task might have its own closid selected. Just reuse
	 * the context switch code.
	 */
	resctrl_sched_in();
}