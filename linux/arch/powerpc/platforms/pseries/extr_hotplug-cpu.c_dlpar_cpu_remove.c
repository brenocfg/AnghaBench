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
 int dlpar_acquire_drc (int /*<<< orphan*/ ) ; 
 int dlpar_detach_node (struct device_node*) ; 
 int dlpar_offline_cpu (struct device_node*) ; 
 int /*<<< orphan*/  dlpar_online_cpu (struct device_node*) ; 
 int dlpar_release_drc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_warn (char*,struct device_node*,int,...) ; 

__attribute__((used)) static ssize_t dlpar_cpu_remove(struct device_node *dn, u32 drc_index)
{
	int rc;

	pr_debug("Attempting to remove CPU %pOFn, drc index: %x\n",
		 dn, drc_index);

	rc = dlpar_offline_cpu(dn);
	if (rc) {
		pr_warn("Failed to offline CPU %pOFn, rc: %d\n", dn, rc);
		return -EINVAL;
	}

	rc = dlpar_release_drc(drc_index);
	if (rc) {
		pr_warn("Failed to release drc (%x) for CPU %pOFn, rc: %d\n",
			drc_index, dn, rc);
		dlpar_online_cpu(dn);
		return rc;
	}

	rc = dlpar_detach_node(dn);
	if (rc) {
		int saved_rc = rc;

		pr_warn("Failed to detach CPU %pOFn, rc: %d", dn, rc);

		rc = dlpar_acquire_drc(drc_index);
		if (!rc)
			dlpar_online_cpu(dn);

		return saved_rc;
	}

	pr_debug("Successfully removed CPU, drc index: %x\n", drc_index);
	return 0;
}