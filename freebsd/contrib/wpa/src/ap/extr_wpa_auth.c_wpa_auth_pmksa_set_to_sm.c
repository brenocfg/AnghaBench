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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_state_machine {struct rsn_pmksa_cache_entry* pmksa; } ;
struct wpa_authenticator {int /*<<< orphan*/ * dot11RSNAPMKIDUsed; } ;
struct rsn_pmksa_cache_entry {int /*<<< orphan*/  pmkid; int /*<<< orphan*/  pmk; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMKID_LEN ; 
 int /*<<< orphan*/  PMK_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wpa_auth_pmksa_set_to_sm(struct rsn_pmksa_cache_entry *pmksa,
			      struct wpa_state_machine *sm,
			      struct wpa_authenticator *wpa_auth,
			      u8 *pmkid, u8 *pmk)
{
	if (!sm)
		return;

	sm->pmksa = pmksa;
	os_memcpy(pmk, pmksa->pmk, PMK_LEN);
	os_memcpy(pmkid, pmksa->pmkid, PMKID_LEN);
	os_memcpy(wpa_auth->dot11RSNAPMKIDUsed, pmksa->pmkid, PMKID_LEN);
}