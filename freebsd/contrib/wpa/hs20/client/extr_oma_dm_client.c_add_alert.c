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
struct hs20_osu_client {int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  int2str (int) ; 
 int /*<<< orphan*/  oma_dm_add_cmdid (struct hs20_osu_client*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xml_node_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xml_node_create_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xml_node_t * add_alert(struct hs20_osu_client *ctx, xml_node_t *parent,
			      int cmdid, int data)
{
	xml_node_t *node;

	node = xml_node_create(ctx->xml, parent, NULL, "Alert");
	if (node == NULL)
		return NULL;
	oma_dm_add_cmdid(ctx, node, cmdid);
	xml_node_create_text(ctx->xml, node, NULL, "Data", int2str(data));

	return node;
}