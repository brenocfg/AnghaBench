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
 int /*<<< orphan*/  xmlNodeSetContent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void xml_node_set_text(struct xml_node_ctx *ctx, xml_node_t *node,
		       const char *value)
{
	/* TODO: escape XML special chars in value */
	xmlNodeSetContent((xmlNodePtr) node, (xmlChar *) value);
}