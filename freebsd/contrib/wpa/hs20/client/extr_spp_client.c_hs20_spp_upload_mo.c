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
struct hs20_osu_client {int /*<<< orphan*/  xml; int /*<<< orphan*/  http; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  URN_HS20_PPS ; 
 int /*<<< orphan*/  add_mo_container (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * build_spp_post_dev_data (struct hs20_osu_client*,int /*<<< orphan*/ **,char const*,char*) ; 
 int /*<<< orphan*/  debug_dump_node (struct hs20_osu_client*,char*,int /*<<< orphan*/ *) ; 
 char* get_spp_attr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hs20_spp_validate (struct hs20_osu_client*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * soap_send_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_attr_value_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static xml_node_t * hs20_spp_upload_mo(struct hs20_osu_client *ctx,
				       xml_node_t *cmd,
				       const char *session_id,
				       const char *pps_fname)
{
	xml_namespace_t *ns;
	xml_node_t *node, *ret_node;
	char *urn;

	urn = get_spp_attr_value(ctx->xml, cmd, "moURN");
	if (!urn) {
		wpa_printf(MSG_INFO, "No URN included");
		return NULL;
	}
	wpa_printf(MSG_INFO, "Upload MO request - URN=%s", urn);
	if (strcasecmp(urn, URN_HS20_PPS) != 0) {
		wpa_printf(MSG_INFO, "Unsupported moURN");
		xml_node_get_attr_value_free(ctx->xml, urn);
		return NULL;
	}
	xml_node_get_attr_value_free(ctx->xml, urn);

	if (!pps_fname) {
		wpa_printf(MSG_INFO, "PPS file name no known");
		return NULL;
	}

	node = build_spp_post_dev_data(ctx, &ns, session_id,
				       "MO upload");
	if (node == NULL)
		return NULL;
	add_mo_container(ctx->xml, ns, node, URN_HS20_PPS, pps_fname);

	ret_node = soap_send_receive(ctx->http, node);
	if (ret_node == NULL)
		return NULL;

	debug_dump_node(ctx, "Received response to MO upload", ret_node);

	if (hs20_spp_validate(ctx, ret_node, "sppPostDevDataResponse") < 0) {
		wpa_printf(MSG_INFO, "SPP validation failed");
		xml_node_free(ctx->xml, ret_node);
		return NULL;
	}

	return ret_node;
}