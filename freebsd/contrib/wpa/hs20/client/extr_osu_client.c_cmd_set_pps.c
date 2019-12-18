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
 int /*<<< orphan*/ * node_from_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strchr (char*,char) ; 
 char* os_strdup (char const*) ; 
 char* os_strstr (char const*,char*) ; 
 int /*<<< orphan*/  set_pps (struct hs20_osu_client*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cmd_set_pps(struct hs20_osu_client *ctx, const char *pps_fname)
{
	xml_node_t *pps;
	const char *fqdn;
	char *fqdn_buf = NULL, *pos;

	pps = node_from_file(ctx->xml, pps_fname);
	if (pps == NULL) {
		wpa_printf(MSG_INFO, "Could not read or parse '%s'", pps_fname);
		return;
	}

	fqdn = os_strstr(pps_fname, "SP/");
	if (fqdn) {
		fqdn_buf = os_strdup(fqdn + 3);
		if (fqdn_buf == NULL)
			return;
		pos = os_strchr(fqdn_buf, '/');
		if (pos)
			*pos = '\0';
		fqdn = fqdn_buf;
	} else
		fqdn = "wi-fi.org";

	wpa_printf(MSG_INFO, "Set PPS MO info to wpa_supplicant - SP FQDN %s",
		   fqdn);
	set_pps(ctx, pps, fqdn);

	os_free(fqdn_buf);
	xml_node_free(ctx->xml, pps);
}