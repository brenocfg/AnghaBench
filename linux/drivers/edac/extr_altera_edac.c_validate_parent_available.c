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
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_parent_available(struct device_node *np)
{
	struct device_node *parent;
	int ret = 0;

	/* SDRAM must be present for Linux (implied parent) */
	if (of_device_is_compatible(np, "altr,sdram-edac-s10"))
		return 0;

	/* Ensure parent device is enabled if parent node exists */
	parent = of_parse_phandle(np, "altr,ecc-parent", 0);
	if (parent && !of_device_is_available(parent))
		ret = -ENODEV;

	of_node_put(parent);
	return ret;
}