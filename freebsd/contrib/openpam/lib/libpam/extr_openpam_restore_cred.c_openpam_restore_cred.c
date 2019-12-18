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
struct pam_saved_cred {scalar_t__ euid; int /*<<< orphan*/  egid; int /*<<< orphan*/  groups; int /*<<< orphan*/  ngroups; } ;
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  PAM_SAVED_CRED ; 
 int PAM_SUCCESS ; 
 int PAM_SYSTEM_ERR ; 
 int /*<<< orphan*/  RETURNC (int) ; 
 scalar_t__ geteuid () ; 
 int pam_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const**) ; 
 int /*<<< orphan*/  pam_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ setegid (int /*<<< orphan*/ ) ; 
 scalar_t__ seteuid (scalar_t__) ; 
 scalar_t__ setgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
openpam_restore_cred(pam_handle_t *pamh)
{
	const struct pam_saved_cred *scred;
	const void *scredp;
	int r;

	ENTER();
	r = pam_get_data(pamh, PAM_SAVED_CRED, &scredp);
	if (r != PAM_SUCCESS)
		RETURNC(r);
	if (scredp == NULL)
		RETURNC(PAM_SYSTEM_ERR);
	scred = scredp;
	if (scred->euid != geteuid()) {
		if (seteuid(scred->euid) < 0 ||
		    setgroups(scred->ngroups, scred->groups) < 0 ||
		    setegid(scred->egid) < 0)
			RETURNC(PAM_SYSTEM_ERR);
	}
	pam_set_data(pamh, PAM_SAVED_CRED, NULL, NULL);
	RETURNC(PAM_SUCCESS);
}