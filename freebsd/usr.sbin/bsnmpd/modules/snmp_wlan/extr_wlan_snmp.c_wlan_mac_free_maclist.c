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
struct wlan_mac_mac {int dummy; } ;
struct wlan_iface {int /*<<< orphan*/  mac_maclist; } ;

/* Variables and functions */
 struct wlan_mac_mac* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct wlan_mac_mac*) ; 
 int /*<<< orphan*/  wm ; 

__attribute__((used)) static void
wlan_mac_free_maclist(struct wlan_iface *wif)
{
	struct wlan_mac_mac *wmm;

	while ((wmm = SLIST_FIRST(&wif->mac_maclist)) != NULL) {
		SLIST_REMOVE_HEAD(&wif->mac_maclist, wm);
		free(wmm);
	}

	SLIST_INIT(&wif->mac_maclist);
}