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
struct xml_node_ctx {int dummy; } ;
struct hs20_osu_client {struct xml_node_ctx* xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  spp_xsd_fname ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*,...) ; 
 char* xml_node_get_localname (struct xml_node_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_is_element (struct xml_node_ctx*,int /*<<< orphan*/ *) ; 
 int xml_validate (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int hs20_spp_validate(struct hs20_osu_client *ctx, xml_node_t *node,
			     const char *expected_name)
{
	struct xml_node_ctx *xctx = ctx->xml;
	const char *name;
	char *err;
	int ret;

	if (!xml_node_is_element(xctx, node))
		return -1;

	name = xml_node_get_localname(xctx, node);
	if (name == NULL)
		return -1;

	if (strcmp(expected_name, name) != 0) {
		wpa_printf(MSG_INFO, "Unexpected SOAP method name '%s' (expected '%s')",
			   name, expected_name);
		write_summary(ctx, "Unexpected SOAP method name '%s' (expected '%s')",
			      name, expected_name);
		return -1;
	}

	ret = xml_validate(xctx, node, spp_xsd_fname, &err);
	if (ret < 0) {
		wpa_printf(MSG_INFO, "XML schema validation error(s)\n%s", err);
		write_summary(ctx, "SPP XML schema validation failed");
		os_free(err);
	}
	return ret;
}