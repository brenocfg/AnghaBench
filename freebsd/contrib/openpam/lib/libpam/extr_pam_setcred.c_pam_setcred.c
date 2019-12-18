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
 int PAM_BAD_CONSTANT ; 
 int PAM_DELETE_CRED ; 
 int PAM_ESTABLISH_CRED ; 
 int PAM_REFRESH_CRED ; 
 int PAM_REINITIALIZE_CRED ; 
 int PAM_SILENT ; 
 int /*<<< orphan*/  PAM_SM_SETCRED ; 
 int /*<<< orphan*/  RETURNC (int) ; 
 int openpam_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
pam_setcred(pam_handle_t *pamh,
	int flags)
{
	int r;

	ENTER();
	if (flags & ~(PAM_SILENT|PAM_ESTABLISH_CRED|PAM_DELETE_CRED|
		PAM_REINITIALIZE_CRED|PAM_REFRESH_CRED))
		RETURNC(PAM_BAD_CONSTANT);
	/* XXX enforce exclusivity */
	r = openpam_dispatch(pamh, PAM_SM_SETCRED, flags);
	RETURNC(r);
}