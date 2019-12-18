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
struct wpa_supplicant {int /*<<< orphan*/  eapol; int /*<<< orphan*/  wpa; } ;
struct wpa_ie_data {size_t num_pmkid; int /*<<< orphan*/ * pmkid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t PMKID_LEN ; 
 int /*<<< orphan*/  eapol_sm_notify_pmkid_attempt (int /*<<< orphan*/ ) ; 
 int pmksa_cache_set_current (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ wpa_sm_parse_own_wpa_ie (int /*<<< orphan*/ ,struct wpa_ie_data*) ; 

__attribute__((used)) static void wpa_find_assoc_pmkid(struct wpa_supplicant *wpa_s)
{
	struct wpa_ie_data ie;
	int pmksa_set = -1;
	size_t i;

	if (wpa_sm_parse_own_wpa_ie(wpa_s->wpa, &ie) < 0 ||
	    ie.pmkid == NULL)
		return;

	for (i = 0; i < ie.num_pmkid; i++) {
		pmksa_set = pmksa_cache_set_current(wpa_s->wpa,
						    ie.pmkid + i * PMKID_LEN,
						    NULL, NULL, 0, NULL, 0);
		if (pmksa_set == 0) {
			eapol_sm_notify_pmkid_attempt(wpa_s->eapol);
			break;
		}
	}

	wpa_dbg(wpa_s, MSG_DEBUG, "RSN: PMKID from assoc IE %sfound from "
		"PMKSA cache", pmksa_set == 0 ? "" : "not ");
}