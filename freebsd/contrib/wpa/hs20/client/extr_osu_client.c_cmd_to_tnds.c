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
 int /*<<< orphan*/ * mo_to_tnds (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * node_from_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  node_to_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cmd_to_tnds(struct hs20_osu_client *ctx, const char *in_fname,
			const char *out_fname, const char *urn, int use_path)
{
	xml_node_t *mo, *node;

	mo = node_from_file(ctx->xml, in_fname);
	if (mo == NULL) {
		wpa_printf(MSG_INFO, "Could not read or parse '%s'", in_fname);
		return;
	}

	node = mo_to_tnds(ctx->xml, mo, use_path, urn, NULL);
	if (node) {
		node_to_file(ctx->xml, out_fname, node);
		xml_node_free(ctx->xml, node);
	}

	xml_node_free(ctx->xml, mo);
}