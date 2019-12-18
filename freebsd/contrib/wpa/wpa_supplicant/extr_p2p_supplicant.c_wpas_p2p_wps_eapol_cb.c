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
struct wpa_supplicant {int /*<<< orphan*/  p2p_in_provisioning; TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p_fail_on_wps_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_p2p_grpform_fail_after_wps (struct wpa_supplicant*) ; 

int wpas_p2p_wps_eapol_cb(struct wpa_supplicant *wpa_s)
{
	if (!wpa_s->global->p2p_fail_on_wps_complete ||
	    !wpa_s->p2p_in_provisioning)
		return 0;

	wpas_p2p_grpform_fail_after_wps(wpa_s);

	return 1;
}