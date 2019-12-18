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
struct hs20_osu_client {int /*<<< orphan*/  xml; int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ os_strcasecmp (char*,char*) ; 
 scalar_t__ set_cred (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void set_pps_cred_policy_min_backhaul(struct hs20_osu_client *ctx, int id,
					     xml_node_t *min_backhaul)
{
	xml_node_t *node;
	char *type, *dl = NULL, *ul = NULL;
	int home;

	node = get_node(ctx->xml, min_backhaul, "NetworkType");
	if (node == NULL) {
		wpa_printf(MSG_INFO, "Ignore MinBackhaulThreshold without mandatory NetworkType node");
		return;
	}

	type = xml_node_get_text(ctx->xml, node);
	if (type == NULL)
		return;
	wpa_printf(MSG_INFO, "- Policy/MinBackhaulThreshold/<X+>/NetworkType = %s",
		   type);
	if (os_strcasecmp(type, "home") == 0)
		home = 1;
	else if (os_strcasecmp(type, "roaming") == 0)
		home = 0;
	else {
		wpa_printf(MSG_INFO, "Ignore MinBackhaulThreshold with invalid NetworkType");
		xml_node_get_text_free(ctx->xml, type);
		return;
	}
	xml_node_get_text_free(ctx->xml, type);

	node = get_node(ctx->xml, min_backhaul, "DLBandwidth");
	if (node)
		dl = xml_node_get_text(ctx->xml, node);

	node = get_node(ctx->xml, min_backhaul, "ULBandwidth");
	if (node)
		ul = xml_node_get_text(ctx->xml, node);

	if (dl == NULL && ul == NULL) {
		wpa_printf(MSG_INFO, "Ignore MinBackhaulThreshold without either DLBandwidth or ULBandwidth nodes");
		return;
	}

	if (dl)
		wpa_printf(MSG_INFO, "- Policy/MinBackhaulThreshold/<X+>/DLBandwidth = %s",
			   dl);
	if (ul)
		wpa_printf(MSG_INFO, "- Policy/MinBackhaulThreshold/<X+>/ULBandwidth = %s",
			   ul);

	if (home) {
		if (dl &&
		    set_cred(ctx->ifname, id, "min_dl_bandwidth_home", dl) < 0)
			wpa_printf(MSG_INFO, "Failed to set cred bandwidth limit");
		if (ul &&
		    set_cred(ctx->ifname, id, "min_ul_bandwidth_home", ul) < 0)
			wpa_printf(MSG_INFO, "Failed to set cred bandwidth limit");
	} else {
		if (dl &&
		    set_cred(ctx->ifname, id, "min_dl_bandwidth_roaming", dl) <
		    0)
			wpa_printf(MSG_INFO, "Failed to set cred bandwidth limit");
		if (ul &&
		    set_cred(ctx->ifname, id, "min_ul_bandwidth_roaming", ul) <
		    0)
			wpa_printf(MSG_INFO, "Failed to set cred bandwidth limit");
	}

	xml_node_get_text_free(ctx->xml, dl);
	xml_node_get_text_free(ctx->xml, ul);
}