#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* path; int /*<<< orphan*/ * dlh; int /*<<< orphan*/ ** func; } ;
typedef  TYPE_1__ pam_module_t ;
typedef  int /*<<< orphan*/ * pam_func_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  PAM_LOG_ERROR ; 
 int /*<<< orphan*/  PAM_LOG_LIBDEBUG ; 
 int PAM_NUM_PRIMITIVES ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlerror () ; 
 scalar_t__ dlfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* dlsym (int /*<<< orphan*/ *,char*) ; 
 int errno ; 
 int /*<<< orphan*/  openpam_log (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/ * pam_sm_func_name ; 
 TYPE_1__* strdup (char const*) ; 
 int /*<<< orphan*/ * try_dlopen (char const*) ; 

__attribute__((used)) static pam_module_t *
try_module(const char *modpath)
{
	const pam_module_t *dlmodule;
	pam_module_t *module;
	int i, serrno;

	if ((module = calloc(1, sizeof *module)) == NULL ||
	    (module->path = strdup(modpath)) == NULL ||
	    (module->dlh = try_dlopen(modpath)) == NULL)
		goto err;
	dlmodule = dlsym(module->dlh, "_pam_module");
	for (i = 0; i < PAM_NUM_PRIMITIVES; ++i) {
		if (dlmodule) {
			module->func[i] = dlmodule->func[i];
		} else {
			module->func[i] = (pam_func_t)dlfunc(module->dlh,
			    pam_sm_func_name[i]);
			/*
			 * This openpam_log() call is a major source of
			 * log spam, and the cases that matter are caught
			 * and logged in openpam_dispatch().  This would
			 * be less problematic if dlerror() returned an
			 * error code so we could log an error only when
			 * dlfunc() failed for a reason other than "no
			 * such symbol".
			 */
#if 0
			if (module->func[i] == NULL)
				openpam_log(PAM_LOG_LIBDEBUG, "%s: %s(): %s",
				    modpath, pam_sm_func_name[i], dlerror());
#endif
		}
	}
	return (module);
err:
	serrno = errno;
	if (module != NULL) {
		if (module->dlh != NULL)
			dlclose(module->dlh);
		if (module->path != NULL)
			FREE(module->path);
		FREE(module);
	}
	errno = serrno;
	if (serrno != 0 && serrno != ENOENT)
		openpam_log(PAM_LOG_ERROR, "%s: %m", modpath);
	errno = serrno;
	return (NULL);
}