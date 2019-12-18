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
 int ENODEV ; 
 int /*<<< orphan*/  icp_hv_ops ; 
 int /*<<< orphan*/ * icp_ops ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 

int icp_hv_init(void)
{
	struct device_node *np;

	np = of_find_compatible_node(NULL, NULL, "ibm,ppc-xicp");
	if (!np)
		np = of_find_node_by_type(NULL,
				    "PowerPC-External-Interrupt-Presentation");
	if (!np)
		return -ENODEV;

	icp_ops = &icp_hv_ops;

	return 0;
}