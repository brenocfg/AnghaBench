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
 long INT_MAX ; 
 long INT_MIN ; 
 int /*<<< orphan*/  PAM_LOG_ERROR ; 
 long PAM_NUM_ERRORS ; 
 int PAM_SYSTEM_ERR ; 
 char* openpam_get_option (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  openpam_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * pam_err_name ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static int
pam_return(pam_handle_t *pamh, int flags,
	int argc, const char *argv[])
{
	const char *errname;
	char *e;
	long errcode;

	(void)flags;
	(void)argc;
	(void)argv;
	if ((errname = openpam_get_option(pamh, "error")) == NULL ||
	    errname[0] == '\0') {
		openpam_log(PAM_LOG_ERROR, "missing error parameter");
		return (PAM_SYSTEM_ERR);
	}
	/* is it a number? */
	errcode = strtol(errname, &e, 10);
	if (e != NULL && *e == '\0') {
		/* yep, check range */
		if (errcode >= INT_MIN && errcode <= INT_MAX)
			return (errcode);
	} else {
		/* nope, look it up */
		for (errcode = 0; errcode < PAM_NUM_ERRORS; ++errcode)
			if (strcmp(errname, pam_err_name[errcode]) == 0)
				return (errcode);
	}
	openpam_log(PAM_LOG_ERROR, "invalid error code '%s'", errname);
	return (PAM_SYSTEM_ERR);
}