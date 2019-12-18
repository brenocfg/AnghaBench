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
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ xmlCopyNode (int /*<<< orphan*/ ,int) ; 

xml_node_t * xml_node_copy(struct xml_node_ctx *ctx, xml_node_t *node)
{
	if (node == NULL)
		return NULL;
	return (xml_node_t *) xmlCopyNode((xmlNodePtr) node, 1);
}