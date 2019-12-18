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
struct hs20_osu_client {int no_reconnect; int pps_cred_set; int /*<<< orphan*/  ifname; int /*<<< orphan*/  pps_fname; int /*<<< orphan*/  xml; } ;
typedef  int /*<<< orphan*/  fname ;

/* Variables and functions */
 int DM_RESP_ALREADY_EXISTS ; 
 int DM_RESP_BAD_REQUEST ; 
 int DM_RESP_COMMAND_FAILED ; 
 int DM_RESP_OK ; 
 int DM_RESP_PERMISSION_DENIED ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  cmd_set_pps (struct hs20_osu_client*,char*) ; 
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int hs20_add_pps_mo (struct hs20_osu_client*,char*,int /*<<< orphan*/ *,char*,int) ; 
 int oma_dm_run_add (struct hs20_osu_client*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ os_file_exists (char const*) ; 
 int /*<<< orphan*/  os_snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  os_strlcpy (char*,char const*,int) ; 
 scalar_t__ os_strncasecmp (char*,char*,int) ; 
 scalar_t__ wpa_command (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int oma_dm_add(struct hs20_osu_client *ctx, xml_node_t *add,
		      xml_node_t *pps, const char *pps_fname)
{
	xml_node_t *node;
	char *locuri;
	char fname[300];
	int ret;

	node = get_node(ctx->xml, add, "Item/Target/LocURI");
	if (node == NULL) {
		wpa_printf(MSG_INFO, "No Target LocURI node found");
		return DM_RESP_BAD_REQUEST;
	}
	locuri = xml_node_get_text(ctx->xml, node);
	if (locuri == NULL) {
		wpa_printf(MSG_ERROR, "No LocURI node text found");
		return DM_RESP_BAD_REQUEST;
	}
	wpa_printf(MSG_INFO, "Target LocURI: %s", locuri);
	if (os_strncasecmp(locuri, "./Wi-Fi/", 8) != 0) {
		wpa_printf(MSG_INFO, "Unsupported Add Target LocURI");
		xml_node_get_text_free(ctx->xml, locuri);
		return DM_RESP_PERMISSION_DENIED;
	}

	node = get_node(ctx->xml, add, "Item/Data");
	if (node == NULL) {
		wpa_printf(MSG_INFO, "No Data node found");
		xml_node_get_text_free(ctx->xml, locuri);
		return DM_RESP_BAD_REQUEST;
	}

	if (pps_fname && os_file_exists(pps_fname)) {
		ret = oma_dm_run_add(ctx, locuri, add, pps, pps_fname);
		if (ret != DM_RESP_OK) {
			xml_node_get_text_free(ctx->xml, locuri);
			return ret;
		}
		ret = 0;
		os_strlcpy(fname, pps_fname, sizeof(fname));
	} else
		ret = hs20_add_pps_mo(ctx, locuri, node, fname, sizeof(fname));
	xml_node_get_text_free(ctx->xml, locuri);
	if (ret < 0)
		return ret == -2 ? DM_RESP_ALREADY_EXISTS :
			DM_RESP_COMMAND_FAILED;

	if (ctx->no_reconnect == 2) {
		os_snprintf(ctx->pps_fname, sizeof(ctx->pps_fname), "%s",
			    fname);
		ctx->pps_cred_set = 1;
		return DM_RESP_OK;
	}

	wpa_printf(MSG_INFO, "Updating wpa_supplicant credentials");
	cmd_set_pps(ctx, fname);

	if (ctx->no_reconnect)
		return DM_RESP_OK;

	wpa_printf(MSG_INFO, "Requesting reconnection with updated configuration");
	if (wpa_command(ctx->ifname, "INTERWORKING_SELECT auto") < 0)
		wpa_printf(MSG_INFO, "Failed to request wpa_supplicant to reconnect");

	return DM_RESP_OK;
}