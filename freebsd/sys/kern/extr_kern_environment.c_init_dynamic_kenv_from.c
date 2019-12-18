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
 int KENV_MNAMELEN ; 
 int KENV_MVALLEN ; 
 int KENV_SIZE ; 
 int /*<<< orphan*/  M_KENV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 char* _getenv_dynamic_locked (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  explicit_bzero (char*,size_t) ; 
 int /*<<< orphan*/ * kenvp ; 
 char* kernenv_next (char*) ; 
 int /*<<< orphan*/  malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
init_dynamic_kenv_from(char *init_env, int *curpos)
{
	char *cp, *cpnext, *eqpos, *found;
	size_t len;
	int i;

	if (init_env && *init_env != '\0') {
		found = NULL;
		i = *curpos;
		for (cp = init_env; cp != NULL; cp = cpnext) {
			cpnext = kernenv_next(cp);
			len = strlen(cp) + 1;
			if (len > KENV_MNAMELEN + 1 + KENV_MVALLEN + 1) {
				printf(
				"WARNING: too long kenv string, ignoring %s\n",
				    cp);
				goto sanitize;
			}
			eqpos = strchr(cp, '=');
			if (eqpos == NULL) {
				printf(
				"WARNING: malformed static env value, ignoring %s\n",
				    cp);
				goto sanitize;
			}
			*eqpos = 0;
			/*
			 * De-dupe the environment as we go.  We don't add the
			 * duplicated assignments because config(8) will flip
			 * the order of the static environment around to make
			 * kernel processing match the order of specification
			 * in the kernel config.
			 */
			found = _getenv_dynamic_locked(cp, NULL);
			*eqpos = '=';
			if (found != NULL)
				goto sanitize;
			if (i > KENV_SIZE) {
				printf(
				"WARNING: too many kenv strings, ignoring %s\n",
				    cp);
				goto sanitize;
			}

			kenvp[i] = malloc(len, M_KENV, M_WAITOK);
			strcpy(kenvp[i++], cp);
sanitize:
			explicit_bzero(cp, len - 1);
		}
		*curpos = i;
	}
}