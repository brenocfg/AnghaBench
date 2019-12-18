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
struct sta_info {int /*<<< orphan*/  eapol_sm; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eapol_auth_reauthenticate (int /*<<< orphan*/ ) ; 
 scalar_t__ hwaddr_aton (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hostapd_ctrl_iface_eapol_reauth(struct hostapd_data *hapd,
					   const char *cmd)
{
	u8 addr[ETH_ALEN];
	struct sta_info *sta;

	if (hwaddr_aton(cmd, addr))
		return -1;

	sta = ap_get_sta(hapd, addr);
	if (!sta || !sta->eapol_sm)
		return -1;

	eapol_auth_reauthenticate(sta->eapol_sm);
	return 0;
}