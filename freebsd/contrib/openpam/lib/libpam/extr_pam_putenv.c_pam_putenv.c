#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char** env; size_t env_count; size_t env_size; } ;
typedef  TYPE_1__ pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  PAM_BUF_ERR ; 
 int /*<<< orphan*/  PAM_SUCCESS ; 
 int /*<<< orphan*/  PAM_SYSTEM_ERR ; 
 int /*<<< orphan*/  RETURNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int openpam_findenv (TYPE_1__*,char const*,int) ; 
 char** realloc (char**,int) ; 
 char* strchr (char const*,char) ; 
 void* strdup (char const*) ; 

int
pam_putenv(pam_handle_t *pamh,
	const char *namevalue)
{
	char **env, *p;
	size_t env_size;
	int i;

	ENTER();

	/* sanity checks */
	if ((p = strchr(namevalue, '=')) == NULL) {
		errno = EINVAL;
		RETURNC(PAM_SYSTEM_ERR);
	}

	/* see if the variable is already in the environment */
	if ((i = openpam_findenv(pamh, namevalue, p - namevalue)) >= 0) {
		if ((p = strdup(namevalue)) == NULL)
			RETURNC(PAM_BUF_ERR);
		FREE(pamh->env[i]);
		pamh->env[i] = p;
		RETURNC(PAM_SUCCESS);
	}

	/* grow the environment list if necessary */
	if (pamh->env_count == pamh->env_size) {
		env_size = pamh->env_size * 2 + 1;
		env = realloc(pamh->env, sizeof(char *) * env_size);
		if (env == NULL)
			RETURNC(PAM_BUF_ERR);
		pamh->env = env;
		pamh->env_size = env_size;
	}

	/* add the variable at the end */
	if ((pamh->env[pamh->env_count] = strdup(namevalue)) == NULL)
		RETURNC(PAM_BUF_ERR);
	++pamh->env_count;
	RETURNC(PAM_SUCCESS);
}