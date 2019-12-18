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
struct wpa_tdls_peer {int /*<<< orphan*/  tpk_success; int /*<<< orphan*/  addr; struct wpa_tdls_peer* next; } ;
struct wpa_sm {scalar_t__ tdls_external_setup; struct wpa_tdls_peer* tdls; int /*<<< orphan*/  tdls_supported; scalar_t__ tdls_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_tdls_do_teardown (struct wpa_sm*,struct wpa_tdls_peer*,int /*<<< orphan*/ ) ; 

void wpa_tdls_remove(struct wpa_sm *sm, const u8 *addr)
{
	struct wpa_tdls_peer *peer;

	if (sm->tdls_disabled || !sm->tdls_supported)
		return;

	for (peer = sm->tdls; peer; peer = peer->next) {
		if (os_memcmp(peer->addr, addr, ETH_ALEN) == 0)
			break;
	}

	if (peer == NULL || !peer->tpk_success)
		return;

	if (sm->tdls_external_setup) {
		/*
		 * Disable previous link to allow renegotiation to be completed
		 * on AP path.
		 */
		wpa_tdls_do_teardown(sm, peer,
				     WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED);
	}
}