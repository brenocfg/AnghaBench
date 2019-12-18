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
typedef  int /*<<< orphan*/  dir ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 scalar_t__ os_file_exists (char*) ; 
 int os_snprintf (char*,int,char*,char*,char const*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 scalar_t__ set_cred_quoted (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void set_pps_cred_realm(struct hs20_osu_client *ctx, int id,
			       xml_node_t *node, const char *fqdn, int sim)
{
	char *str = xml_node_get_text(ctx->xml, node);
	char buf[200], dir[200];
	int res;

	if (str == NULL)
		return;

	wpa_printf(MSG_INFO, "- Credential/Realm = %s", str);
	if (set_cred_quoted(ctx->ifname, id, "realm", str) < 0)
		wpa_printf(MSG_INFO, "Failed to set cred realm");
	xml_node_get_text_free(ctx->xml, str);

	if (sim)
		return;

	if (getcwd(dir, sizeof(dir)) == NULL)
		return;
	res = os_snprintf(buf, sizeof(buf), "%s/SP/%s/aaa-ca.pem", dir, fqdn);
	if (os_snprintf_error(sizeof(buf), res))
		return;
	if (os_file_exists(buf)) {
		if (set_cred_quoted(ctx->ifname, id, "ca_cert", buf) < 0) {
			wpa_printf(MSG_INFO, "Failed to set CA cert");
		}
	}
}