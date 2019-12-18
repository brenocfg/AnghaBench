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

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 scalar_t__ set_cred (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_base64_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void set_pps_cred_password(struct hs20_osu_client *ctx, int id,
				  xml_node_t *node)
{
	int len, i;
	char *pw, *hex, *pos, *end;

	pw = xml_node_get_base64_text(ctx->xml, node, &len);
	if (pw == NULL)
		return;

	wpa_printf(MSG_INFO, "- Credential/UsernamePassword/Password = %s", pw);

	hex = malloc(len * 2 + 1);
	if (hex == NULL) {
		free(pw);
		return;
	}
	end = hex + len * 2 + 1;
	pos = hex;
	for (i = 0; i < len; i++) {
		snprintf(pos, end - pos, "%02x", pw[i]);
		pos += 2;
	}
	free(pw);

	if (set_cred(ctx->ifname, id, "password", hex) < 0)
		wpa_printf(MSG_INFO, "Failed to set cred password");
	free(hex);
}