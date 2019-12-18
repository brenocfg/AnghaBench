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
 int /*<<< orphan*/  PAM_CHANGE_EXPIRED_AUTHTOK ; 
 int /*<<< orphan*/  PAM_CONV ; 
 scalar_t__ PAM_SUCCESS ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 scalar_t__ pam_chauthtok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pam_set_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  pam_strerror (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sshpam_err ; 
 int /*<<< orphan*/  sshpam_handle ; 
 int /*<<< orphan*/  tty_conv ; 
 scalar_t__ use_privsep ; 

void
do_pam_chauthtok(void)
{
	if (use_privsep)
		fatal("Password expired (unable to change with privsep)");
	sshpam_err = pam_set_item(sshpam_handle, PAM_CONV,
	    (const void *)&tty_conv);
	if (sshpam_err != PAM_SUCCESS)
		fatal("PAM: failed to set PAM_CONV: %s",
		    pam_strerror(sshpam_handle, sshpam_err));
	debug("PAM: changing password");
	sshpam_err = pam_chauthtok(sshpam_handle, PAM_CHANGE_EXPIRED_AUTHTOK);
	if (sshpam_err != PAM_SUCCESS)
		fatal("PAM: pam_chauthtok(): %s",
		    pam_strerror(sshpam_handle, sshpam_err));
}