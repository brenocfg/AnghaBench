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
struct hs20_osu_client {int dummy; } ;

/* Variables and functions */
 int DM_RESP_BAD_REQUEST ; 
 int DM_RESP_NOT_FOUND ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int oma_dm_exec_browser (struct hs20_osu_client*,int /*<<< orphan*/ *) ; 
 int oma_dm_exec_get_cert (struct hs20_osu_client*,int /*<<< orphan*/ *) ; 
 char* oma_dm_get_target_locuri (struct hs20_osu_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int oma_dm_exec(struct hs20_osu_client *ctx, xml_node_t *exec)
{
	char *locuri;
	int ret;

	locuri = oma_dm_get_target_locuri(ctx, exec);
	if (locuri == NULL) {
		wpa_printf(MSG_INFO, "No Target LocURI node found");
		return DM_RESP_BAD_REQUEST;
	}

	wpa_printf(MSG_INFO, "Target LocURI: %s", locuri);

	if (os_strcasecmp(locuri, "./DevDetail/Ext/org.wi-fi/Wi-Fi/Ops/"
			  "launchBrowserToURI") == 0) {
		ret = oma_dm_exec_browser(ctx, exec);
	} else if (os_strcasecmp(locuri, "./DevDetail/Ext/org.wi-fi/Wi-Fi/Ops/"
			  "getCertificate") == 0) {
		ret = oma_dm_exec_get_cert(ctx, exec);
	} else {
		wpa_printf(MSG_INFO, "Unsupported exec Target LocURI");
		ret = DM_RESP_NOT_FOUND;
	}
	os_free(locuri);

	return ret;
}