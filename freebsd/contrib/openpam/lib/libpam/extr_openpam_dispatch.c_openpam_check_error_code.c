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
 int PAM_ABORT ; 
 int PAM_ACCT_EXPIRED ; 
 int PAM_AUTHINFO_UNAVAIL ; 
 int PAM_AUTHTOK_DISABLE_AGING ; 
 int PAM_AUTHTOK_ERR ; 
 int PAM_AUTHTOK_LOCK_BUSY ; 
 int PAM_AUTHTOK_RECOVERY_ERR ; 
 int PAM_AUTH_ERR ; 
 int PAM_BUF_ERR ; 
 int PAM_CONV_ERR ; 
 int PAM_CRED_ERR ; 
 int PAM_CRED_EXPIRED ; 
 int PAM_CRED_INSUFFICIENT ; 
 int PAM_CRED_UNAVAIL ; 
 int /*<<< orphan*/  PAM_LOG_ERROR ; 
 int PAM_MAXTRIES ; 
 int PAM_NEW_AUTHTOK_REQD ; 
 int PAM_PERM_DENIED ; 
 int PAM_SERVICE_ERR ; 
 int PAM_SESSION_ERR ; 
#define  PAM_SM_ACCT_MGMT 133 
#define  PAM_SM_AUTHENTICATE 132 
#define  PAM_SM_CHAUTHTOK 131 
#define  PAM_SM_CLOSE_SESSION 130 
#define  PAM_SM_OPEN_SESSION 129 
#define  PAM_SM_SETCRED 128 
 int PAM_SUCCESS ; 
 int PAM_SYSTEM_ERR ; 
 int PAM_TRY_AGAIN ; 
 int PAM_USER_UNKNOWN ; 
 int /*<<< orphan*/  openpam_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pam_sm_func_name ; 

__attribute__((used)) static void
openpam_check_error_code(int primitive, int r)
{
	/* common error codes */
	if (r == PAM_SUCCESS ||
	    r == PAM_SYSTEM_ERR ||
	    r == PAM_SERVICE_ERR ||
	    r == PAM_BUF_ERR ||
	    r == PAM_CONV_ERR ||
	    r == PAM_PERM_DENIED ||
	    r == PAM_ABORT)
		return;

	/* specific error codes */
	switch (primitive) {
	case PAM_SM_AUTHENTICATE:
		if (r == PAM_AUTH_ERR ||
		    r == PAM_CRED_INSUFFICIENT ||
		    r == PAM_AUTHINFO_UNAVAIL ||
		    r == PAM_USER_UNKNOWN ||
		    r == PAM_MAXTRIES)
			return;
		break;
	case PAM_SM_SETCRED:
		if (r == PAM_CRED_UNAVAIL ||
		    r == PAM_CRED_EXPIRED ||
		    r == PAM_USER_UNKNOWN ||
		    r == PAM_CRED_ERR)
			return;
		break;
	case PAM_SM_ACCT_MGMT:
		if (r == PAM_USER_UNKNOWN ||
		    r == PAM_AUTH_ERR ||
		    r == PAM_NEW_AUTHTOK_REQD ||
		    r == PAM_ACCT_EXPIRED)
			return;
		break;
	case PAM_SM_OPEN_SESSION:
	case PAM_SM_CLOSE_SESSION:
		if (r == PAM_SESSION_ERR)
			return;
		break;
	case PAM_SM_CHAUTHTOK:
		if (r == PAM_PERM_DENIED ||
		    r == PAM_AUTHTOK_ERR ||
		    r == PAM_AUTHTOK_RECOVERY_ERR ||
		    r == PAM_AUTHTOK_LOCK_BUSY ||
		    r == PAM_AUTHTOK_DISABLE_AGING ||
		    r == PAM_TRY_AGAIN)
			return;
		break;
	}

	openpam_log(PAM_LOG_ERROR, "%s(): unexpected return value %d",
	    pam_sm_func_name[primitive], r);
}