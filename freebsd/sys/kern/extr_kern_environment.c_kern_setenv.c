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
 int /*<<< orphan*/  KENV_CHECK ; 
 int KENV_MNAMELEN ; 
 int KENV_MVALLEN ; 
 int KENV_SIZE ; 
 int /*<<< orphan*/  M_KENV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 char* _getenv_dynamic (char const*,int*) ; 
 int /*<<< orphan*/  dynamic_kenv ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kenv_lock ; 
 char** kenvp ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ md_env_len ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int setenv_static (char const*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 int strlen (char const*) ; 

int
kern_setenv(const char *name, const char *value)
{
	char *buf, *cp, *oldenv;
	int namelen, vallen, i;

	if (!dynamic_kenv && md_env_len > 0)
		return (setenv_static(name, value));

	KENV_CHECK;

	namelen = strlen(name) + 1;
	if (namelen > KENV_MNAMELEN + 1)
		return (-1);
	vallen = strlen(value) + 1;
	if (vallen > KENV_MVALLEN + 1)
		return (-1);
	buf = malloc(namelen + vallen, M_KENV, M_WAITOK);
	sprintf(buf, "%s=%s", name, value);

	mtx_lock(&kenv_lock);
	cp = _getenv_dynamic(name, &i);
	if (cp != NULL) {
		oldenv = kenvp[i];
		kenvp[i] = buf;
		mtx_unlock(&kenv_lock);
		free(oldenv, M_KENV);
	} else {
		/* We add the option if it wasn't found */
		for (i = 0; (cp = kenvp[i]) != NULL; i++)
			;

		/* Bounds checking */
		if (i < 0 || i >= KENV_SIZE) {
			free(buf, M_KENV);
			mtx_unlock(&kenv_lock);
			return (-1);
		}

		kenvp[i] = buf;
		kenvp[i + 1] = NULL;
		mtx_unlock(&kenv_lock);
	}
	return (0);
}