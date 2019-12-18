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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct hostapd_data {int /*<<< orphan*/  msg_ctx; TYPE_1__* conf; TYPE_2__* iface; int /*<<< orphan*/ * drv_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  driver_ap_teardown; } ;
struct TYPE_3__ {scalar_t__ broadcast_deauth; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ hostapd_drv_none (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_drv_sta_deauth (struct hostapd_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hostapd_flush (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_free_stas (struct hostapd_data*) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wpa_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hostapd_flush_old_stations(struct hostapd_data *hapd, u16 reason)
{
	int ret = 0;
	u8 addr[ETH_ALEN];

	if (hostapd_drv_none(hapd) || hapd->drv_priv == NULL)
		return 0;

	if (!hapd->iface->driver_ap_teardown) {
		wpa_dbg(hapd->msg_ctx, MSG_DEBUG,
			"Flushing old station entries");

		if (hostapd_flush(hapd)) {
			wpa_msg(hapd->msg_ctx, MSG_WARNING,
				"Could not connect to kernel driver");
			ret = -1;
		}
	}
	if (hapd->conf && hapd->conf->broadcast_deauth) {
		wpa_dbg(hapd->msg_ctx, MSG_DEBUG,
			"Deauthenticate all stations");
		os_memset(addr, 0xff, ETH_ALEN);
		hostapd_drv_sta_deauth(hapd, addr, reason);
	}
	hostapd_free_stas(hapd);

	return ret;
}