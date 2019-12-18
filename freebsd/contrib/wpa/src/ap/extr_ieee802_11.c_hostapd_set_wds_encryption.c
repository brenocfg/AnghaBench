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
struct sta_info {int dummy; } ;
struct TYPE_4__ {int idx; int /*<<< orphan*/ * len; scalar_t__* key; } ;
struct hostapd_ssid {TYPE_2__ wep; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_3__ {scalar_t__ wpa; scalar_t__ ieee802_1x; struct hostapd_ssid ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  WPA_ALG_WEP ; 
 scalar_t__ hostapd_drv_set_key (char*,struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void hostapd_set_wds_encryption(struct hostapd_data *hapd,
				       struct sta_info *sta,
				       char *ifname_wds)
{
	int i;
	struct hostapd_ssid *ssid = &hapd->conf->ssid;

	if (hapd->conf->ieee802_1x || hapd->conf->wpa)
		return;

	for (i = 0; i < 4; i++) {
		if (ssid->wep.key[i] &&
		    hostapd_drv_set_key(ifname_wds, hapd, WPA_ALG_WEP, NULL, i,
					i == ssid->wep.idx, NULL, 0,
					ssid->wep.key[i], ssid->wep.len[i])) {
			wpa_printf(MSG_WARNING,
				   "Could not set WEP keys for WDS interface; %s",
				   ifname_wds);
			break;
		}
	}
}