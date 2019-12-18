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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int dlpar_attach_node (struct device_node*,struct device_node*) ; 
 struct device_node* dlpar_configure_connector (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  dlpar_free_cc_nodes (struct device_node*) ; 
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int add_dt_node(__be32 parent_phandle, __be32 drc_index)
{
	struct device_node *dn;
	struct device_node *parent_dn;
	int rc;

	parent_dn = of_find_node_by_phandle(be32_to_cpu(parent_phandle));
	if (!parent_dn)
		return -ENOENT;

	dn = dlpar_configure_connector(drc_index, parent_dn);
	if (!dn) {
		of_node_put(parent_dn);
		return -ENOENT;
	}

	rc = dlpar_attach_node(dn, parent_dn);
	if (rc)
		dlpar_free_cc_nodes(dn);

	of_node_put(parent_dn);
	return rc;
}