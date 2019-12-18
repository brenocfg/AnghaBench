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
struct wlan_iface {scalar_t__ mode; scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ RowStatus_active ; 
 scalar_t__ WlanIfaceOperatingModeType_meshPoint ; 
 struct wlan_iface* wlan_next_interface (struct wlan_iface*) ; 

__attribute__((used)) static struct wlan_iface *
wlan_mesh_next_interface(struct wlan_iface *wif)
{
	struct wlan_iface *nwif;

	while ((nwif = wlan_next_interface(wif)) != NULL) {
		if (nwif->mode == WlanIfaceOperatingModeType_meshPoint &&
		    nwif->status == RowStatus_active)
			break;
		wif = nwif;
	}

	return (nwif);
}