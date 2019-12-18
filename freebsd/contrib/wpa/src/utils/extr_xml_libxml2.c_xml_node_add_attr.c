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
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  scalar_t__ xmlAttrPtr ;
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ xmlNewNsProp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ xmlNewProp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int xml_node_add_attr(struct xml_node_ctx *ctx, xml_node_t *node,
		      xml_namespace_t *ns, const char *name, const char *value)
{
	xmlAttrPtr attr;

	if (ns) {
		attr = xmlNewNsProp((xmlNodePtr) node, (xmlNsPtr) ns,
				    (const xmlChar *) name,
				    (const xmlChar *) value);
	} else {
		attr = xmlNewProp((xmlNodePtr) node, (const xmlChar *) name,
				  (const xmlChar *) value);
	}

	return attr ? 0 : -1;
}