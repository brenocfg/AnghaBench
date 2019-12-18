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
struct intel_excl_cntrs {int core_id; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 struct intel_excl_cntrs* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct intel_excl_cntrs *allocate_excl_cntrs(int cpu)
{
	struct intel_excl_cntrs *c;

	c = kzalloc_node(sizeof(struct intel_excl_cntrs),
			 GFP_KERNEL, cpu_to_node(cpu));
	if (c) {
		raw_spin_lock_init(&c->lock);
		c->core_id = -1;
	}
	return c;
}