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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * get_child_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_base64_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

void get_user_pw(struct hs20_osu_client *ctx, xml_node_t *pps,
		 const char *alt_loc, char **user, char **pw)
{
	xml_node_t *node;

	node = get_child_node(ctx->xml, pps,
			      "Credential/UsernamePassword/Username");
	if (node)
		*user = xml_node_get_text(ctx->xml, node);

	node = get_child_node(ctx->xml, pps,
			      "Credential/UsernamePassword/Password");
	if (node)
		*pw = xml_node_get_base64_text(ctx->xml, node, NULL);

	node = get_child_node(ctx->xml, pps, alt_loc);
	if (node) {
		xml_node_t *a;
		a = get_node(ctx->xml, node, "Username");
		if (a) {
			xml_node_get_text_free(ctx->xml, *user);
			*user = xml_node_get_text(ctx->xml, a);
			wpa_printf(MSG_INFO, "Use OSU username '%s'", *user);
		}

		a = get_node(ctx->xml, node, "Password");
		if (a) {
			free(*pw);
			*pw = xml_node_get_base64_text(ctx->xml, a, NULL);
			wpa_printf(MSG_INFO, "Use OSU password");
		}
	}
}