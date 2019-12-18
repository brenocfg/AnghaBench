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
struct wpa_state_machine {scalar_t__ pairwise; int /*<<< orphan*/  dot11RSNAStatsTKIPRemoteMICFailures; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {scalar_t__ wpa_group; } ;
struct wpa_authenticator {int /*<<< orphan*/  dot11RSNAStatsTKIPRemoteMICFailures; TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_INFO ; 
 scalar_t__ WPA_CIPHER_TKIP ; 
 int /*<<< orphan*/  wpa_auth_logger (struct wpa_authenticator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_auth_mic_failure_report (struct wpa_authenticator*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_auth_vlogger (struct wpa_authenticator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpa_request_new_ptk (struct wpa_state_machine*) ; 

__attribute__((used)) static int wpa_receive_error_report(struct wpa_authenticator *wpa_auth,
				    struct wpa_state_machine *sm, int group)
{
	/* Supplicant reported a Michael MIC error */
	wpa_auth_vlogger(wpa_auth, sm->addr, LOGGER_INFO,
			 "received EAPOL-Key Error Request "
			 "(STA detected Michael MIC failure (group=%d))",
			 group);

	if (group && wpa_auth->conf.wpa_group != WPA_CIPHER_TKIP) {
		wpa_auth_logger(wpa_auth, sm->addr, LOGGER_INFO,
				"ignore Michael MIC failure report since "
				"group cipher is not TKIP");
	} else if (!group && sm->pairwise != WPA_CIPHER_TKIP) {
		wpa_auth_logger(wpa_auth, sm->addr, LOGGER_INFO,
				"ignore Michael MIC failure report since "
				"pairwise cipher is not TKIP");
	} else {
		if (wpa_auth_mic_failure_report(wpa_auth, sm->addr) > 0)
			return 1; /* STA entry was removed */
		sm->dot11RSNAStatsTKIPRemoteMICFailures++;
		wpa_auth->dot11RSNAStatsTKIPRemoteMICFailures++;
	}

	/*
	 * Error report is not a request for a new key handshake, but since
	 * Authenticator may do it, let's change the keys now anyway.
	 */
	wpa_request_new_ptk(sm);
	return 0;
}