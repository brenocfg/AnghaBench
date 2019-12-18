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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DM_GENERIC_ALERT ; 
 int /*<<< orphan*/  DM_URI_PPS ; 
 int /*<<< orphan*/ * add_alert (struct hs20_osu_client*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oma_dm_add_locuri (struct hs20_osu_client*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/ * xml_node_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xml_node_create_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  xml_node_create_text_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*) ; 

__attribute__((used)) static void oma_dm_add_hs20_generic_alert(struct hs20_osu_client *ctx,
					  xml_node_t *syncbody,
					  int cmdid, const char *oper,
					  const char *data)
{
	xml_node_t *node, *item;
	char buf[200];

	node = add_alert(ctx, syncbody, cmdid, DM_GENERIC_ALERT);

	item = xml_node_create(ctx->xml, node, NULL, "Item");
	oma_dm_add_locuri(ctx, item, "Source", DM_URI_PPS);
	node = xml_node_create(ctx->xml, item, NULL, "Meta");
	snprintf(buf, sizeof(buf), "Reversed-Domain-Name: %s", oper);
	xml_node_create_text_ns(ctx->xml, node, "syncml:metinf", "Type", buf);
	xml_node_create_text_ns(ctx->xml, node, "syncml:metinf", "Format",
				"xml");
	xml_node_create_text(ctx->xml, item, NULL, "Data", data);
}