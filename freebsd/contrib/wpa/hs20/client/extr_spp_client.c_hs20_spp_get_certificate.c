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
typedef  int /*<<< orphan*/  xml_namespace_t ;
struct hs20_osu_client {int /*<<< orphan*/  xml; int /*<<< orphan*/  http; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * build_spp_post_dev_data (struct hs20_osu_client*,int /*<<< orphan*/ **,char const*,char*) ; 
 int /*<<< orphan*/  debug_dump_node (struct hs20_osu_client*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ hs20_spp_validate (struct hs20_osu_client*,int /*<<< orphan*/ *,char*) ; 
 int osu_get_certificate (struct hs20_osu_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * soap_send_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static xml_node_t * hs20_spp_get_certificate(struct hs20_osu_client *ctx,
					     xml_node_t *cmd,
					     const char *session_id,
					     const char *pps_fname)
{
	xml_namespace_t *ns;
	xml_node_t *node, *ret_node;
	int res;

	wpa_printf(MSG_INFO, "Client certificate enrollment");

	res = osu_get_certificate(ctx, cmd);
	if (res < 0)
		wpa_printf(MSG_INFO, "EST simpleEnroll failed");

	node = build_spp_post_dev_data(ctx, &ns, session_id,
				       res == 0 ?
				       "Certificate enrollment completed" :
				       "Certificate enrollment failed");
	if (node == NULL)
		return NULL;

	ret_node = soap_send_receive(ctx->http, node);
	if (ret_node == NULL)
		return NULL;

	debug_dump_node(ctx, "Received response to certificate enrollment "
			"completed", ret_node);

	if (hs20_spp_validate(ctx, ret_node, "sppPostDevDataResponse") < 0) {
		wpa_printf(MSG_INFO, "SPP validation failed");
		xml_node_free(ctx->xml, ret_node);
		return NULL;
	}

	return ret_node;
}