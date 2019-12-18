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
struct hs20_osu_client {int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  debug_dump_node (struct hs20_osu_client*,char*,int /*<<< orphan*/ *) ; 
 char* get_spp_attr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*,char*) ; 
 int /*<<< orphan*/  xml_node_get_attr_value_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int process_spp_exchange_complete(struct hs20_osu_client *ctx,
					 xml_node_t *node)
{
	char *status, *session_id;

	debug_dump_node(ctx, "sppExchangeComplete", node);

	status = get_spp_attr_value(ctx->xml, node, "sppStatus");
	if (status == NULL) {
		wpa_printf(MSG_INFO, "No sppStatus attribute");
		return -1;
	}
	write_summary(ctx, "Received sppExchangeComplete sppStatus='%s'",
		      status);

	session_id = get_spp_attr_value(ctx->xml, node, "sessionID");
	if (session_id == NULL) {
		wpa_printf(MSG_INFO, "No sessionID attribute");
		xml_node_get_attr_value_free(ctx->xml, status);
		return -1;
	}

	wpa_printf(MSG_INFO, "[hs20] sppStatus: '%s'  sessionID: '%s'",
		   status, session_id);
	xml_node_get_attr_value_free(ctx->xml, session_id);

	if (strcasecmp(status, "Exchange complete, release TLS connection") ==
	    0) {
		xml_node_get_attr_value_free(ctx->xml, status);
		return 0;
	}

	wpa_printf(MSG_INFO, "Unexpected sppStatus '%s'", status);
	write_summary(ctx, "Unexpected sppStatus '%s'", status);
	xml_node_get_attr_value_free(ctx->xml, status);
	return -1;
}