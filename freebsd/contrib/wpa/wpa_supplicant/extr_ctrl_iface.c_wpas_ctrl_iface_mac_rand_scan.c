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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {unsigned int mac_addr_rand_supported; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 unsigned int MAC_ADDR_RAND_PNO ; 
 unsigned int MAC_ADDR_RAND_SCAN ; 
 unsigned int MAC_ADDR_RAND_SCHED_SCAN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 unsigned int atoi (char*) ; 
 scalar_t__ hwaddr_aton (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ os_strcasecmp (char*,char*) ; 
 scalar_t__ os_strncasecmp (char*,char*,int) ; 
 char* str_token (char*,char*,char**) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int wpas_disable_mac_addr_randomization (struct wpa_supplicant*,unsigned int) ; 
 int wpas_enable_mac_addr_randomization (struct wpa_supplicant*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wpas_ctrl_iface_mac_rand_scan(struct wpa_supplicant *wpa_s,
					 char *cmd)
{
	char *token, *context = NULL;
	unsigned int enable = ~0, type = 0;
	u8 _addr[ETH_ALEN], _mask[ETH_ALEN];
	u8 *addr = NULL, *mask = NULL;

	while ((token = str_token(cmd, " ", &context))) {
		if (os_strcasecmp(token, "scan") == 0) {
			type |= MAC_ADDR_RAND_SCAN;
		} else if (os_strcasecmp(token, "sched") == 0) {
			type |= MAC_ADDR_RAND_SCHED_SCAN;
		} else if (os_strcasecmp(token, "pno") == 0) {
			type |= MAC_ADDR_RAND_PNO;
		} else if (os_strcasecmp(token, "all") == 0) {
			type = wpa_s->mac_addr_rand_supported;
		} else if (os_strncasecmp(token, "enable=", 7) == 0) {
			enable = atoi(token + 7);
		} else if (os_strncasecmp(token, "addr=", 5) == 0) {
			addr = _addr;
			if (hwaddr_aton(token + 5, addr)) {
				wpa_printf(MSG_INFO,
					   "CTRL: Invalid MAC address: %s",
					   token);
				return -1;
			}
		} else if (os_strncasecmp(token, "mask=", 5) == 0) {
			mask = _mask;
			if (hwaddr_aton(token + 5, mask)) {
				wpa_printf(MSG_INFO,
					   "CTRL: Invalid MAC address mask: %s",
					   token);
				return -1;
			}
		} else {
			wpa_printf(MSG_INFO,
				   "CTRL: Invalid MAC_RAND_SCAN parameter: %s",
				   token);
			return -1;
		}
	}

	if (!type) {
		wpa_printf(MSG_INFO, "CTRL: MAC_RAND_SCAN no type specified");
		return -1;
	}

	if (enable > 1) {
		wpa_printf(MSG_INFO,
			   "CTRL: MAC_RAND_SCAN enable=<0/1> not specified");
		return -1;
	}

	if (!enable)
		return wpas_disable_mac_addr_randomization(wpa_s, type);

	return wpas_enable_mac_addr_randomization(wpa_s, type, addr, mask);
}