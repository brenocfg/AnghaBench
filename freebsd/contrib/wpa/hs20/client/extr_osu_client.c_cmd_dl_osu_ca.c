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
 int download_cert (struct hs20_osu_client*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * get_child_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * node_from_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmd_dl_osu_ca(struct hs20_osu_client *ctx, const char *pps_fname,
			 const char *ca_fname)
{
	xml_node_t *pps, *node;
	int ret;

	pps = node_from_file(ctx->xml, pps_fname);
	if (pps == NULL) {
		wpa_printf(MSG_INFO, "Could not read or parse '%s'", pps_fname);
		return -1;
	}

	node = get_child_node(ctx->xml, pps,
			      "SubscriptionUpdate/TrustRoot");
	if (node == NULL) {
		wpa_printf(MSG_INFO, "No SubscriptionUpdate/TrustRoot/CertURL found from PPS");
		xml_node_free(ctx->xml, pps);
		return -1;
	}

	ret = download_cert(ctx, node, ca_fname);
	xml_node_free(ctx->xml, pps);

	return ret;
}