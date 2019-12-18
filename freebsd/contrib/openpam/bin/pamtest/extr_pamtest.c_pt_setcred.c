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
 int PAM_SUCCESS ; 
 int pam_setcred (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pamh ; 
 int /*<<< orphan*/  pt_error (int,char*) ; 
 int /*<<< orphan*/  pt_verbose (char*) ; 
 int silent ; 

__attribute__((used)) static int
pt_setcred(int flags)
{
	int pame;

	flags |= silent;
	pt_verbose("pam_setcred()");
	if ((pame = pam_setcred(pamh, flags)) != PAM_SUCCESS)
		pt_error(pame, "pam_setcred()");
	return (pame);
}