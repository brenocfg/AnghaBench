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
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ xmlGetNoNsProp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

char * xml_node_get_attr_value(struct xml_node_ctx *ctx, xml_node_t *node,
			       char *name)
{
	return (char *) xmlGetNoNsProp((xmlNodePtr) node,
				       (const xmlChar *) name);
}