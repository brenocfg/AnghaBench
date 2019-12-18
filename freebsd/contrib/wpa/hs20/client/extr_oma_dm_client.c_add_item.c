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
 int /*<<< orphan*/  oma_dm_add_locuri (struct hs20_osu_client*,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * xml_node_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xml_node_create_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  xml_node_create_text_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*) ; 

__attribute__((used)) static void add_item(struct hs20_osu_client *ctx, xml_node_t *parent,
		     const char *locuri, const char *data)
{
	xml_node_t *item, *node;

	item = xml_node_create(ctx->xml, parent, NULL, "Item");
	oma_dm_add_locuri(ctx, item, "Source", locuri);
	node = xml_node_create(ctx->xml, item, NULL, "Meta");
	xml_node_create_text_ns(ctx->xml, node, "syncml:metinf", "Format",
				"Chr");
	xml_node_create_text_ns(ctx->xml, node, "syncml:metinf", "Type",
				"text/plain");
	xml_node_create_text(ctx->xml, item, NULL, "Data", data);
}