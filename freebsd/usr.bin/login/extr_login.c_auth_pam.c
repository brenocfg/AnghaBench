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
#define  PAM_AUTH_ERR 132 
 int PAM_CHANGE_EXPIRED_AUTHTOK ; 
#define  PAM_MAXTRIES 131 
#define  PAM_NEW_AUTHTOK_REQD 130 
#define  PAM_SUCCESS 129 
 int /*<<< orphan*/  PAM_USER ; 
#define  PAM_USER_UNKNOWN 128 
 int /*<<< orphan*/  getpwnam (char const*) ; 
 int pam_acct_mgmt (int /*<<< orphan*/ *,int) ; 
 int pam_authenticate (int /*<<< orphan*/ *,int) ; 
 int pam_chauthtok (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pam_end (int /*<<< orphan*/ *,int) ; 
 int pam_err ; 
 int pam_get_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const**) ; 
 int pam_silent ; 
 int /*<<< orphan*/  pam_syslog (char*) ; 
 int /*<<< orphan*/ * pamh ; 
 int /*<<< orphan*/  pwd ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  username ; 

__attribute__((used)) static int
auth_pam(void)
{
	const char *tmpl_user;
	const void *item;
	int rval;

	pam_err = pam_authenticate(pamh, pam_silent);
	switch (pam_err) {

	case PAM_SUCCESS:
		/*
		 * With PAM we support the concept of a "template"
		 * user.  The user enters a login name which is
		 * authenticated by PAM, usually via a remote service
		 * such as RADIUS or TACACS+.  If authentication
		 * succeeds, a different but related "template" name
		 * is used for setting the credentials, shell, and
		 * home directory.  The name the user enters need only
		 * exist on the remote authentication server, but the
		 * template name must be present in the local password
		 * database.
		 *
		 * This is supported by two various mechanisms in the
		 * individual modules.  However, from the application's
		 * point of view, the template user is always passed
		 * back as a changed value of the PAM_USER item.
		 */
		pam_err = pam_get_item(pamh, PAM_USER, &item);
		if (pam_err == PAM_SUCCESS) {
			tmpl_user = (const char *)item;
			if (strcmp(username, tmpl_user) != 0)
				pwd = getpwnam(tmpl_user);
		} else {
			pam_syslog("pam_get_item(PAM_USER)");
		}
		rval = 0;
		break;

	case PAM_AUTH_ERR:
	case PAM_USER_UNKNOWN:
	case PAM_MAXTRIES:
		rval = 1;
		break;

	default:
		pam_syslog("pam_authenticate()");
		rval = -1;
		break;
	}

	if (rval == 0) {
		pam_err = pam_acct_mgmt(pamh, pam_silent);
		switch (pam_err) {
		case PAM_SUCCESS:
			break;
		case PAM_NEW_AUTHTOK_REQD:
			pam_err = pam_chauthtok(pamh,
			    pam_silent|PAM_CHANGE_EXPIRED_AUTHTOK);
			if (pam_err != PAM_SUCCESS) {
				pam_syslog("pam_chauthtok()");
				rval = 1;
			}
			break;
		default:
			pam_syslog("pam_acct_mgmt()");
			rval = 1;
			break;
		}
	}

	if (rval != 0) {
		pam_end(pamh, pam_err);
		pamh = NULL;
	}
	return (rval);
}