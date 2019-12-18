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
 int /*<<< orphan*/  M_KENV ; 
 char* _getenv_dynamic (char const*,int*) ; 
 int /*<<< orphan*/  explicit_bzero (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kenv_lock ; 
 char** kenvp ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
kern_unsetenv(const char *name)
{
	char *cp, *oldenv;
	int i, j;

	KENV_CHECK;

	mtx_lock(&kenv_lock);
	cp = _getenv_dynamic(name, &i);
	if (cp != NULL) {
		oldenv = kenvp[i];
		for (j = i + 1; kenvp[j] != NULL; j++)
			kenvp[i++] = kenvp[j];
		kenvp[i] = NULL;
		mtx_unlock(&kenv_lock);
		explicit_bzero(oldenv, strlen(oldenv));
		free(oldenv, M_KENV);
		return (0);
	}
	mtx_unlock(&kenv_lock);
	return (-1);
}