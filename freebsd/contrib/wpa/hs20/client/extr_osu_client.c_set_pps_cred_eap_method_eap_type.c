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
struct hs20_osu_client {int /*<<< orphan*/  ifname; int /*<<< orphan*/  xml; } ;

/* Variables and functions */
#define  EAP_TYPE_PEAP 131 
#define  EAP_TYPE_PWD 130 
#define  EAP_TYPE_TLS 129 
#define  EAP_TYPE_TTLS 128 
 int /*<<< orphan*/  MSG_INFO ; 
 int atoi (char*) ; 
 scalar_t__ set_cred (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void set_pps_cred_eap_method_eap_type(struct hs20_osu_client *ctx,
					     int id, xml_node_t *node)
{
	char *str = xml_node_get_text(ctx->xml, node);
	int type;
	const char *eap_method = NULL;

	if (!str)
		return;
	wpa_printf(MSG_INFO,
		   "- Credential/UsernamePassword/EAPMethod/EAPType = %s", str);
	type = atoi(str);
	switch (type) {
	case EAP_TYPE_TLS:
		eap_method = "TLS";
		break;
	case EAP_TYPE_TTLS:
		eap_method = "TTLS";
		break;
	case EAP_TYPE_PEAP:
		eap_method = "PEAP";
		break;
	case EAP_TYPE_PWD:
		eap_method = "PWD";
		break;
	}
	xml_node_get_text_free(ctx->xml, str);
	if (!eap_method) {
		wpa_printf(MSG_INFO, "Unknown EAPType value");
		return;
	}

	if (set_cred(ctx->ifname, id, "eap", eap_method) < 0)
		wpa_printf(MSG_INFO, "Failed to set cred eap");
}