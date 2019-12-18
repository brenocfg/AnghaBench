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
struct wpa_supplicant {int /*<<< orphan*/  p2pdev; scalar_t__ p2p_in_provisioning; } ;
struct wpa_ssid {scalar_t__ p2p_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_p2p_group_formation_timeout ; 

void wpas_p2p_network_removed(struct wpa_supplicant *wpa_s,
			      struct wpa_ssid *ssid)
{
	if (wpa_s->p2p_in_provisioning && ssid->p2p_group &&
	    eloop_cancel_timeout(wpas_p2p_group_formation_timeout,
				 wpa_s->p2pdev, NULL) > 0) {
		/**
		 * Remove the network by scheduling the group formation
		 * timeout to happen immediately. The teardown code
		 * needs to be scheduled to run asynch later so that we
		 * don't delete data from under ourselves unexpectedly.
		 * Calling wpas_p2p_group_formation_timeout directly
		 * causes a series of crashes in WPS failure scenarios.
		 */
		wpa_printf(MSG_DEBUG, "P2P: Canceled group formation due to "
			   "P2P group network getting removed");
		eloop_register_timeout(0, 0, wpas_p2p_group_formation_timeout,
				       wpa_s->p2pdev, NULL);
	}
}