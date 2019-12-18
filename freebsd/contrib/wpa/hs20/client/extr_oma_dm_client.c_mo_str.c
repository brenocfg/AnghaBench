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
 int /*<<< orphan*/ * mo_to_tnds (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/ * node_from_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* xml_node_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char * mo_str(struct hs20_osu_client *ctx, const char *urn,
		     const char *fname)
{
	xml_node_t *fnode, *tnds;
	char *str;

	fnode = node_from_file(ctx->xml, fname);
	if (!fnode)
		return NULL;
	tnds = mo_to_tnds(ctx->xml, fnode, 0, urn, "syncml:dmddf1.2");
	xml_node_free(ctx->xml, fnode);
	if (!tnds)
		return NULL;

	str = xml_node_to_str(ctx->xml, tnds);
	xml_node_free(ctx->xml, tnds);
	if (str == NULL)
		return NULL;
	wpa_printf(MSG_INFO, "MgmtTree: %s", str);

	return str;
}