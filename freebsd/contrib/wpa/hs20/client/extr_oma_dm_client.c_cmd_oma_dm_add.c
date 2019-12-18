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
struct hs20_osu_client {int /*<<< orphan*/  xml; int /*<<< orphan*/  fqdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * node_from_file (int /*<<< orphan*/ ,char const*) ; 
 int oma_dm_add (struct hs20_osu_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  os_strdup (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cmd_oma_dm_add(struct hs20_osu_client *ctx, const char *pps_fname,
		    const char *add_fname)
{
	xml_node_t *pps, *add;
	int res;

	ctx->fqdn = os_strdup("wi-fi.org");

	pps = node_from_file(ctx->xml, pps_fname);
	if (pps == NULL) {
		wpa_printf(MSG_INFO, "PPS file %s could not be parsed",
			   pps_fname);
		return;
	}

	add = node_from_file(ctx->xml, add_fname);
	if (add == NULL) {
		wpa_printf(MSG_INFO, "Add file %s could not be parsed",
			   add_fname);
		xml_node_free(ctx->xml, pps);
		return;
	}

	res = oma_dm_add(ctx, add, pps, pps_fname);
	wpa_printf(MSG_INFO, "oma_dm_add --> %d", res);

	xml_node_free(ctx->xml, pps);
	xml_node_free(ctx->xml, add);
}