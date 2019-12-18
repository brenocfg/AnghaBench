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
#define  PAM_AUTHTOK 138 
#define  PAM_AUTHTOK_PROMPT 137 
#define  PAM_HOST 136 
#define  PAM_OLDAUTHTOK 135 
#define  PAM_OLDAUTHTOK_PROMPT 134 
#define  PAM_RHOST 133 
#define  PAM_RUSER 132 
#define  PAM_SERVICE 131 
 int PAM_SUCCESS ; 
#define  PAM_TTY 130 
#define  PAM_USER 129 
#define  PAM_USER_PROMPT 128 
 int /*<<< orphan*/ * pam_item_name ; 
 int pam_set_item (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  pamh ; 
 int /*<<< orphan*/  pt_error (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_verbose (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
pt_set_item(int item, const char *p)
{
	int pame;

	switch (item) {
	case PAM_SERVICE:
	case PAM_USER:
	case PAM_AUTHTOK:
	case PAM_OLDAUTHTOK:
	case PAM_TTY:
	case PAM_RHOST:
	case PAM_RUSER:
	case PAM_USER_PROMPT:
	case PAM_AUTHTOK_PROMPT:
	case PAM_OLDAUTHTOK_PROMPT:
	case PAM_HOST:
		pt_verbose("setting %s to %s", pam_item_name[item], p);
		break;
	default:
		pt_verbose("setting %s", pam_item_name[item]);
		break;
	}
	if ((pame = pam_set_item(pamh, item, p)) != PAM_SUCCESS)
		pt_error(pame, "pam_set_item(%s)", pam_item_name[item]);
	return (pame);
}