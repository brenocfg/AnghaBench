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

/* Variables and functions */
 int PAM_DELETE_CRED ; 
 scalar_t__ PAM_SUCCESS ; 
 scalar_t__ pam_close_session (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pam_cred_established ; 
 int /*<<< orphan*/  pam_end (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ pam_err ; 
 scalar_t__ pam_session_established ; 
 scalar_t__ pam_setcred (int /*<<< orphan*/ *,int) ; 
 int pam_silent ; 
 int /*<<< orphan*/  pam_syslog (char*) ; 
 int /*<<< orphan*/ * pamh ; 

__attribute__((used)) static void
pam_cleanup(void)
{

	if (pamh != NULL) {
		if (pam_session_established) {
			pam_err = pam_close_session(pamh, 0);
			if (pam_err != PAM_SUCCESS)
				pam_syslog("pam_close_session()");
		}
		pam_session_established = 0;
		if (pam_cred_established) {
			pam_err = pam_setcred(pamh, pam_silent|PAM_DELETE_CRED);
			if (pam_err != PAM_SUCCESS)
				pam_syslog("pam_setcred()");
		}
		pam_cred_established = 0;
		pam_end(pamh, pam_err);
		pamh = NULL;
	}
}