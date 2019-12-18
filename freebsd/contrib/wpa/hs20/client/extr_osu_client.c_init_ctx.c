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
struct hs20_osu_client {char* ifname; int /*<<< orphan*/ * http; int /*<<< orphan*/ * xml; int /*<<< orphan*/  devid; } ;

/* Variables and functions */
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * http_init_ctx (struct hs20_osu_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_ocsp_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  http_set_cert_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hs20_osu_client*) ; 
 int /*<<< orphan*/ * node_from_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  os_memset (struct hs20_osu_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strdup (char*) ; 
 int /*<<< orphan*/  osu_cert_cb ; 
 int /*<<< orphan*/  xml_node_deinit_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* xml_node_get_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * xml_node_init_ctx (struct hs20_osu_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_ctx(struct hs20_osu_client *ctx)
{
	xml_node_t *devinfo, *devid;

	os_memset(ctx, 0, sizeof(*ctx));
	ctx->ifname = "wlan0";
	ctx->xml = xml_node_init_ctx(ctx, NULL);
	if (ctx->xml == NULL)
		return -1;

	devinfo = node_from_file(ctx->xml, "devinfo.xml");
	if (devinfo) {
		devid = get_node(ctx->xml, devinfo, "DevId");
		if (devid) {
			char *tmp = xml_node_get_text(ctx->xml, devid);

			if (tmp) {
				ctx->devid = os_strdup(tmp);
				xml_node_get_text_free(ctx->xml, tmp);
			}
		}
		xml_node_free(ctx->xml, devinfo);
	}

	ctx->http = http_init_ctx(ctx, ctx->xml);
	if (ctx->http == NULL) {
		xml_node_deinit_ctx(ctx->xml);
		return -1;
	}
	http_ocsp_set(ctx->http, 2);
	http_set_cert_cb(ctx->http, osu_cert_cb, ctx);

	return 0;
}