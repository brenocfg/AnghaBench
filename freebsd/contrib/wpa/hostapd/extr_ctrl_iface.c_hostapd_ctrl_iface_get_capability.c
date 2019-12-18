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
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int os_snprintf (char*,size_t,char*) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 scalar_t__ os_strcmp (char const*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int hostapd_ctrl_iface_get_capability(struct hostapd_data *hapd,
					     const char *field, char *buf,
					     size_t buflen)
{
	wpa_printf(MSG_DEBUG, "CTRL_IFACE: GET_CAPABILITY '%s'", field);

#ifdef CONFIG_DPP
	if (os_strcmp(field, "dpp") == 0) {
		int res;

#ifdef CONFIG_DPP2
		res = os_snprintf(buf, buflen, "DPP=2");
#else /* CONFIG_DPP2 */
		res = os_snprintf(buf, buflen, "DPP=1");
#endif /* CONFIG_DPP2 */
		if (os_snprintf_error(buflen, res))
			return -1;
		return res;
	}
#endif /* CONFIG_DPP */

	wpa_printf(MSG_DEBUG, "CTRL_IFACE: Unknown GET_CAPABILITY field '%s'",
		   field);

	return -1;
}