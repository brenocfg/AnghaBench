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
struct hs20_osu_client {char* fqdn; int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int DM_RESP_BAD_REQUEST ; 
 int DM_RESP_COMMAND_FAILED ; 
 int DM_RESP_NOT_FOUND ; 
 int DM_RESP_OK ; 
 int DM_RESP_PERMISSION_DENIED ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 char* oma_dm_get_target_locuri (struct hs20_osu_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcasecmp (char const*,char*) ; 
 size_t os_strlen (char*) ; 
 scalar_t__ os_strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_localname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oma_dm_get(struct hs20_osu_client *ctx, xml_node_t *get,
		      xml_node_t *pps, const char *pps_fname, char **value)
{
	char *locuri, *pos;
	size_t fqdn_len;
	xml_node_t *pps_node;
	const char *name;

	*value = NULL;

	locuri = oma_dm_get_target_locuri(ctx, get);
	if (locuri == NULL)
		return DM_RESP_BAD_REQUEST;

	wpa_printf(MSG_INFO, "Get command target LocURI: %s", locuri);
	if (os_strncasecmp(locuri, "./Wi-Fi/", 8) != 0) {
		wpa_printf(MSG_INFO, "Do not allow Get outside ./Wi-Fi");
		os_free(locuri);
		return DM_RESP_PERMISSION_DENIED;
	}
	pos = locuri + 8;

	if (ctx->fqdn == NULL)
		return DM_RESP_COMMAND_FAILED;
	fqdn_len = os_strlen(ctx->fqdn);
	if (os_strncasecmp(pos, ctx->fqdn, fqdn_len) != 0 ||
	    pos[fqdn_len] != '/') {
		wpa_printf(MSG_INFO, "Do not allow Get outside ./Wi-Fi/%s",
			   ctx->fqdn);
		os_free(locuri);
		return DM_RESP_PERMISSION_DENIED;
	}
	pos += fqdn_len + 1;

	if (os_strncasecmp(pos, "PerProviderSubscription/", 24) != 0) {
		wpa_printf(MSG_INFO,
			   "Do not allow Get outside ./Wi-Fi/%s/PerProviderSubscription",
			   ctx->fqdn);
		os_free(locuri);
		return DM_RESP_PERMISSION_DENIED;
	}
	pos += 24;

	wpa_printf(MSG_INFO, "Get command for PPS node %s", pos);

	pps_node = get_node(ctx->xml, pps, pos);
	if (pps_node == NULL) {
		wpa_printf(MSG_INFO, "Specified PPS node not found");
		os_free(locuri);
		return DM_RESP_NOT_FOUND;
	}

	name = xml_node_get_localname(ctx->xml, pps_node);
	wpa_printf(MSG_INFO, "Get command returned node with name '%s'", name);
	if (os_strcasecmp(name, "Password") == 0) {
		wpa_printf(MSG_INFO, "Do not allow Get for Password node");
		os_free(locuri);
		return DM_RESP_PERMISSION_DENIED;
	}

	/*
	 * TODO: No support for DMTNDS, so if interior node, reply with a
	 * list of children node names in Results element. The child list type is
	 * defined in [DMTND].
	 */

	*value = xml_node_get_text(ctx->xml, pps_node);
	if (*value == NULL)
		return DM_RESP_COMMAND_FAILED;

	return DM_RESP_OK;
}