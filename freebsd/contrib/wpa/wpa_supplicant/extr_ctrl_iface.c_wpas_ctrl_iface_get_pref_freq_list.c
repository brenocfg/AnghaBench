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
struct wpa_supplicant {int dummy; } ;
typedef  enum wpa_driver_if_type { ____Placeholder_wpa_driver_if_type } wpa_driver_if_type ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_IF_AP_BSS ; 
 int WPA_IF_IBSS ; 
 int WPA_IF_P2P_CLIENT ; 
 int WPA_IF_P2P_GO ; 
 int WPA_IF_STATION ; 
 int WPA_IF_TDLS ; 
 int os_snprintf (char*,int,char*,char*,unsigned int) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int wpa_drv_get_pref_freq_list (struct wpa_supplicant*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,char*) ; 

__attribute__((used)) static int wpas_ctrl_iface_get_pref_freq_list(
	struct wpa_supplicant *wpa_s, char *cmd, char *buf, size_t buflen)
{
	unsigned int freq_list[100], num = 100, i;
	int ret;
	enum wpa_driver_if_type iface_type;
	char *pos, *end;

	pos = buf;
	end = buf + buflen;

	/* buf: "<interface_type>" */
	if (os_strcmp(cmd, "STATION") == 0)
		iface_type = WPA_IF_STATION;
	else if (os_strcmp(cmd, "AP") == 0)
		iface_type = WPA_IF_AP_BSS;
	else if (os_strcmp(cmd, "P2P_GO") == 0)
		iface_type = WPA_IF_P2P_GO;
	else if (os_strcmp(cmd, "P2P_CLIENT") == 0)
		iface_type = WPA_IF_P2P_CLIENT;
	else if (os_strcmp(cmd, "IBSS") == 0)
		iface_type = WPA_IF_IBSS;
	else if (os_strcmp(cmd, "TDLS") == 0)
		iface_type = WPA_IF_TDLS;
	else
		return -1;

	wpa_printf(MSG_DEBUG,
		   "CTRL_IFACE: GET_PREF_FREQ_LIST iface_type=%d (%s)",
		   iface_type, cmd);

	ret = wpa_drv_get_pref_freq_list(wpa_s, iface_type, &num, freq_list);
	if (ret)
		return -1;

	for (i = 0; i < num; i++) {
		ret = os_snprintf(pos, end - pos, "%s%u",
				  i > 0 ? "," : "", freq_list[i]);
		if (os_snprintf_error(end - pos, ret))
			return -1;
		pos += ret;
	}

	return pos - buf;
}