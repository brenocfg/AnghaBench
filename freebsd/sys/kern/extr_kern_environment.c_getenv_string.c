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
 char* _getenv_dynamic (char const*,int /*<<< orphan*/ *) ; 
 char* _getenv_static (char const*) ; 
 scalar_t__ dynamic_kenv ; 
 int /*<<< orphan*/  kenv_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

int
getenv_string(const char *name, char *data, int size)
{
	char *cp;

	if (dynamic_kenv) {
		mtx_lock(&kenv_lock);
		cp = _getenv_dynamic(name, NULL);
		if (cp != NULL)
			strlcpy(data, cp, size);
		mtx_unlock(&kenv_lock);
	} else {
		cp = _getenv_static(name);
		if (cp != NULL)
			strlcpy(data, cp, size);
	}
	return (cp != NULL);
}