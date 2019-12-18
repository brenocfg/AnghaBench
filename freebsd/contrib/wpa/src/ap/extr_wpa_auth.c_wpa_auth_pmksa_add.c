#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  kck_len; int /*<<< orphan*/  kck; } ;
struct wpa_state_machine {scalar_t__ wpa; int /*<<< orphan*/  wpa_key_mgmt; int /*<<< orphan*/  addr; TYPE_3__* wpa_auth; TYPE_2__ PTK; } ;
struct eapol_state_machine {int dummy; } ;
struct TYPE_4__ {scalar_t__ disable_pmksa_caching; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  pmksa; TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int PMK_LEN ; 
 unsigned int PMK_LEN_SUITE_B_192 ; 
 scalar_t__ WPA_VERSION_WPA2 ; 
 scalar_t__ pmksa_cache_auth_add (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct eapol_state_machine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ wpa_key_mgmt_ft (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_sha384 (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_wpa_ieee8021x (int /*<<< orphan*/ ) ; 

int wpa_auth_pmksa_add(struct wpa_state_machine *sm, const u8 *pmk,
		       unsigned int pmk_len,
		       int session_timeout, struct eapol_state_machine *eapol)
{
	if (sm == NULL || sm->wpa != WPA_VERSION_WPA2 ||
	    sm->wpa_auth->conf.disable_pmksa_caching)
		return -1;

#ifdef CONFIG_IEEE80211R_AP
	if (pmk_len >= 2 * PMK_LEN && wpa_key_mgmt_ft(sm->wpa_key_mgmt) &&
	    wpa_key_mgmt_wpa_ieee8021x(sm->wpa_key_mgmt) &&
	    !wpa_key_mgmt_sha384(sm->wpa_key_mgmt)) {
		/* Cache MPMK/XXKey instead of initial part from MSK */
		pmk = pmk + PMK_LEN;
		pmk_len = PMK_LEN;
	} else
#endif /* CONFIG_IEEE80211R_AP */
	if (wpa_key_mgmt_sha384(sm->wpa_key_mgmt)) {
		if (pmk_len > PMK_LEN_SUITE_B_192)
			pmk_len = PMK_LEN_SUITE_B_192;
	} else if (pmk_len > PMK_LEN) {
		pmk_len = PMK_LEN;
	}

	wpa_hexdump_key(MSG_DEBUG, "RSN: Cache PMK", pmk, pmk_len);
	if (pmksa_cache_auth_add(sm->wpa_auth->pmksa, pmk, pmk_len, NULL,
				 sm->PTK.kck, sm->PTK.kck_len,
				 sm->wpa_auth->addr, sm->addr, session_timeout,
				 eapol, sm->wpa_key_mgmt))
		return 0;

	return -1;
}