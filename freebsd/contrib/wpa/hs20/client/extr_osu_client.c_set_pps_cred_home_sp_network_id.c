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
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void set_pps_cred_home_sp_network_id(struct hs20_osu_client *ctx,
					    int id, xml_node_t *node)
{
	xml_node_t *ssid_node, *hessid_node;
	char *ssid, *hessid;

	ssid_node = get_node(ctx->xml, node, "SSID");
	if (ssid_node == NULL) {
		wpa_printf(MSG_INFO, "Ignore HomeSP/NetworkID without mandatory SSID node");
		return;
	}

	hessid_node = get_node(ctx->xml, node, "HESSID");

	ssid = xml_node_get_text(ctx->xml, ssid_node);
	if (ssid == NULL)
		return;
	hessid = hessid_node ? xml_node_get_text(ctx->xml, hessid_node) : NULL;

	wpa_printf(MSG_INFO, "- HomeSP/NetworkID/<X+>/SSID = %s", ssid);
	if (hessid)
		wpa_printf(MSG_INFO, "- HomeSP/NetworkID/<X+>/HESSID = %s",
			   hessid);

	/* TODO: Configure to wpa_supplicant */

	xml_node_get_text_free(ctx->xml, ssid);
	xml_node_get_text_free(ctx->xml, hessid);
}