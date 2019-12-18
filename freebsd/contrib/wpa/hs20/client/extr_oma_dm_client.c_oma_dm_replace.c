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
struct hs20_osu_client {char* fqdn; int pps_updated; int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int DM_RESP_BAD_REQUEST ; 
 int DM_RESP_COMMAND_FAILED ; 
 int DM_RESP_NOT_FOUND ; 
 int DM_RESP_OK ; 
 int DM_RESP_PERMISSION_DENIED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  debug_dump_node (struct hs20_osu_client*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 char* oma_dm_get_target_locuri (struct hs20_osu_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 size_t os_strlen (char*) ; 
 scalar_t__ os_strncasecmp (char*,char*,int) ; 
 scalar_t__ os_strstr (char*,char*) ; 
 int /*<<< orphan*/ * tnds_to_mo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ update_pps_file (struct hs20_osu_client*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xml_node_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xml_node_from_buf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * xml_node_get_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xml_node_set_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int oma_dm_replace(struct hs20_osu_client *ctx, xml_node_t *replace,
			  xml_node_t *pps, const char *pps_fname)
{
	char *locuri, *pos;
	size_t fqdn_len;
	xml_node_t *node, *tnds, *unode, *pps_node, *parent;
	char *data;
	int use_tnds = 0;

	locuri = oma_dm_get_target_locuri(ctx, replace);
	if (locuri == NULL)
		return DM_RESP_BAD_REQUEST;

	wpa_printf(MSG_INFO, "Replace command target LocURI: %s", locuri);
	if (os_strncasecmp(locuri, "./Wi-Fi/", 8) != 0) {
		wpa_printf(MSG_INFO, "Do not allow Replace outside ./Wi-Fi");
		os_free(locuri);
		return DM_RESP_PERMISSION_DENIED;
	}
	pos = locuri + 8;

	if (ctx->fqdn == NULL) {
		os_free(locuri);
		return DM_RESP_COMMAND_FAILED;
	}
	fqdn_len = os_strlen(ctx->fqdn);
	if (os_strncasecmp(pos, ctx->fqdn, fqdn_len) != 0 ||
	    pos[fqdn_len] != '/') {
		wpa_printf(MSG_INFO, "Do not allow Replace outside ./Wi-Fi/%s",
			   ctx->fqdn);
		os_free(locuri);
		return DM_RESP_PERMISSION_DENIED;
	}
	pos += fqdn_len + 1;

	if (os_strncasecmp(pos, "PerProviderSubscription/", 24) != 0) {
		wpa_printf(MSG_INFO,
			   "Do not allow Replace outside ./Wi-Fi/%s/PerProviderSubscription",
			   ctx->fqdn);
		os_free(locuri);
		return DM_RESP_PERMISSION_DENIED;
	}
	pos += 24;

	wpa_printf(MSG_INFO, "Replace command for PPS node %s", pos);

	pps_node = get_node(ctx->xml, pps, pos);
	if (pps_node == NULL) {
		wpa_printf(MSG_INFO, "Specified PPS node not found");
		os_free(locuri);
		return DM_RESP_NOT_FOUND;
	}

	node = get_node(ctx->xml, replace, "Item/Meta/Type");
	if (node) {
		char *type;
		type = xml_node_get_text(ctx->xml, node);
		if (type == NULL) {
			wpa_printf(MSG_INFO, "Could not find type text");
			os_free(locuri);
			return DM_RESP_BAD_REQUEST;
		}
		use_tnds = node &&
			os_strstr(type, "application/vnd.syncml.dmtnds+xml");
	}

	node = get_node(ctx->xml, replace, "Item/Data");
	if (node == NULL) {
		wpa_printf(MSG_INFO, "No Replace/Item/Data found");
		os_free(locuri);
		return DM_RESP_BAD_REQUEST;
	}

	data = xml_node_get_text(ctx->xml, node);
	if (data == NULL) {
		wpa_printf(MSG_INFO, "Could not get Replace/Item/Data text");
		os_free(locuri);
		return DM_RESP_BAD_REQUEST;
	}

	wpa_printf(MSG_DEBUG, "Replace/Item/Data: %s", data);

	if (use_tnds) {
		tnds = xml_node_from_buf(ctx->xml, data);
		xml_node_get_text_free(ctx->xml, data);
		if (tnds == NULL) {
			wpa_printf(MSG_INFO,
				   "Could not parse Replace/Item/Data text");
			os_free(locuri);
			return DM_RESP_BAD_REQUEST;
		}

		unode = tnds_to_mo(ctx->xml, tnds);
		xml_node_free(ctx->xml, tnds);
		if (unode == NULL) {
			wpa_printf(MSG_INFO, "Could not parse TNDS text");
			os_free(locuri);
			return DM_RESP_BAD_REQUEST;
		}

		debug_dump_node(ctx, "Parsed TNDS", unode);

		parent = xml_node_get_parent(ctx->xml, pps_node);
		xml_node_detach(ctx->xml, pps_node);
		xml_node_add_child(ctx->xml, parent, unode);
	} else {
		xml_node_set_text(ctx->xml, pps_node, data);
		xml_node_get_text_free(ctx->xml, data);
	}

	os_free(locuri);

	if (update_pps_file(ctx, pps_fname, pps) < 0)
		return DM_RESP_COMMAND_FAILED;

	ctx->pps_updated = 1;

	return DM_RESP_OK;
}