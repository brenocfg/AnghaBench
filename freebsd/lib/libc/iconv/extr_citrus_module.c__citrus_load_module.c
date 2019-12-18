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
typedef  int /*<<< orphan*/  path ;
typedef  scalar_t__ _citrus_module_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int I18NMODULE_MAJOR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  RTLD_LAZY ; 
 int /*<<< orphan*/ * _PATH_I18NMODULE ; 
 char* _findshlib (char*,int*,int*) ; 
 int /*<<< orphan*/ * _pathI18nModule ; 
 char* dlerror () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  issetugid () ; 
 void* libc_dlopen (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
_citrus_load_module(_citrus_module_t *rhandle, const char *encname)
{
	const char *p;
	char path[PATH_MAX];
	void *handle;
	int maj, min;

	if (_pathI18nModule == NULL) {
		p = getenv("PATH_I18NMODULE");
		if (p != NULL && !issetugid()) {
			_pathI18nModule = strdup(p);
			if (_pathI18nModule == NULL)
				return (ENOMEM);
		} else
			_pathI18nModule = _PATH_I18NMODULE;
	}

	(void)snprintf(path, sizeof(path), "lib%s", encname);
	maj = I18NMODULE_MAJOR;
	min = -1;
	p = _findshlib(path, &maj, &min);
	if (!p)
		return (EINVAL);
	handle = libc_dlopen(p, RTLD_LAZY);
	if (!handle) {
		printf("%s", dlerror());
		return (EINVAL);
	}

	*rhandle = (_citrus_module_t)handle;

	return (0);
}