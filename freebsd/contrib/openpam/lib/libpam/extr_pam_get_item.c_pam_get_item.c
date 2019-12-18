#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void** item; } ;
typedef  TYPE_1__ pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTERI (int) ; 
#define  PAM_AUTHTOK 140 
#define  PAM_AUTHTOK_PROMPT 139 
 int /*<<< orphan*/  PAM_BAD_ITEM ; 
#define  PAM_CONV 138 
#define  PAM_HOST 137 
#define  PAM_OLDAUTHTOK 136 
#define  PAM_OLDAUTHTOK_PROMPT 135 
#define  PAM_REPOSITORY 134 
#define  PAM_RHOST 133 
#define  PAM_RUSER 132 
#define  PAM_SERVICE 131 
 int /*<<< orphan*/  PAM_SUCCESS ; 
#define  PAM_TTY 130 
#define  PAM_USER 129 
#define  PAM_USER_PROMPT 128 
 int /*<<< orphan*/  RETURNC (int /*<<< orphan*/ ) ; 

int
pam_get_item(const pam_handle_t *pamh,
	int item_type,
	const void **item)
{

	ENTERI(item_type);
	switch (item_type) {
	case PAM_SERVICE:
	case PAM_USER:
	case PAM_AUTHTOK:
	case PAM_OLDAUTHTOK:
	case PAM_TTY:
	case PAM_RHOST:
	case PAM_RUSER:
	case PAM_CONV:
	case PAM_USER_PROMPT:
	case PAM_REPOSITORY:
	case PAM_AUTHTOK_PROMPT:
	case PAM_OLDAUTHTOK_PROMPT:
	case PAM_HOST:
		*item = pamh->item[item_type];
		RETURNC(PAM_SUCCESS);
	default:
		RETURNC(PAM_BAD_ITEM);
	}
}