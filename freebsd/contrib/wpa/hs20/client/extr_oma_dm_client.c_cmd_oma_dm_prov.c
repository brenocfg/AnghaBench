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
struct hs20_osu_client {scalar_t__ pps_cred_set; int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * build_oma_dm_1_sub_reg (struct hs20_osu_client*,char const*,int) ; 
 int /*<<< orphan*/ * oma_dm_process (struct hs20_osu_client*,char const*,int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * oma_dm_send_recv (struct hs20_osu_client*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cmd_oma_dm_prov(struct hs20_osu_client *ctx, const char *url)
{
	xml_node_t *syncml, *resp;
	char *resp_uri = NULL;
	int msgid = 0;

	if (url == NULL) {
		wpa_printf(MSG_INFO, "Invalid prov command (missing URL)");
		return -1;
	}

	wpa_printf(MSG_INFO, "OMA-DM credential provisioning requested");
	write_summary(ctx, "OMA-DM credential provisioning");

	msgid++;
	syncml = build_oma_dm_1_sub_reg(ctx, url, msgid);
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

	return ctx->pps_cred_set ? 0 : -1;
}