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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_ssid {int update_identifier; struct wpa_cred* parent_cred; } ;
struct wpa_cred {int update_identifier; struct wpa_cred* next; } ;
struct TYPE_2__ {struct wpa_cred* cred; } ;

/* Variables and functions */

int hs20_get_pps_mo_id(struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid)
{
	struct wpa_cred *cred;

	if (ssid == NULL)
		return 0;

	if (ssid->update_identifier)
		return ssid->update_identifier;

	if (ssid->parent_cred == NULL)
		return 0;

	for (cred = wpa_s->conf->cred; cred; cred = cred->next) {
		if (ssid->parent_cred == cred)
			return cred->update_identifier;
	}

	return 0;
}