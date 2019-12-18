#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {scalar_t__ agreed_to_steer; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  disassoc_low_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE80211 ; 
 int /*<<< orphan*/  WLAN_REASON_DISASSOC_LOW_ACK ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ap_sta_disassociate (struct hostapd_data*,struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_drv_sta_disassoc (struct hostapd_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void hostapd_event_sta_low_ack(struct hostapd_data *hapd, const u8 *addr)
{
	struct sta_info *sta = ap_get_sta(hapd, addr);

	if (!sta || !hapd->conf->disassoc_low_ack || sta->agreed_to_steer)
		return;

	hostapd_logger(hapd, addr, HOSTAPD_MODULE_IEEE80211,
		       HOSTAPD_LEVEL_INFO,
		       "disconnected due to excessive missing ACKs");
	hostapd_drv_sta_disassoc(hapd, addr, WLAN_REASON_DISASSOC_LOW_ACK);
	ap_sta_disassociate(hapd, sta, WLAN_REASON_DISASSOC_LOW_ACK);
}