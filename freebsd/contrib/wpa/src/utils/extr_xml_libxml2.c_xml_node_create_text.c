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
typedef  int /*<<< orphan*/  xml_namespace_t ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  scalar_t__ xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ xmlNewTextChild (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

xml_node_t * xml_node_create_text(struct xml_node_ctx *ctx,
				  xml_node_t *parent, xml_namespace_t *ns,
				  const char *name, const char *value)
{
	xmlNodePtr node;
	node = xmlNewTextChild((xmlNodePtr) parent, (xmlNsPtr) ns,
			       (const xmlChar *) name, (const xmlChar *) value);
	return (xml_node_t *) node;
}