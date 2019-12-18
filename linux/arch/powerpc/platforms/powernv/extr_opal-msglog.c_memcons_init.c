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
typedef  int /*<<< orphan*/  u64 ;
struct memcons {int /*<<< orphan*/  magic; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ MEMCONS_MAGIC ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u64 (struct device_node*,char const*,int /*<<< orphan*/ *) ; 
 struct memcons* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

struct memcons *memcons_init(struct device_node *node, const char *mc_prop_name)
{
	u64 mcaddr;
	struct memcons *mc;

	if (of_property_read_u64(node, mc_prop_name, &mcaddr)) {
		pr_warn("%s property not found, no message log\n",
			mc_prop_name);
		goto out_err;
	}

	mc = phys_to_virt(mcaddr);
	if (!mc) {
		pr_warn("memory console address is invalid\n");
		goto out_err;
	}

	if (be64_to_cpu(mc->magic) != MEMCONS_MAGIC) {
		pr_warn("memory console version is invalid\n");
		goto out_err;
	}

	return mc;

out_err:
	return NULL;
}