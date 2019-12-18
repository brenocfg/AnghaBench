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
typedef  int /*<<< orphan*/  xml_node_t ;
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPP_NS_URI ; 
 char* xml_node_get_attr_value_ns (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char * get_spp_attr_value(struct xml_node_ctx *ctx, xml_node_t *node,
				 char *attr_name)
{
	return xml_node_get_attr_value_ns(ctx, node, SPP_NS_URI, attr_name);
}