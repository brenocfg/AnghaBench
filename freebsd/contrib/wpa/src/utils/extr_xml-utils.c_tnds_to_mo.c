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
 int /*<<< orphan*/ * get_first_child_node (struct xml_node_ctx*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ os_strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * tnds_to_mo_iter (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* xml_node_get_localname (struct xml_node_ctx*,int /*<<< orphan*/ *) ; 

xml_node_t * tnds_to_mo(struct xml_node_ctx *ctx, xml_node_t *tnds)
{
	const char *name;
	xml_node_t *node;

	name = xml_node_get_localname(ctx, tnds);
	if (name == NULL || os_strcmp(name, "MgmtTree") != 0)
		return NULL;

	node = get_first_child_node(ctx, tnds, "Node");
	if (!node)
		return NULL;
	return tnds_to_mo_iter(ctx, NULL, node, NULL);
}