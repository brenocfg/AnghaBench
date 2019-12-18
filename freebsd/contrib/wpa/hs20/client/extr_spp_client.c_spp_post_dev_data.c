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
struct hs20_osu_client {int /*<<< orphan*/  xml; int /*<<< orphan*/  http; } ;
typedef  enum spp_post_dev_data_use { ____Placeholder_spp_post_dev_data_use } spp_post_dev_data_use ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * build_spp_post_dev_data (struct hs20_osu_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ hs20_spp_validate (struct hs20_osu_client*,int /*<<< orphan*/ *,char*) ; 
 char* http_get_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_spp_post_dev_data_response (struct hs20_osu_client*,int,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * soap_send_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  write_result (struct hs20_osu_client*,char*,char const*) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spp_post_dev_data(struct hs20_osu_client *ctx,
			     enum spp_post_dev_data_use use,
			     const char *reason,
			     const char *pps_fname, xml_node_t *pps)
{
	xml_node_t *payload;
	xml_node_t *ret_node;

	payload = build_spp_post_dev_data(ctx, NULL, NULL, reason);
	if (payload == NULL)
		return -1;

	ret_node = soap_send_receive(ctx->http, payload);
	if (!ret_node) {
		const char *err = http_get_err(ctx->http);
		if (err) {
			wpa_printf(MSG_INFO, "HTTP error: %s", err);
			write_result(ctx, "HTTP error: %s", err);
		} else {
			write_summary(ctx, "Failed to send SOAP message");
		}
		return -1;
	}

	if (hs20_spp_validate(ctx, ret_node, "sppPostDevDataResponse") < 0) {
		wpa_printf(MSG_INFO, "SPP validation failed");
		xml_node_free(ctx->xml, ret_node);
		return -1;
	}

	process_spp_post_dev_data_response(ctx, use, ret_node,
					   pps_fname, pps);
	return 0;
}