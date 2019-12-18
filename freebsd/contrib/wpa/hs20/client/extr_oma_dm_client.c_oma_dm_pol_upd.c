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
struct hs20_osu_client {int /*<<< orphan*/  ifname; scalar_t__ pps_updated; int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * build_oma_dm_1_pol_upd (struct hs20_osu_client*,char const*,int) ; 
 int /*<<< orphan*/  cmd_set_pps (struct hs20_osu_client*,char const*) ; 
 int /*<<< orphan*/ * oma_dm_process (struct hs20_osu_client*,char const*,int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * oma_dm_send_recv (struct hs20_osu_client*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ wpa_command (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void oma_dm_pol_upd(struct hs20_osu_client *ctx, const char *address,
		    const char *pps_fname,
		    const char *client_cert, const char *client_key,
		    const char *cred_username, const char *cred_password,
		    xml_node_t *pps)
{
	xml_node_t *syncml, *resp;
	char *resp_uri = NULL;
	int msgid = 0;

	wpa_printf(MSG_INFO, "OMA-DM policy update");
	write_summary(ctx, "OMA-DM policy update");

	msgid++;
	syncml = build_oma_dm_1_pol_upd(ctx, address, msgid);
	if (syncml == NULL)
		return;

	while (syncml) {
		resp = oma_dm_send_recv(ctx, resp_uri ? resp_uri : address,
					syncml, NULL, cred_username,
					cred_password, client_cert, client_key);
		if (resp == NULL)
			return;

		msgid++;
		syncml = oma_dm_process(ctx, address, resp, msgid, &resp_uri,
					pps, pps_fname);
		xml_node_free(ctx->xml, resp);
	}

	os_free(resp_uri);

	if (ctx->pps_updated) {
		wpa_printf(MSG_INFO, "Update wpa_supplicant credential based on updated PPS MO");
		write_summary(ctx, "Update wpa_supplicant credential based on updated PPS MO and request connection");
		cmd_set_pps(ctx, pps_fname);
		if (wpa_command(ctx->ifname, "INTERWORKING_SELECT auto") < 0) {
			wpa_printf(MSG_INFO,
				   "Failed to request wpa_supplicant to reconnect");
			write_summary(ctx,
				      "Failed to request wpa_supplicant to reconnect");
		}
	}
}