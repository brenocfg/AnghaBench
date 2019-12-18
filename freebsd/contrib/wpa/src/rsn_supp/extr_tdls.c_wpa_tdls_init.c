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
struct wpa_sm {int tdls_supported; scalar_t__ tdls_chan_switch; scalar_t__ tdls_external_setup; int /*<<< orphan*/ * l2_tdls; int /*<<< orphan*/  own_addr; scalar_t__ ifname; scalar_t__ bridge_ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_80211_ENCAP ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/ * l2_packet_init (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_sm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_sm_tdls_get_capa (struct wpa_sm*,int*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  wpa_supplicant_rx_tdls ; 

int wpa_tdls_init(struct wpa_sm *sm)
{
	if (sm == NULL)
		return -1;

	sm->l2_tdls = l2_packet_init(sm->bridge_ifname ? sm->bridge_ifname :
				     sm->ifname,
				     sm->own_addr,
				     ETH_P_80211_ENCAP, wpa_supplicant_rx_tdls,
				     sm, 0);
	if (sm->l2_tdls == NULL) {
		wpa_printf(MSG_ERROR, "TDLS: Failed to open l2_packet "
			   "connection");
		return -1;
	}

	/*
	 * Drivers that support TDLS but don't implement the get_capa callback
	 * are assumed to perform everything internally
	 */
	if (wpa_sm_tdls_get_capa(sm, &sm->tdls_supported,
				 &sm->tdls_external_setup,
				 &sm->tdls_chan_switch) < 0) {
		sm->tdls_supported = 1;
		sm->tdls_external_setup = 0;
	}

	wpa_printf(MSG_DEBUG, "TDLS: TDLS operation%s supported by "
		   "driver", sm->tdls_supported ? "" : " not");
	wpa_printf(MSG_DEBUG, "TDLS: Driver uses %s link setup",
		   sm->tdls_external_setup ? "external" : "internal");
	wpa_printf(MSG_DEBUG, "TDLS: Driver %s TDLS channel switching",
		   sm->tdls_chan_switch ? "supports" : "does not support");

	return 0;
}