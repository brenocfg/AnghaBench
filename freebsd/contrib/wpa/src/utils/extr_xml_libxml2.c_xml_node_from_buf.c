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
typedef  scalar_t__ xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ xmlCopyNode (scalar_t__,int) ; 
 scalar_t__ xmlDocGetRootElement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlParseMemory (char const*,int /*<<< orphan*/ ) ; 

xml_node_t * xml_node_from_buf(struct xml_node_ctx *ctx, const char *buf)
{
	xmlDocPtr doc;
	xmlNodePtr node;

	doc = xmlParseMemory(buf, strlen(buf));
	if (doc == NULL)
		return NULL;
	node = xmlDocGetRootElement(doc);
	node = xmlCopyNode(node, 1);
	xmlFreeDoc(doc);

	return (xml_node_t *) node;
}