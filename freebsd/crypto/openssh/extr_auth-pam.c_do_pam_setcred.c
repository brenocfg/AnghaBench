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
 int /*<<< orphan*/  PAM_ESTABLISH_CRED ; 
 int /*<<< orphan*/  PAM_REINITIALIZE_CRED ; 
 scalar_t__ PAM_SUCCESS ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pam_set_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 scalar_t__ pam_setcred (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pam_strerror (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sshpam_authenticated ; 
 int sshpam_cred_established ; 
 scalar_t__ sshpam_err ; 
 int /*<<< orphan*/  sshpam_handle ; 
 int /*<<< orphan*/  store_conv ; 

void
do_pam_setcred(int init)
{
	sshpam_err = pam_set_item(sshpam_handle, PAM_CONV,
	    (const void *)&store_conv);
	if (sshpam_err != PAM_SUCCESS)
		fatal("PAM: failed to set PAM_CONV: %s",
		    pam_strerror(sshpam_handle, sshpam_err));
	if (init) {
		debug("PAM: establishing credentials");
		sshpam_err = pam_setcred(sshpam_handle, PAM_ESTABLISH_CRED);
	} else {
		debug("PAM: reinitializing credentials");
		sshpam_err = pam_setcred(sshpam_handle, PAM_REINITIALIZE_CRED);
	}
	if (sshpam_err == PAM_SUCCESS) {
		sshpam_cred_established = 1;
		return;
	}
	if (sshpam_authenticated)
		fatal("PAM: pam_setcred(): %s",
		    pam_strerror(sshpam_handle, sshpam_err));
	else
		debug("PAM: pam_setcred(): %s",
		    pam_strerror(sshpam_handle, sshpam_err));
}