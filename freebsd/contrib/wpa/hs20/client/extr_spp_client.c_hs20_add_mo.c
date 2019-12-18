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
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  URN_HS20_PPS ; 
 int /*<<< orphan*/  debug_dump_node (struct hs20_osu_client*,char*,int /*<<< orphan*/ *) ; 
 char* get_spp_attr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int hs20_add_pps_mo (struct hs20_osu_client*,char*,int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xml_node_get_attr_value_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hs20_add_mo(struct hs20_osu_client *ctx, xml_node_t *add_mo,
		       char *fname, size_t fname_len)
{
	char *uri, *urn;
	int ret;

	debug_dump_node(ctx, "Received addMO", add_mo);

	urn = get_spp_attr_value(ctx->xml, add_mo, "moURN");
	if (urn == NULL) {
		wpa_printf(MSG_INFO, "[hs20] No moURN in addMO");
		return -1;
	}
	wpa_printf(MSG_INFO, "addMO - moURN: '%s'", urn);
	if (strcasecmp(urn, URN_HS20_PPS) != 0) {
		wpa_printf(MSG_INFO, "[hs20] Unsupported MO in addMO");
		xml_node_get_attr_value_free(ctx->xml, urn);
		return -1;
	}
	xml_node_get_attr_value_free(ctx->xml, urn);

	uri = get_spp_attr_value(ctx->xml, add_mo, "managementTreeURI");
	if (uri == NULL) {
		wpa_printf(MSG_INFO, "[hs20] No managementTreeURI in addMO");
		return -1;
	}
	wpa_printf(MSG_INFO, "addMO - managementTreeURI: '%s'", uri);

	ret = hs20_add_pps_mo(ctx, uri, add_mo, fname, fname_len);
	xml_node_get_attr_value_free(ctx->xml, uri);
	return ret;
}