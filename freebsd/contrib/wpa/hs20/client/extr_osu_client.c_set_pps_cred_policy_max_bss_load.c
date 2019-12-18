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
 scalar_t__ set_cred (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void set_pps_cred_policy_max_bss_load(struct hs20_osu_client *ctx, int id,
					     xml_node_t *node)
{
	char *str = xml_node_get_text(ctx->xml, node);
	if (str == NULL)
		return;
	wpa_printf(MSG_INFO, "- Policy/MaximumBSSLoadValue - %s", str);
	if (set_cred(ctx->ifname, id, "max_bss_load", str) < 0)
		wpa_printf(MSG_INFO, "Failed to set cred max_bss_load limit");
	xml_node_get_text_free(ctx->xml, str);
}