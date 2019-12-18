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
struct wpa_supplicant {int /*<<< orphan*/  ifname; struct wpa_supplicant* next; } ;
struct wpa_global {struct wpa_supplicant* ifaces; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct wpa_supplicant**) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 char* os_strchr (char*,char) ; 
 scalar_t__ os_strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int wpa_supplicant_ctrl_iface_dup_network (struct wpa_supplicant*,char*,struct wpa_supplicant*) ; 

__attribute__((used)) static int wpas_global_ctrl_iface_dup_network(struct wpa_global *global,
					      char *cmd)
{
	struct wpa_supplicant *wpa_s[2]; /* src, dst */
	char *p;
	unsigned int i;

	/* cmd: "<src ifname> <dst ifname> <src network id> <dst network id>
	 * <variable name> */

	for (i = 0; i < ARRAY_SIZE(wpa_s) ; i++) {
		p = os_strchr(cmd, ' ');
		if (p == NULL)
			return -1;
		*p = '\0';

		wpa_s[i] = global->ifaces;
		for (; wpa_s[i]; wpa_s[i] = wpa_s[i]->next) {
			if (os_strcmp(cmd, wpa_s[i]->ifname) == 0)
				break;
		}

		if (!wpa_s[i]) {
			wpa_printf(MSG_DEBUG,
				   "CTRL_IFACE: Could not find iface=%s", cmd);
			return -1;
		}

		cmd = p + 1;
	}

	return wpa_supplicant_ctrl_iface_dup_network(wpa_s[0], cmd, wpa_s[1]);
}