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
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  PAM_AUTHTOK ; 
 int PAM_BAD_CONSTANT ; 
 int PAM_CHANGE_EXPIRED_AUTHTOK ; 
 int /*<<< orphan*/  PAM_OLDAUTHTOK ; 
 int PAM_PRELIM_CHECK ; 
 int PAM_SILENT ; 
 int /*<<< orphan*/  PAM_SM_CHAUTHTOK ; 
 int PAM_SUCCESS ; 
 int PAM_UPDATE_AUTHTOK ; 
 int /*<<< orphan*/  RETURNC (int) ; 
 int openpam_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pam_set_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
pam_chauthtok(pam_handle_t *pamh,
	int flags)
{
	int r;

	ENTER();
	if (flags & ~(PAM_SILENT|PAM_CHANGE_EXPIRED_AUTHTOK))
		RETURNC(PAM_BAD_CONSTANT);
	r = openpam_dispatch(pamh, PAM_SM_CHAUTHTOK,
	    flags | PAM_PRELIM_CHECK);
	if (r == PAM_SUCCESS)
		r = openpam_dispatch(pamh, PAM_SM_CHAUTHTOK,
		    flags | PAM_UPDATE_AUTHTOK);
	pam_set_item(pamh, PAM_OLDAUTHTOK, NULL);
	pam_set_item(pamh, PAM_AUTHTOK, NULL);
	RETURNC(r);
}