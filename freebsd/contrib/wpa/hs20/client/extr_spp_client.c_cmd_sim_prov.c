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
struct hs20_osu_client {scalar_t__ pps_cred_set; int /*<<< orphan*/  ca_fname; int /*<<< orphan*/  http; int /*<<< orphan*/  ifname; int /*<<< orphan*/  server_url; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SPP_SUBSCRIPTION_REGISTRATION ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strdup (char const*) ; 
 scalar_t__ soap_init_client (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spp_post_dev_data (struct hs20_osu_client*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_ip_addr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int cmd_sim_prov(struct hs20_osu_client *ctx, const char *url)
{
	if (url == NULL) {
		wpa_printf(MSG_INFO, "Invalid prov command (missing URL)");
		return -1;
	}

	wpa_printf(MSG_INFO, "SIM provisioning requested");

	os_free(ctx->server_url);
	ctx->server_url = os_strdup(url);

	wpa_printf(MSG_INFO, "Wait for IP address before starting SIM provisioning");

	if (wait_ip_addr(ctx->ifname, 15) < 0) {
		wpa_printf(MSG_INFO, "Could not get IP address for WLAN - try connection anyway");
	}

	if (soap_init_client(ctx->http, url, ctx->ca_fname, NULL, NULL, NULL,
			     NULL) < 0)
		return -1;
	spp_post_dev_data(ctx, SPP_SUBSCRIPTION_REGISTRATION,
			  "Subscription provisioning", NULL, NULL);

	return ctx->pps_cred_set ? 0 : -1;
}