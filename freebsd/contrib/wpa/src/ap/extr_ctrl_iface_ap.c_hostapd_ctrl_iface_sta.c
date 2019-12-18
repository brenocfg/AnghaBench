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
struct sta_info {int /*<<< orphan*/ * eapol_sm; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int eapol_auth_dump_state (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ fst_ctrl_iface_mb_info (int /*<<< orphan*/ *,char*,size_t) ; 
 int hostapd_ctrl_iface_sta_mib (struct hostapd_data*,struct sta_info*,char*,size_t) ; 
 scalar_t__ hwaddr_aton (char const*,int /*<<< orphan*/ *) ; 
 int os_snprintf (char*,size_t,char*) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 char* os_strchr (char const*,char) ; 
 scalar_t__ os_strcmp (char const*,char*) ; 

int hostapd_ctrl_iface_sta(struct hostapd_data *hapd, const char *txtaddr,
			   char *buf, size_t buflen)
{
	u8 addr[ETH_ALEN];
	int ret;
	const char *pos;
	struct sta_info *sta;

	if (hwaddr_aton(txtaddr, addr)) {
		ret = os_snprintf(buf, buflen, "FAIL\n");
		if (os_snprintf_error(buflen, ret))
			return 0;
		return ret;
	}

	sta = ap_get_sta(hapd, addr);
	if (sta == NULL)
		return -1;

	pos = os_strchr(txtaddr, ' ');
	if (pos) {
		pos++;

#ifdef HOSTAPD_DUMP_STATE
		if (os_strcmp(pos, "eapol") == 0) {
			if (sta->eapol_sm == NULL)
				return -1;
			return eapol_auth_dump_state(sta->eapol_sm, buf,
						     buflen);
		}
#endif /* HOSTAPD_DUMP_STATE */

		return -1;
	}

	ret = hostapd_ctrl_iface_sta_mib(hapd, sta, buf, buflen);
	ret += fst_ctrl_iface_mb_info(addr, buf + ret, buflen - ret);

	return ret;
}