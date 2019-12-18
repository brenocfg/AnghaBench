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
struct wlan_iface {struct wlan_iface* chanlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct wlan_iface*) ; 
 int /*<<< orphan*/  wlan_free_peerlist (struct wlan_iface*) ; 
 int /*<<< orphan*/  wlan_mac_free_maclist (struct wlan_iface*) ; 
 int /*<<< orphan*/  wlan_mesh_free_routes (struct wlan_iface*) ; 
 int /*<<< orphan*/  wlan_scan_free_results (struct wlan_iface*) ; 

__attribute__((used)) static void
wlan_free_interface(struct wlan_iface *wif)
{
	wlan_free_peerlist(wif);
	free(wif->chanlist);
	wlan_scan_free_results(wif);
	wlan_mac_free_maclist(wif);
	wlan_mesh_free_routes(wif);
	free(wif);
}