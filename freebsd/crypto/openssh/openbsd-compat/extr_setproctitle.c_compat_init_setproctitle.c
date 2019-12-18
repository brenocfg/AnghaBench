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
 int argv_env_len ; 
 char* argv_start ; 
 char** calloc (int,int) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

void
compat_init_setproctitle(int argc, char *argv[])
{
#if !defined(HAVE_SETPROCTITLE) && \
    defined(SPT_TYPE) && SPT_TYPE == SPT_REUSEARGV
	extern char **environ;
	char *lastargv = NULL;
	char **envp = environ;
	int i;

	/*
	 * NB: This assumes that argv has already been copied out of the
	 * way. This is true for sshd, but may not be true for other
	 * programs. Beware.
	 */

	if (argc == 0 || argv[0] == NULL)
		return;

	/* Fail if we can't allocate room for the new environment */
	for (i = 0; envp[i] != NULL; i++)
		;
	if ((environ = calloc(i + 1, sizeof(*environ))) == NULL) {
		environ = envp;	/* put it back */
		return;
	}

	/*
	 * Find the last argv string or environment variable within
	 * our process memory area.
	 */
	for (i = 0; i < argc; i++) {
		if (lastargv == NULL || lastargv + 1 == argv[i])
			lastargv = argv[i] + strlen(argv[i]);
	}
	for (i = 0; envp[i] != NULL; i++) {
		if (lastargv + 1 == envp[i])
			lastargv = envp[i] + strlen(envp[i]);
	}

	argv[1] = NULL;
	argv_start = argv[0];
	argv_env_len = lastargv - argv[0] - 1;

	/*
	 * Copy environment
	 * XXX - will truncate env on strdup fail
	 */
	for (i = 0; envp[i] != NULL; i++)
		environ[i] = strdup(envp[i]);
	environ[i] = NULL;
#endif /* SPT_REUSEARGV */
}