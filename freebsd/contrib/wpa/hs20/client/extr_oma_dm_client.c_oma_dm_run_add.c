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
struct hs20_osu_client {char const* fqdn; int pps_updated; int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int DM_RESP_ALREADY_EXISTS ; 
 int DM_RESP_BAD_REQUEST ; 
 int DM_RESP_COMMAND_FAILED ; 
 int DM_RESP_OK ; 
 int DM_RESP_PERMISSION_DENIED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  debug_dump_node (struct hs20_osu_client*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strchr (char*,char) ; 
 char* os_strdup (char const*) ; 
 int /*<<< orphan*/  os_strlcpy (char*,char const*,size_t) ; 
 size_t os_strlen (char const*) ; 
 scalar_t__ os_strncasecmp (char const*,char*,int) ; 
 char* os_strrchr (char*,char) ; 
 scalar_t__ os_strstr (char*,char*) ; 
 int /*<<< orphan*/ * tnds_to_mo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ update_pps_file (struct hs20_osu_client*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xml_node_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xml_node_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xml_node_from_buf (int /*<<< orphan*/ ,char*) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int oma_dm_run_add(struct hs20_osu_client *ctx, const char *locuri,
			  xml_node_t *add, xml_node_t *pps,
			  const char *pps_fname)
{
	const char *pos;
	size_t fqdn_len;
	xml_node_t *node, *tnds, *unode, *pps_node;
	char *data, *uri, *upos, *end;
	int use_tnds = 0;
	size_t uri_len;

	wpa_printf(MSG_INFO, "Add command target LocURI: %s", locuri);

	if (os_strncasecmp(locuri, "./Wi-Fi/", 8) != 0) {
		wpa_printf(MSG_INFO, "Do not allow Add outside ./Wi-Fi");
		return DM_RESP_PERMISSION_DENIED;
	}
	pos = locuri + 8;

	if (ctx->fqdn == NULL)
		return DM_RESP_COMMAND_FAILED;
	fqdn_len = os_strlen(ctx->fqdn);
	if (os_strncasecmp(pos, ctx->fqdn, fqdn_len) != 0 ||
	    pos[fqdn_len] != '/') {
		wpa_printf(MSG_INFO, "Do not allow Add outside ./Wi-Fi/%s",
			   ctx->fqdn);
		return DM_RESP_PERMISSION_DENIED;
	}
	pos += fqdn_len + 1;

	if (os_strncasecmp(pos, "PerProviderSubscription/", 24) != 0) {
		wpa_printf(MSG_INFO,
			   "Do not allow Add outside ./Wi-Fi/%s/PerProviderSubscription",
			   ctx->fqdn);
		return DM_RESP_PERMISSION_DENIED;
	}
	pos += 24;

	wpa_printf(MSG_INFO, "Add command for PPS node %s", pos);

	pps_node = get_node(ctx->xml, pps, pos);
	if (pps_node) {
		wpa_printf(MSG_INFO, "Specified PPS node exists already");
		return DM_RESP_ALREADY_EXISTS;
	}

	uri = os_strdup(pos);
	if (uri == NULL)
		return DM_RESP_COMMAND_FAILED;
	while (!pps_node) {
		upos = os_strrchr(uri, '/');
		if (!upos)
			break;
		upos[0] = '\0';
		pps_node = get_node(ctx->xml, pps, uri);
		wpa_printf(MSG_INFO, "Node %s %s", uri,
			   pps_node ? "exists" : "does not exist");
	}

	wpa_printf(MSG_INFO, "Parent URI: %s", uri);

	if (!pps_node) {
		/* Add at root of PPS MO */
		pps_node = pps;
	}

	uri_len = os_strlen(uri);
	os_strlcpy(uri, pos + uri_len, os_strlen(pos));
	upos = uri;
	while (*upos == '/')
		upos++;
	wpa_printf(MSG_INFO, "Nodes to add: %s", upos);

	for (;;) {
		end = os_strchr(upos, '/');
		if (!end)
			break;
		*end = '\0';
		wpa_printf(MSG_INFO, "Adding interim node %s", upos);
		pps_node = xml_node_create(ctx->xml, pps_node, NULL, upos);
		if (pps_node == NULL) {
			os_free(uri);
			return DM_RESP_COMMAND_FAILED;
		}
		upos = end + 1;
	}

	wpa_printf(MSG_INFO, "Adding node %s", upos);

	node = get_node(ctx->xml, add, "Item/Meta/Type");
	if (node) {
		char *type;
		type = xml_node_get_text(ctx->xml, node);
		if (type == NULL) {
			wpa_printf(MSG_ERROR, "Could not find type text");
			os_free(uri);
			return DM_RESP_BAD_REQUEST;
		}
		use_tnds = node &&
			os_strstr(type, "application/vnd.syncml.dmtnds+xml");
	}

	node = get_node(ctx->xml, add, "Item/Data");
	if (node == NULL) {
		wpa_printf(MSG_INFO, "No Add/Item/Data found");
		os_free(uri);
		return DM_RESP_BAD_REQUEST;
	}

	data = xml_node_get_text(ctx->xml, node);
	if (data == NULL) {
		wpa_printf(MSG_INFO, "Could not get Add/Item/Data text");
		os_free(uri);
		return DM_RESP_BAD_REQUEST;
	}

	wpa_printf(MSG_DEBUG, "Add/Item/Data: %s", data);

	if (use_tnds) {
		tnds = xml_node_from_buf(ctx->xml, data);
		xml_node_get_text_free(ctx->xml, data);
		if (tnds == NULL) {
			wpa_printf(MSG_INFO,
				   "Could not parse Add/Item/Data text");
			os_free(uri);
			return DM_RESP_BAD_REQUEST;
		}

		unode = tnds_to_mo(ctx->xml, tnds);
		xml_node_free(ctx->xml, tnds);
		if (unode == NULL) {
			wpa_printf(MSG_INFO, "Could not parse TNDS text");
			os_free(uri);
			return DM_RESP_BAD_REQUEST;
		}

		debug_dump_node(ctx, "Parsed TNDS", unode);

		xml_node_add_child(ctx->xml, pps_node, unode);
	} else {
		/* TODO: What to do here? */
		os_free(uri);
		return DM_RESP_BAD_REQUEST;
	}

	os_free(uri);

	if (update_pps_file(ctx, pps_fname, pps) < 0)
		return DM_RESP_COMMAND_FAILED;

	ctx->pps_updated = 1;

	return DM_RESP_OK;
}