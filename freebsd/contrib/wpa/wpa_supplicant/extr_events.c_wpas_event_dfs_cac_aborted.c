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
struct wpa_supplicant {scalar_t__ ifmsh; scalar_t__ ap_iface; } ;
struct dfs_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_ap_event_dfs_cac_aborted (struct wpa_supplicant*,struct dfs_event*) ; 
 int /*<<< orphan*/  wpas_auth_timeout_restart (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_event_dfs_cac_aborted(struct wpa_supplicant *wpa_s,
				       struct dfs_event *radar)
{
#if defined(NEED_AP_MLME) && defined(CONFIG_AP)
	if (wpa_s->ap_iface || wpa_s->ifmsh) {
		wpas_ap_event_dfs_cac_aborted(wpa_s, radar);
	} else
#endif /* NEED_AP_MLME && CONFIG_AP */
	{
		/* Restart auth timeout with original value after CAC is
		 * aborted */
		wpas_auth_timeout_restart(wpa_s, 0);
	}
}