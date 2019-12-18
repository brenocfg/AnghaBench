#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* current; } ;
typedef  TYPE_1__ pam_handle_t ;
struct TYPE_5__ {int optc; char** optv; } ;
typedef  TYPE_2__ pam_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTERS (char const*) ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  PAM_BUF_ERR ; 
 int /*<<< orphan*/  PAM_SUCCESS ; 
 int /*<<< orphan*/  PAM_SYSTEM_ERR ; 
 int /*<<< orphan*/  RETURNC (int /*<<< orphan*/ ) ; 
 scalar_t__ asprintf (char**,char*,int,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** realloc (char**,int) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 

int
openpam_set_option(pam_handle_t *pamh,
	const char *option,
	const char *value)
{
	pam_chain_t *cur;
	char *opt, **optv;
	size_t len;
	int i;

	ENTERS(option);
	if (pamh == NULL || pamh->current == NULL || option == NULL)
		RETURNC(PAM_SYSTEM_ERR);
	cur = pamh->current;
	for (len = 0; option[len] != '\0'; ++len)
		if (option[len] == '=')
			break;
	for (i = 0; i < cur->optc; ++i) {
		if (strncmp(cur->optv[i], option, len) == 0 &&
		    (cur->optv[i][len] == '\0' || cur->optv[i][len] == '='))
			break;
	}
	if (value == NULL) {
		/* remove */
		if (i == cur->optc)
			RETURNC(PAM_SUCCESS);
		for (free(cur->optv[i]); i < cur->optc; ++i)
			cur->optv[i] = cur->optv[i + 1];
		cur->optv[i] = NULL;
		RETURNC(PAM_SUCCESS);
	}
	if (asprintf(&opt, "%.*s=%s", (int)len, option, value) < 0)
		RETURNC(PAM_BUF_ERR);
	if (i == cur->optc) {
		/* add */
		optv = realloc(cur->optv, sizeof(char *) * (cur->optc + 2));
		if (optv == NULL) {
			FREE(opt);
			RETURNC(PAM_BUF_ERR);
		}
		optv[i] = opt;
		optv[i + 1] = NULL;
		cur->optv = optv;
		++cur->optc;
	} else {
		/* replace */
		FREE(cur->optv[i]);
		cur->optv[i] = opt;
	}
	RETURNC(PAM_SUCCESS);
}