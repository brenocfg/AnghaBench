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
 int /*<<< orphan*/ * get_first_child_node (struct xml_node_ctx*,int /*<<< orphan*/ *,char const*) ; 
 char* xml_node_get_text (struct xml_node_ctx*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char * get_node_text(struct xml_node_ctx *ctx, xml_node_t *node,
			    const char *node_name)
{
	node = get_first_child_node(ctx, node, node_name);
	if (node == NULL)
		return NULL;
	return xml_node_get_text(ctx, node);
}