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
struct wpa_supplicant {TYPE_1__* ap_iface; } ;
struct rx_mgmt {int /*<<< orphan*/  frame_len; int /*<<< orphan*/  frame; int /*<<< orphan*/  ssi_signal; int /*<<< orphan*/  datarate; } ;
struct hostapd_frame_info {int /*<<< orphan*/  ssi_signal; int /*<<< orphan*/  datarate; } ;
typedef  int /*<<< orphan*/  fi ;
struct TYPE_2__ {int /*<<< orphan*/ * bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee802_11_mgmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hostapd_frame_info*) ; 
 int /*<<< orphan*/  os_memset (struct hostapd_frame_info*,int /*<<< orphan*/ ,int) ; 

void ap_mgmt_rx(void *ctx, struct rx_mgmt *rx_mgmt)
{
#ifdef NEED_AP_MLME
	struct wpa_supplicant *wpa_s = ctx;
	struct hostapd_frame_info fi;
	os_memset(&fi, 0, sizeof(fi));
	fi.datarate = rx_mgmt->datarate;
	fi.ssi_signal = rx_mgmt->ssi_signal;
	ieee802_11_mgmt(wpa_s->ap_iface->bss[0], rx_mgmt->frame,
			rx_mgmt->frame_len, &fi);
#endif /* NEED_AP_MLME */
}