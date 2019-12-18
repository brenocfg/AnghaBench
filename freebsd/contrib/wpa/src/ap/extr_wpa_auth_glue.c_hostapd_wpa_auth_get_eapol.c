#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int wpa_eapol_variable ;
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {TYPE_2__* eapol_sm; } ;
struct hostapd_data {int dummy; } ;
struct TYPE_4__ {int keyRun; TYPE_1__* eap_if; } ;
struct TYPE_3__ {int eapKeyAvailable; } ;

/* Variables and functions */
#define  WPA_EAPOL_keyAvailable 129 
#define  WPA_EAPOL_keyRun 128 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int hostapd_wpa_auth_get_eapol(void *ctx, const u8 *addr,
				      wpa_eapol_variable var)
{
	struct hostapd_data *hapd = ctx;
	struct sta_info *sta = ap_get_sta(hapd, addr);
	if (sta == NULL || sta->eapol_sm == NULL)
		return -1;
	switch (var) {
	case WPA_EAPOL_keyRun:
		return sta->eapol_sm->keyRun;
	case WPA_EAPOL_keyAvailable:
		return sta->eapol_sm->eap_if->eapKeyAvailable;
	default:
		return -1;
	}
}