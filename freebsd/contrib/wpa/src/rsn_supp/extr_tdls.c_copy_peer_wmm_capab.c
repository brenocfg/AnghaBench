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
struct wpa_tdls_peer {int wmm_capable; int /*<<< orphan*/  qos_info; } ;
struct wpa_eapol_ie_parse {int wmm_len; scalar_t__ wmm; } ;
struct wmm_information_element {int /*<<< orphan*/  qos_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int copy_peer_wmm_capab(const struct wpa_eapol_ie_parse *kde,
			       struct wpa_tdls_peer *peer)
{
	struct wmm_information_element *wmm;

	if (!kde->wmm) {
		wpa_printf(MSG_DEBUG, "TDLS: No supported WMM capabilities received");
		return 0;
	}

	if (kde->wmm_len < sizeof(struct wmm_information_element)) {
		wpa_printf(MSG_DEBUG, "TDLS: Invalid supported WMM capabilities received");
		return -1;
	}

	wmm = (struct wmm_information_element *) kde->wmm;
	peer->qos_info = wmm->qos_info;

	peer->wmm_capable = 1;

	wpa_printf(MSG_DEBUG, "TDLS: Peer WMM QOS Info 0x%x", peer->qos_info);
	return 0;
}