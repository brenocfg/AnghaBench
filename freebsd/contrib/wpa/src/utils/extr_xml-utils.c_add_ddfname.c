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
 int /*<<< orphan*/ * xml_node_create (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xml_node_create_text (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int add_ddfname(struct xml_node_ctx *ctx, xml_node_t *parent,
		       const char *urn)
{
	xml_node_t *node;

	node = xml_node_create(ctx, parent, NULL, "RTProperties");
	if (node == NULL)
		return -1;
	node = xml_node_create(ctx, node, NULL, "Type");
	if (node == NULL)
		return -1;
	xml_node_create_text(ctx, node, NULL, "DDFName", urn);
	return 0;
}