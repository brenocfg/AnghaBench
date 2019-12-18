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
struct wpa_supplicant {TYPE_1__* ap_iface; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int) ; 

void ap_eapol_tx_status(void *ctx, const u8 *dst,
			const u8 *data, size_t len, int ack)
{
#ifdef NEED_AP_MLME
	struct wpa_supplicant *wpa_s = ctx;
	if (!wpa_s->ap_iface)
		return;
	hostapd_tx_status(wpa_s->ap_iface->bss[0], dst, data, len, ack);
#endif /* NEED_AP_MLME */
}