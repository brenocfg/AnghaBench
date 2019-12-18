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
 int /*<<< orphan*/  PAM_CONV ; 
 int /*<<< orphan*/  PAM_DELETE_CRED ; 
 int /*<<< orphan*/  PAM_SILENT ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  mm_is_monitor () ; 
 int /*<<< orphan*/  null_conv ; 
 int /*<<< orphan*/  pam_close_session (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pam_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pam_set_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  pam_setcred (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sshpam_authenticated ; 
 scalar_t__ sshpam_cred_established ; 
 int /*<<< orphan*/  sshpam_err ; 
 int /*<<< orphan*/ * sshpam_handle ; 
 scalar_t__ sshpam_session_open ; 
 scalar_t__ use_privsep ; 

void
sshpam_cleanup(void)
{
	if (sshpam_handle == NULL || (use_privsep && !mm_is_monitor()))
		return;
	debug("PAM: cleanup");
	pam_set_item(sshpam_handle, PAM_CONV, (const void *)&null_conv);
	if (sshpam_session_open) {
		debug("PAM: closing session");
		pam_close_session(sshpam_handle, PAM_SILENT);
		sshpam_session_open = 0;
	}
	if (sshpam_cred_established) {
		debug("PAM: deleting credentials");
		pam_setcred(sshpam_handle, PAM_DELETE_CRED);
		sshpam_cred_established = 0;
	}
	sshpam_authenticated = 0;
	pam_end(sshpam_handle, sshpam_err);
	sshpam_handle = NULL;
}