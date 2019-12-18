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
struct wpa_supplicant {int drv_flags; int /*<<< orphan*/  own_addr; int /*<<< orphan*/  wpa; int /*<<< orphan*/ * l2; int /*<<< orphan*/  ifname; int /*<<< orphan*/  p2p_mgmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_EAPOL ; 
 int /*<<< orphan*/  L2_PACKET_FILTER_PKTTYPE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE ; 
 int WPA_DRIVER_FLAGS_P2P_DEDICATED_INTERFACE ; 
 int /*<<< orphan*/  l2_packet_deinit (int /*<<< orphan*/ *) ; 
 scalar_t__ l2_packet_get_own_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * l2_packet_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ l2_packet_set_packet_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpa_drv_get_mac_addr (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_sm_set_own_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_rx_eapol ; 

int wpa_supplicant_update_mac_addr(struct wpa_supplicant *wpa_s)
{
	if ((!wpa_s->p2p_mgmt ||
	     !(wpa_s->drv_flags & WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE)) &&
	    !(wpa_s->drv_flags & WPA_DRIVER_FLAGS_P2P_DEDICATED_INTERFACE)) {
		l2_packet_deinit(wpa_s->l2);
		wpa_s->l2 = l2_packet_init(wpa_s->ifname,
					   wpa_drv_get_mac_addr(wpa_s),
					   ETH_P_EAPOL,
					   wpa_supplicant_rx_eapol, wpa_s, 0);
		if (wpa_s->l2 == NULL)
			return -1;

		if (l2_packet_set_packet_filter(wpa_s->l2,
						L2_PACKET_FILTER_PKTTYPE))
			wpa_dbg(wpa_s, MSG_DEBUG,
				"Failed to attach pkt_type filter");
	} else {
		const u8 *addr = wpa_drv_get_mac_addr(wpa_s);
		if (addr)
			os_memcpy(wpa_s->own_addr, addr, ETH_ALEN);
	}

	if (wpa_s->l2 && l2_packet_get_own_addr(wpa_s->l2, wpa_s->own_addr)) {
		wpa_msg(wpa_s, MSG_ERROR, "Failed to get own L2 address");
		return -1;
	}

	wpa_sm_set_own_addr(wpa_s->wpa, wpa_s->own_addr);

	return 0;
}