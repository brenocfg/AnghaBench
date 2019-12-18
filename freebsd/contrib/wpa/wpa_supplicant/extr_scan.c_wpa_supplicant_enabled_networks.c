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
struct wpa_supplicant {TYPE_1__* conf; scalar_t__ p2p_mgmt; } ;
struct wpa_ssid {struct wpa_ssid* next; } ;
struct TYPE_2__ {scalar_t__ auto_interworking; scalar_t__ interworking; scalar_t__ cred; struct wpa_ssid* ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpas_network_disabled (struct wpa_supplicant*,struct wpa_ssid*) ; 

int wpa_supplicant_enabled_networks(struct wpa_supplicant *wpa_s)
{
	struct wpa_ssid *ssid = wpa_s->conf->ssid;
	int count = 0, disabled = 0;

	if (wpa_s->p2p_mgmt)
		return 0; /* no normal network profiles on p2p_mgmt interface */

	while (ssid) {
		if (!wpas_network_disabled(wpa_s, ssid))
			count++;
		else
			disabled++;
		ssid = ssid->next;
	}
	if (wpa_s->conf->cred && wpa_s->conf->interworking &&
	    wpa_s->conf->auto_interworking)
		count++;
	if (count == 0 && disabled > 0) {
		wpa_dbg(wpa_s, MSG_DEBUG, "No enabled networks (%d disabled "
			"networks)", disabled);
	}
	return count;
}