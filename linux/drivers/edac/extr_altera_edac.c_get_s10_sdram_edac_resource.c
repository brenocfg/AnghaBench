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
struct resource {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_s10_sdram_edac_resource(struct device_node *np,
				       struct resource *res)
{
	struct device_node *parent;
	int ret;

	parent = of_parse_phandle(np, "altr,sdr-syscon", 0);
	if (!parent)
		return -ENODEV;

	ret = of_address_to_resource(parent, 0, res);
	of_node_put(parent);

	return ret;
}