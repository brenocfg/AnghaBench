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
struct hs20_osu_client {char* server_url; int /*<<< orphan*/  xml; int /*<<< orphan*/  http; int /*<<< orphan*/  ca_fname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  debug_dump_node (struct hs20_osu_client*,char*,int /*<<< orphan*/ *) ; 
 char* http_get_err (int /*<<< orphan*/ ) ; 
 char* http_post (int /*<<< orphan*/ ,char const*,char*,char*,char const*,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strdup (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  write_result (struct hs20_osu_client*,char*,char const*) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xml_node_from_buf (int /*<<< orphan*/ ,char*) ; 
 char* xml_node_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static xml_node_t * oma_dm_send_recv(struct hs20_osu_client *ctx,
				     const char *url, xml_node_t *syncml,
				     const char *ext_hdr,
				     const char *username, const char *password,
				     const char *client_cert,
				     const char *client_key)
{
	xml_node_t *resp;
	char *str, *res;
	char *resp_uri = NULL;

	str = xml_node_to_str(ctx->xml, syncml);
	xml_node_free(ctx->xml, syncml);
	if (str == NULL)
		return NULL;

	wpa_printf(MSG_INFO, "Send OMA DM Package");
	write_summary(ctx, "Send OMA DM Package");
	os_free(ctx->server_url);
	ctx->server_url = os_strdup(url);
	res = http_post(ctx->http, url, str, "application/vnd.syncml.dm+xml",
			ext_hdr, ctx->ca_fname, username, password,
			client_cert, client_key, NULL);
	os_free(str);
	os_free(resp_uri);
	resp_uri = NULL;

	if (res == NULL) {
		const char *err = http_get_err(ctx->http);
		if (err) {
			wpa_printf(MSG_INFO, "HTTP error: %s", err);
			write_result(ctx, "HTTP error: %s", err);
		} else {
			write_summary(ctx, "Failed to send OMA DM Package");
		}
		return NULL;
	}
	wpa_printf(MSG_DEBUG, "Server response: %s", res);

	wpa_printf(MSG_INFO, "Process OMA DM Package");
	write_summary(ctx, "Process received OMA DM Package");
	resp = xml_node_from_buf(ctx->xml, res);
	os_free(res);
	if (resp == NULL) {
		wpa_printf(MSG_INFO, "Failed to parse OMA DM response");
		return NULL;
	}

	debug_dump_node(ctx, "OMA DM Package", resp);

	return resp;
}