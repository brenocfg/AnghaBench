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

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * build_spp_post_dev_data (struct hs20_osu_client*,int /*<<< orphan*/ *,char const*,char*) ; 
 scalar_t__ hs20_spp_validate (struct hs20_osu_client*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ soap_reinit_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * soap_send_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static xml_node_t * hs20_spp_user_input_completed(struct hs20_osu_client *ctx,
						    const char *session_id)
{
	xml_node_t *node, *ret_node;

	node = build_spp_post_dev_data(ctx, NULL, session_id,
				       "User input completed");
	if (node == NULL)
		return NULL;

	ret_node = soap_send_receive(ctx->http, node);
	if (!ret_node) {
		if (soap_reinit_client(ctx->http) < 0)
			return NULL;
		wpa_printf(MSG_INFO, "Try to finish with re-opened connection");
		node = build_spp_post_dev_data(ctx, NULL, session_id,
					       "User input completed");
		if (node == NULL)
			return NULL;
		ret_node = soap_send_receive(ctx->http, node);
		if (ret_node == NULL)
			return NULL;
		wpa_printf(MSG_INFO, "Continue with new connection");
	}

	if (hs20_spp_validate(ctx, ret_node, "sppPostDevDataResponse") < 0) {
		wpa_printf(MSG_INFO, "SPP validation failed");
		xml_node_free(ctx->xml, ret_node);
		return NULL;
	}

	return ret_node;
}