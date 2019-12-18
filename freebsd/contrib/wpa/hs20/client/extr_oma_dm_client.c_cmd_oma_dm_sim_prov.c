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
struct hs20_osu_client {int no_reconnect; scalar_t__ pps_cred_set; int /*<<< orphan*/  ifname; int /*<<< orphan*/  pps_fname; int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * build_oma_dm_1_sub_prov (struct hs20_osu_client*,char const*,int) ; 
 int /*<<< orphan*/  cmd_set_pps (struct hs20_osu_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * oma_dm_process (struct hs20_osu_client*,char const*,int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * oma_dm_send_recv (struct hs20_osu_client*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ wait_ip_addr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wpa_command (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cmd_oma_dm_sim_prov(struct hs20_osu_client *ctx, const char *url)
{
	xml_node_t *syncml, *resp;
	char *resp_uri = NULL;
	int msgid = 0;

	if (url == NULL) {
		wpa_printf(MSG_INFO, "Invalid prov command (missing URL)");
		return -1;
	}

	wpa_printf(MSG_INFO, "OMA-DM SIM provisioning requested");
	ctx->no_reconnect = 2;

	wpa_printf(MSG_INFO, "Wait for IP address before starting SIM provisioning");
	write_summary(ctx, "Wait for IP address before starting SIM provisioning");

	if (wait_ip_addr(ctx->ifname, 15) < 0) {
		wpa_printf(MSG_INFO, "Could not get IP address for WLAN - try connection anyway");
	}
	write_summary(ctx, "OMA-DM SIM provisioning");

	msgid++;
	syncml = build_oma_dm_1_sub_prov(ctx, url, msgid);
	if (syncml == NULL)
		return -1;

	while (syncml) {
		resp = oma_dm_send_recv(ctx, resp_uri ? resp_uri : url,
					syncml, NULL, NULL, NULL, NULL, NULL);
		if (resp == NULL)
			return -1;

		msgid++;
		syncml = oma_dm_process(ctx, url, resp, msgid, &resp_uri,
					NULL, NULL);
		xml_node_free(ctx->xml, resp);
	}

	os_free(resp_uri);

	if (ctx->pps_cred_set) {
		wpa_printf(MSG_INFO, "Updating wpa_supplicant credentials");
		cmd_set_pps(ctx, ctx->pps_fname);

		wpa_printf(MSG_INFO, "Requesting reconnection with updated configuration");
		write_summary(ctx, "Requesting reconnection with updated configuration");
		if (wpa_command(ctx->ifname, "INTERWORKING_SELECT auto") < 0) {
			wpa_printf(MSG_INFO, "Failed to request wpa_supplicant to reconnect");
			write_summary(ctx, "Failed to request wpa_supplicant to reconnect");
			return -1;
		}
	}

	return ctx->pps_cred_set ? 0 : -1;
}