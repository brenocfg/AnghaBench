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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int of_property_count_elems_of_size (struct device_node*,char*,int) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  xive_provision_cache ; 
 int xive_provision_chip_count ; 
 int /*<<< orphan*/  xive_provision_chips ; 
 int /*<<< orphan*/  xive_provision_size ; 

__attribute__((used)) static bool xive_parse_provisioning(struct device_node *np)
{
	int rc;

	if (of_property_read_u32(np, "ibm,xive-provision-page-size",
				 &xive_provision_size) < 0)
		return true;
	rc = of_property_count_elems_of_size(np, "ibm,xive-provision-chips", 4);
	if (rc < 0) {
		pr_err("Error %d getting provision chips array\n", rc);
		return false;
	}
	xive_provision_chip_count = rc;
	if (rc == 0)
		return true;

	xive_provision_chips = kcalloc(4, xive_provision_chip_count,
				       GFP_KERNEL);
	if (WARN_ON(!xive_provision_chips))
		return false;

	rc = of_property_read_u32_array(np, "ibm,xive-provision-chips",
					xive_provision_chips,
					xive_provision_chip_count);
	if (rc < 0) {
		pr_err("Error %d reading provision chips array\n", rc);
		return false;
	}

	xive_provision_cache = kmem_cache_create("xive-provision",
						 xive_provision_size,
						 xive_provision_size,
						 0, NULL);
	if (!xive_provision_cache) {
		pr_err("Failed to allocate provision cache\n");
		return false;
	}
	return true;
}