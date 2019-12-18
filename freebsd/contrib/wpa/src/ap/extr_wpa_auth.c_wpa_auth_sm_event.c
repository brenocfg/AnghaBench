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
struct wpa_state_machine {int started; int ft_completed; int fils_completed; void* changed; scalar_t__ in_step_loop; int /*<<< orphan*/  PTK; void* PTK_valid; int /*<<< orphan*/  wpa_key_mgmt; scalar_t__ mgmt_frame_prot; void* tk_already_set; void* ReAuthenticationRequest; void* PtkGroupInit; void* GUpdateStationKeys; TYPE_1__* group; void* AuthenticationRequest; void* Init; int /*<<< orphan*/  pmk_r1_len; int /*<<< orphan*/ * pmk_r1; int /*<<< orphan*/  xxkey_len; int /*<<< orphan*/ * xxkey; int /*<<< orphan*/  pmk_len; int /*<<< orphan*/ * PMK; void* DeauthenticationRequest; int /*<<< orphan*/  addr; int /*<<< orphan*/  wpa_auth; } ;
typedef  enum wpa_event { ____Placeholder_wpa_event } wpa_event ;
struct TYPE_2__ {int /*<<< orphan*/  GKeyDoneStations; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  LOGGER_DEBUG ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* TRUE ; 
#define  WPA_ASSOC 136 
#define  WPA_ASSOC_FILS 135 
#define  WPA_ASSOC_FT 134 
#define  WPA_AUTH 133 
#define  WPA_DEAUTH 132 
#define  WPA_DISASSOC 131 
#define  WPA_DRV_STA_REMOVED 130 
#define  WPA_REAUTH 129 
#define  WPA_REAUTH_EAPOL 128 
 int /*<<< orphan*/  fils_set_tk (struct wpa_state_machine*) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_auth_set_ptk_rekey_timer (struct wpa_state_machine*) ; 
 int /*<<< orphan*/  wpa_auth_start_ampe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_auth_vlogger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpa_ft_install_ptk (struct wpa_state_machine*) ; 
 scalar_t__ wpa_key_mgmt_fils (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_remove_ptk (struct wpa_state_machine*) ; 
 int wpa_sm_step (struct wpa_state_machine*) ; 

int wpa_auth_sm_event(struct wpa_state_machine *sm, enum wpa_event event)
{
	int remove_ptk = 1;

	if (sm == NULL)
		return -1;

	wpa_auth_vlogger(sm->wpa_auth, sm->addr, LOGGER_DEBUG,
			 "event %d notification", event);

	switch (event) {
	case WPA_AUTH:
#ifdef CONFIG_MESH
		/* PTKs are derived through AMPE */
		if (wpa_auth_start_ampe(sm->wpa_auth, sm->addr)) {
			/* not mesh */
			break;
		}
		return 0;
#endif /* CONFIG_MESH */
	case WPA_ASSOC:
		break;
	case WPA_DEAUTH:
	case WPA_DISASSOC:
		sm->DeauthenticationRequest = TRUE;
#ifdef CONFIG_IEEE80211R_AP
		os_memset(sm->PMK, 0, sizeof(sm->PMK));
		sm->pmk_len = 0;
		os_memset(sm->xxkey, 0, sizeof(sm->xxkey));
		sm->xxkey_len = 0;
		os_memset(sm->pmk_r1, 0, sizeof(sm->pmk_r1));
		sm->pmk_r1_len = 0;
#endif /* CONFIG_IEEE80211R_AP */
		break;
	case WPA_REAUTH:
	case WPA_REAUTH_EAPOL:
		if (!sm->started) {
			/*
			 * When using WPS, we may end up here if the STA
			 * manages to re-associate without the previous STA
			 * entry getting removed. Consequently, we need to make
			 * sure that the WPA state machines gets initialized
			 * properly at this point.
			 */
			wpa_printf(MSG_DEBUG, "WPA state machine had not been "
				   "started - initialize now");
			sm->started = 1;
			sm->Init = TRUE;
			if (wpa_sm_step(sm) == 1)
				return 1; /* should not really happen */
			sm->Init = FALSE;
			sm->AuthenticationRequest = TRUE;
			break;
		}
		if (sm->GUpdateStationKeys) {
			/*
			 * Reauthentication cancels the pending group key
			 * update for this STA.
			 */
			sm->group->GKeyDoneStations--;
			sm->GUpdateStationKeys = FALSE;
			sm->PtkGroupInit = TRUE;
		}
		sm->ReAuthenticationRequest = TRUE;
		break;
	case WPA_ASSOC_FT:
#ifdef CONFIG_IEEE80211R_AP
		wpa_printf(MSG_DEBUG, "FT: Retry PTK configuration "
			   "after association");
		wpa_ft_install_ptk(sm);

		/* Using FT protocol, not WPA auth state machine */
		sm->ft_completed = 1;
		wpa_auth_set_ptk_rekey_timer(sm);
		return 0;
#else /* CONFIG_IEEE80211R_AP */
		break;
#endif /* CONFIG_IEEE80211R_AP */
	case WPA_ASSOC_FILS:
#ifdef CONFIG_FILS
		wpa_printf(MSG_DEBUG,
			   "FILS: TK configuration after association");
		fils_set_tk(sm);
		sm->fils_completed = 1;
		return 0;
#else /* CONFIG_FILS */
		break;
#endif /* CONFIG_FILS */
	case WPA_DRV_STA_REMOVED:
		sm->tk_already_set = FALSE;
		return 0;
	}

#ifdef CONFIG_IEEE80211R_AP
	sm->ft_completed = 0;
#endif /* CONFIG_IEEE80211R_AP */

#ifdef CONFIG_IEEE80211W
	if (sm->mgmt_frame_prot && event == WPA_AUTH)
		remove_ptk = 0;
#endif /* CONFIG_IEEE80211W */
#ifdef CONFIG_FILS
	if (wpa_key_mgmt_fils(sm->wpa_key_mgmt) &&
	    (event == WPA_AUTH || event == WPA_ASSOC))
		remove_ptk = 0;
#endif /* CONFIG_FILS */

	if (remove_ptk) {
		sm->PTK_valid = FALSE;
		os_memset(&sm->PTK, 0, sizeof(sm->PTK));

		if (event != WPA_REAUTH_EAPOL)
			wpa_remove_ptk(sm);
	}

	if (sm->in_step_loop) {
		/*
		 * wpa_sm_step() is already running - avoid recursive call to
		 * it by making the existing loop process the new update.
		 */
		sm->changed = TRUE;
		return 0;
	}
	return wpa_sm_step(sm);
}