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
struct hs20_osu_client {char* ca_fname; scalar_t__ pps_cred_set; int /*<<< orphan*/  http; int /*<<< orphan*/  server_url; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SPP_SUBSCRIPTION_REGISTRATION ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strdup (char const*) ; 
 scalar_t__ soap_init_client (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spp_post_dev_data (struct hs20_osu_client*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int cmd_prov(struct hs20_osu_client *ctx, const char *url)
{
	unlink("Cert/est_cert.der");
	unlink("Cert/est_cert.pem");

	if (url == NULL) {
		wpa_printf(MSG_INFO, "Invalid prov command (missing URL)");
		return -1;
	}

	wpa_printf(MSG_INFO,
		   "Credential provisioning requested - URL: %s ca_fname: %s",
		   url, ctx->ca_fname ? ctx->ca_fname : "N/A");

	os_free(ctx->server_url);
	ctx->server_url = os_strdup(url);

	if (soap_init_client(ctx->http, url, ctx->ca_fname, NULL, NULL, NULL,
			     NULL) < 0)
		return -1;
	spp_post_dev_data(ctx, SPP_SUBSCRIPTION_REGISTRATION,
			  "Subscription registration", NULL, NULL);

	return ctx->pps_cred_set ? 0 : -1;
}