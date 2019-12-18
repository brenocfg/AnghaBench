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
struct TYPE_4__ {int idx; int /*<<< orphan*/ * len; int /*<<< orphan*/ * key; scalar_t__ default_len; } ;
struct hostapd_ssid {TYPE_2__ wep; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_3__ {int /*<<< orphan*/  iface; struct hostapd_ssid ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  WPA_ALG_WEP ; 
 int /*<<< orphan*/  broadcast_ether_addr ; 
 scalar_t__ hostapd_drv_set_key (int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hostapd_broadcast_wep_set(struct hostapd_data *hapd)
{
	int errors = 0, idx;
	struct hostapd_ssid *ssid = &hapd->conf->ssid;

	idx = ssid->wep.idx;
	if (ssid->wep.default_len &&
	    hostapd_drv_set_key(hapd->conf->iface,
				hapd, WPA_ALG_WEP, broadcast_ether_addr, idx,
				1, NULL, 0, ssid->wep.key[idx],
				ssid->wep.len[idx])) {
		wpa_printf(MSG_WARNING, "Could not set WEP encryption.");
		errors++;
	}

	return errors;
}