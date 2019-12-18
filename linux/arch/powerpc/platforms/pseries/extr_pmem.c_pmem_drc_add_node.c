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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int dlpar_acquire_drc (int /*<<< orphan*/ ) ; 
 int dlpar_attach_node (struct device_node*,int /*<<< orphan*/ ) ; 
 struct device_node* dlpar_configure_connector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlpar_free_cc_nodes (struct device_node*) ; 
 scalar_t__ dlpar_release_drc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmem_node ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  pr_info (char*,struct device_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pmem_drc_add_node(u32 drc_index)
{
	struct device_node *dn;
	int rc;

	pr_debug("Attempting to add pmem node, drc index: %x\n", drc_index);

	rc = dlpar_acquire_drc(drc_index);
	if (rc) {
		pr_err("Failed to acquire DRC, rc: %d, drc index: %x\n",
			rc, drc_index);
		return -EINVAL;
	}

	dn = dlpar_configure_connector(cpu_to_be32(drc_index), pmem_node);
	if (!dn) {
		pr_err("configure-connector failed for drc %x\n", drc_index);
		dlpar_release_drc(drc_index);
		return -EINVAL;
	}

	/* NB: The of reconfig notifier creates platform device from the node */
	rc = dlpar_attach_node(dn, pmem_node);
	if (rc) {
		pr_err("Failed to attach node %pOF, rc: %d, drc index: %x\n",
			dn, rc, drc_index);

		if (dlpar_release_drc(drc_index))
			dlpar_free_cc_nodes(dn);

		return rc;
	}

	pr_info("Successfully added %pOF, drc index: %x\n", dn, drc_index);

	return 0;
}