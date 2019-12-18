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
struct wpa_supplicant {int dummy; } ;
struct hostapd_iface {TYPE_1__* mconf; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rsn_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_interface_deinit (struct hostapd_iface*) ; 
 int /*<<< orphan*/  hostapd_interface_free (struct hostapd_iface*) ; 
 int /*<<< orphan*/  mesh_mpm_deinit (struct wpa_supplicant*,struct hostapd_iface*) ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 

void wpa_supplicant_mesh_iface_deinit(struct wpa_supplicant *wpa_s,
				      struct hostapd_iface *ifmsh)
{
	if (!ifmsh)
		return;

	if (ifmsh->mconf) {
		mesh_mpm_deinit(wpa_s, ifmsh);
		if (ifmsh->mconf->rsn_ie) {
			ifmsh->mconf->rsn_ie = NULL;
			/* We cannot free this struct
			 * because wpa_authenticator on
			 * hostapd side is also using it
			 * for now just set to NULL and
			 * let hostapd code free it.
			 */
		}
		os_free(ifmsh->mconf);
		ifmsh->mconf = NULL;
	}

	/* take care of shared data */
	hostapd_interface_deinit(ifmsh);
	hostapd_interface_free(ifmsh);
}