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
struct wlan_peer {int dummy; } ;
struct wlan_iface {int /*<<< orphan*/  peerlist; } ;

/* Variables and functions */
 struct wlan_peer* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct wlan_peer*) ; 
 int /*<<< orphan*/  wp ; 

__attribute__((used)) static void
wlan_free_peerlist(struct wlan_iface *wif)
{
	struct wlan_peer *wip;

	while ((wip = SLIST_FIRST(&wif->peerlist)) != NULL) {
		SLIST_REMOVE_HEAD(&wif->peerlist, wp);
		free(wip);
	}

	SLIST_INIT(&wif->peerlist);
}