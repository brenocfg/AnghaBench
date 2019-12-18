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
struct of_phandle_args {struct device_node* np; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 

__attribute__((used)) static struct device_node *_get_component_node(struct device_node *node, int i)
{
	int rc;
	struct of_phandle_args clkspec;

	rc = of_parse_phandle_with_args(node, "clocks", "#clock-cells", i,
					&clkspec);
	if (rc)
		return NULL;

	return clkspec.np;
}