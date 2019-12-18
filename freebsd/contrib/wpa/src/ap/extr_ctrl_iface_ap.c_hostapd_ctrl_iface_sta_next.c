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
struct sta_info {int /*<<< orphan*/  next; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int hostapd_ctrl_iface_sta_mib (struct hostapd_data*,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ hwaddr_aton (char const*,int /*<<< orphan*/ *) ; 
 int os_snprintf (char*,size_t,char*) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 

int hostapd_ctrl_iface_sta_next(struct hostapd_data *hapd, const char *txtaddr,
				char *buf, size_t buflen)
{
	u8 addr[ETH_ALEN];
	struct sta_info *sta;
	int ret;

	if (hwaddr_aton(txtaddr, addr) ||
	    (sta = ap_get_sta(hapd, addr)) == NULL) {
		ret = os_snprintf(buf, buflen, "FAIL\n");
		if (os_snprintf_error(buflen, ret))
			return 0;
		return ret;
	}

	if (!sta->next)
		return 0;

	return hostapd_ctrl_iface_sta_mib(hapd, sta->next, buf, buflen);
}