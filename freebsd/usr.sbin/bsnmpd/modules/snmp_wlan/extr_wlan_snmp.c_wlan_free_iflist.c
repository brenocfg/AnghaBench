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
struct wlan_iface {int dummy; } ;

/* Variables and functions */
 struct wlan_iface* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_if ; 
 int /*<<< orphan*/  wlan_free_interface (struct wlan_iface*) ; 
 int /*<<< orphan*/  wlan_ifaces ; 

__attribute__((used)) static void
wlan_free_iflist(void)
{
	struct wlan_iface *w;

	while ((w = SLIST_FIRST(&wlan_ifaces)) != NULL) {
		SLIST_REMOVE_HEAD(&wlan_ifaces, w_if);
		wlan_free_interface(w);
	}
}