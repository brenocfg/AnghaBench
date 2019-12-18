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
struct wpa_sm {struct wpa_tdls_peer* tdls; int /*<<< orphan*/  tdls_supported; scalar_t__ tdls_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

const char * wpa_tdls_get_link_status(struct wpa_sm *sm, const u8 *addr)
{
	struct wpa_tdls_peer *peer;

	if (sm->tdls_disabled || !sm->tdls_supported)
		return "disabled";

	for (peer = sm->tdls; peer; peer = peer->next) {
		if (os_memcmp(peer->addr, addr, ETH_ALEN) == 0)
			break;
	}

	if (peer == NULL)
		return "peer does not exist";

	if (!peer->tpk_success)
		return "peer not connected";

	return "connected";
}