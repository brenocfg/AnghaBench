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
struct wpa_supplicant {int /*<<< orphan*/  ifname; struct wpa_supplicant* next; int /*<<< orphan*/  const* own_addr; TYPE_1__* global; struct wpa_supplicant* parent; int /*<<< orphan*/  pending_action_tx; scalar_t__ ap_iface; scalar_t__ p2p_mgmt; } ;
struct TYPE_2__ {struct wpa_supplicant* ifaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WLAN_ACTION_PUBLIC ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* wpabuf_head_u8 (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpa_supplicant *
wpas_get_tx_interface(struct wpa_supplicant *wpa_s, const u8 *src)
{
	struct wpa_supplicant *iface;

	if (os_memcmp(src, wpa_s->own_addr, ETH_ALEN) == 0) {
#ifdef CONFIG_P2P
		if (wpa_s->p2p_mgmt && wpa_s != wpa_s->parent &&
		    wpa_s->parent->ap_iface &&
		    os_memcmp(wpa_s->parent->own_addr,
			      wpa_s->own_addr, ETH_ALEN) == 0 &&
		    wpabuf_len(wpa_s->pending_action_tx) >= 2 &&
		    *wpabuf_head_u8(wpa_s->pending_action_tx) !=
		    WLAN_ACTION_PUBLIC) {
			/*
			 * When P2P Device interface has same MAC address as
			 * the GO interface, make sure non-Public Action frames
			 * are sent through the GO interface. The P2P Device
			 * interface can only send Public Action frames.
			 */
			wpa_printf(MSG_DEBUG,
				   "P2P: Use GO interface %s instead of interface %s for Action TX",
				   wpa_s->parent->ifname, wpa_s->ifname);
			return wpa_s->parent;
		}
#endif /* CONFIG_P2P */
		return wpa_s;
	}

	/*
	 * Try to find a group interface that matches with the source address.
	 */
	iface = wpa_s->global->ifaces;
	while (iface) {
		if (os_memcmp(src, iface->own_addr, ETH_ALEN) == 0)
			break;
		iface = iface->next;
	}
	if (iface) {
		wpa_printf(MSG_DEBUG, "P2P: Use group interface %s "
			   "instead of interface %s for Action TX",
			   iface->ifname, wpa_s->ifname);
		return iface;
	}

	return wpa_s;
}