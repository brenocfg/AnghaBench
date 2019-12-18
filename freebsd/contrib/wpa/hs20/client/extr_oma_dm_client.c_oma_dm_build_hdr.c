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
struct hs20_osu_client {char const* devid; int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 char* int2str (int) ; 
 int /*<<< orphan*/  oma_dm_add_locuri (struct hs20_osu_client*,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * xml_node_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * xml_node_create_root (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  xml_node_create_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static xml_node_t * oma_dm_build_hdr(struct hs20_osu_client *ctx,
				     const char *url, int msgid)
{
	xml_node_t *syncml, *synchdr;
	xml_namespace_t *ns;

	if (!ctx->devid) {
		wpa_printf(MSG_ERROR,
			   "DevId from devinfo.xml is not available - cannot use OMA DM");
		return NULL;
	}

	syncml = xml_node_create_root(ctx->xml, "SYNCML:SYNCML1.2", NULL, &ns,
				      "SyncML");

	synchdr = xml_node_create(ctx->xml, syncml, NULL, "SyncHdr");
	xml_node_create_text(ctx->xml, synchdr, NULL, "VerDTD", "1.2");
	xml_node_create_text(ctx->xml, synchdr, NULL, "VerProto", "DM/1.2");
	xml_node_create_text(ctx->xml, synchdr, NULL, "SessionID", "1");
	xml_node_create_text(ctx->xml, synchdr, NULL, "MsgID", int2str(msgid));

	oma_dm_add_locuri(ctx, synchdr, "Target", url);
	oma_dm_add_locuri(ctx, synchdr, "Source", ctx->devid);

	return syncml;
}