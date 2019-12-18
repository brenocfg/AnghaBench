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
struct pam_repository {int dummy; } ;
struct pam_conv {int dummy; } ;
struct TYPE_3__ {void** item; } ;
typedef  TYPE_1__ pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTERI (int) ; 
 int /*<<< orphan*/  FREE (void*) ; 
#define  PAM_AUTHTOK 140 
#define  PAM_AUTHTOK_PROMPT 139 
 int /*<<< orphan*/  PAM_BAD_ITEM ; 
 int /*<<< orphan*/  PAM_BUF_ERR ; 
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
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 int /*<<< orphan*/  strlen (void const*) ; 

int
pam_set_item(pam_handle_t *pamh,
	int item_type,
	const void *item)
{
	void **slot;
	size_t nsize, osize;

	ENTERI(item_type);
	slot = &pamh->item[item_type];
	osize = nsize = 0;
	switch (item_type) {
	case PAM_SERVICE:
		/* set once only, by pam_start() */
		if (*slot != NULL && item != NULL)
			RETURNC(PAM_BAD_ITEM);
		/* fall through */
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
		if (*slot != NULL)
			osize = strlen(*slot) + 1;
		if (item != NULL)
			nsize = strlen(item) + 1;
		break;
	case PAM_REPOSITORY:
		osize = nsize = sizeof(struct pam_repository);
		break;
	case PAM_CONV:
		osize = nsize = sizeof(struct pam_conv);
		break;
	default:
		RETURNC(PAM_BAD_ITEM);
	}
	if (*slot != NULL) {
		memset(*slot, 0xd0, osize);
		FREE(*slot);
	}
	if (item != NULL) {
		if ((*slot = malloc(nsize)) == NULL)
			RETURNC(PAM_BUF_ERR);
		memcpy(*slot, item, nsize);
	} else {
		*slot = NULL;
	}
	RETURNC(PAM_SUCCESS);
}