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
struct intel_excl_cntrs {int core_id; scalar_t__ refcnt; } ;
struct cpu_hw_events {struct intel_excl_cntrs* constraint_list; struct intel_excl_cntrs* excl_cntrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct intel_excl_cntrs*) ; 

__attribute__((used)) static void free_excl_cntrs(struct cpu_hw_events *cpuc)
{
	struct intel_excl_cntrs *c;

	c = cpuc->excl_cntrs;
	if (c) {
		if (c->core_id == -1 || --c->refcnt == 0)
			kfree(c);
		cpuc->excl_cntrs = NULL;
	}

	kfree(cpuc->constraint_list);
	cpuc->constraint_list = NULL;
}