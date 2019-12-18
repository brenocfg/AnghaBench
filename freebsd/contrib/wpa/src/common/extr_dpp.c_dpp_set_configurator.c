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
struct dpp_global {int dummy; } ;
struct dpp_authentication {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 scalar_t__ dpp_configuration_parse (struct dpp_authentication*,char const*) ; 
 int /*<<< orphan*/  dpp_configurator_get_id (struct dpp_global*,int /*<<< orphan*/ ) ; 
 char* os_strstr (char const*,char*) ; 
 int /*<<< orphan*/  wpa_msg (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int dpp_set_configurator(struct dpp_global *dpp, void *msg_ctx,
			 struct dpp_authentication *auth,
			 const char *cmd)
{
	const char *pos;

	if (!cmd)
		return 0;

	wpa_printf(MSG_DEBUG, "DPP: Set configurator parameters: %s", cmd);

	pos = os_strstr(cmd, " configurator=");
	if (pos) {
		pos += 14;
		auth->conf = dpp_configurator_get_id(dpp, atoi(pos));
		if (!auth->conf) {
			wpa_printf(MSG_INFO,
				   "DPP: Could not find the specified configurator");
			return -1;
		}
	}

	if (dpp_configuration_parse(auth, cmd) < 0) {
		wpa_msg(msg_ctx, MSG_INFO,
			"DPP: Failed to set configurator parameters");
		return -1;
	}
	return 0;
}