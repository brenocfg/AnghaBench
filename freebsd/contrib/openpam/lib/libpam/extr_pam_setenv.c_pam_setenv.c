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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int PAM_BUF_ERR ; 
 int PAM_SUCCESS ; 
 int PAM_SYSTEM_ERR ; 
 int /*<<< orphan*/  RETURNC (int) ; 
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ openpam_findenv (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int pam_putenv (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
pam_setenv(pam_handle_t *pamh,
	const char *name,
	const char *value,
	int overwrite)
{
	char *env;
	int r;

	ENTER();

	/* sanity checks */
	if (*name == '\0' || strchr(name, '=') != NULL) {
		errno = EINVAL;
		RETURNC(PAM_SYSTEM_ERR);
	}

	/* is it already there? */
	if (!overwrite && openpam_findenv(pamh, name, strlen(name)) >= 0)
		RETURNC(PAM_SUCCESS);

	/* set it... */
	if (asprintf(&env, "%s=%s", name, value) < 0)
		RETURNC(PAM_BUF_ERR);
	r = pam_putenv(pamh, env);
	FREE(env);
	RETURNC(r);
}