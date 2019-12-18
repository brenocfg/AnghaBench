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
 int /*<<< orphan*/  DM_CLIENT_INITIATED_MGMT ; 
 int /*<<< orphan*/  add_alert (struct hs20_osu_client*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_replace_devinfo (struct hs20_osu_client*,int /*<<< orphan*/ *,int) ; 
 char* mo_str (struct hs20_osu_client*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  oma_dm_add_hs20_generic_alert (struct hs20_osu_client*,int /*<<< orphan*/ *,int,char const*,char*) ; 
 int /*<<< orphan*/ * oma_dm_build_hdr (struct hs20_osu_client*,char const*,int) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/ * xml_node_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static xml_node_t * build_oma_dm_1(struct hs20_osu_client *ctx,
				   const char *url, int msgid, const char *oper)
{
	xml_node_t *syncml, *syncbody;
	char *str;
	int cmdid = 0;

	syncml = oma_dm_build_hdr(ctx, url, msgid);
	if (syncml == NULL)
		return NULL;

	syncbody = xml_node_create(ctx->xml, syncml, NULL, "SyncBody");
	if (syncbody == NULL) {
		xml_node_free(ctx->xml, syncml);
		return NULL;
	}

	cmdid++;
	add_alert(ctx, syncbody, cmdid, DM_CLIENT_INITIATED_MGMT);

	str = mo_str(ctx, NULL, "devdetail.xml");
	if (str == NULL) {
		xml_node_free(ctx->xml, syncml);
		return NULL;
	}
	cmdid++;
	oma_dm_add_hs20_generic_alert(ctx, syncbody, cmdid, oper, str);
	os_free(str);

	cmdid++;
	add_replace_devinfo(ctx, syncbody, cmdid);

	xml_node_create(ctx->xml, syncbody, NULL, "Final");

	return syncml;
}