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
struct hs20_osu_client {int /*<<< orphan*/  xml; int /*<<< orphan*/  client_cert_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int S_IRWXG ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  android_update_permission (char*,int) ; 
 scalar_t__ est_build_csr (struct hs20_osu_client*,char*) ; 
 scalar_t__ est_load_cacerts (struct hs20_osu_client*,char*) ; 
 scalar_t__ est_simple_enroll (struct hs20_osu_client*,char*,char*,char*) ; 
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 scalar_t__ os_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*,char*) ; 
 char* xml_node_get_attr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xml_node_get_attr_value_free (int /*<<< orphan*/ ,char*) ; 
 char* xml_node_get_base64_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

int osu_get_certificate(struct hs20_osu_client *ctx, xml_node_t *getcert)
{
	xml_node_t *node;
	char *url, *user = NULL, *pw = NULL;
	char *proto;
	int ret = -1;

	proto = xml_node_get_attr_value(ctx->xml, getcert,
					"enrollmentProtocol");
	if (!proto)
		return -1;
	wpa_printf(MSG_INFO, "getCertificate - enrollmentProtocol=%s", proto);
	write_summary(ctx, "getCertificate - enrollmentProtocol=%s", proto);
	if (os_strcasecmp(proto, "EST") != 0) {
		wpa_printf(MSG_INFO, "Unsupported enrollmentProtocol");
		xml_node_get_attr_value_free(ctx->xml, proto);
		return -1;
	}
	xml_node_get_attr_value_free(ctx->xml, proto);

	node = get_node(ctx->xml, getcert, "enrollmentServerURI");
	if (node == NULL) {
		wpa_printf(MSG_INFO, "Could not find enrollmentServerURI node");
		xml_node_get_attr_value_free(ctx->xml, proto);
		return -1;
	}
	url = xml_node_get_text(ctx->xml, node);
	if (url == NULL) {
		wpa_printf(MSG_INFO, "Could not get URL text");
		return -1;
	}
	wpa_printf(MSG_INFO, "enrollmentServerURI: %s", url);
	write_summary(ctx, "enrollmentServerURI: %s", url);

	node = get_node(ctx->xml, getcert, "estUserID");
	if (node == NULL && !ctx->client_cert_present) {
		wpa_printf(MSG_INFO, "Could not find estUserID node");
		goto fail;
	}
	if (node) {
		user = xml_node_get_text(ctx->xml, node);
		if (user == NULL) {
			wpa_printf(MSG_INFO, "Could not get estUserID text");
			goto fail;
		}
		wpa_printf(MSG_INFO, "estUserID: %s", user);
		write_summary(ctx, "estUserID: %s", user);
	}

	node = get_node(ctx->xml, getcert, "estPassword");
	if (node == NULL && !ctx->client_cert_present) {
		wpa_printf(MSG_INFO, "Could not find estPassword node");
		goto fail;
	}
	if (node) {
		pw = xml_node_get_base64_text(ctx->xml, node, NULL);
		if (pw == NULL) {
			wpa_printf(MSG_INFO, "Could not get estPassword text");
			goto fail;
		}
		wpa_printf(MSG_INFO, "estPassword: %s", pw);
	}

	mkdir("Cert", S_IRWXU);
	android_update_permission("Cert", S_IRWXU | S_IRWXG);

	if (est_load_cacerts(ctx, url) < 0 ||
	    est_build_csr(ctx, url) < 0 ||
	    est_simple_enroll(ctx, url, user, pw) < 0)
		goto fail;

	ret = 0;
fail:
	xml_node_get_text_free(ctx->xml, url);
	xml_node_get_text_free(ctx->xml, user);
	xml_node_get_text_free(ctx->xml, pw);

	return ret;
}