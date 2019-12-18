#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  modname ;
struct TYPE_6__ {int ndeps; scalar_t__ fbt_nentries; TYPE_1__** deps; int /*<<< orphan*/  filename; } ;
typedef  TYPE_2__ modctl_t ;
struct TYPE_5__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  fbt_provide_module_function ; 
 int /*<<< orphan*/  linker_file_function_listall (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
fbt_provide_module(void *arg, modctl_t *lf)
{
	char modname[MAXPATHLEN];
	int i;
	size_t len;

	strlcpy(modname, lf->filename, sizeof(modname));
	len = strlen(modname);
	if (len > 3 && strcmp(modname + len - 3, ".ko") == 0)
		modname[len - 3] = '\0';

	/*
	 * Employees of dtrace and their families are ineligible.  Void
	 * where prohibited.
	 */
	if (strcmp(modname, "dtrace") == 0)
		return;

	/*
	 * To register with DTrace, a module must list 'dtrace' as a
	 * dependency in order for the kernel linker to resolve
	 * symbols like dtrace_register(). All modules with such a
	 * dependency are ineligible for FBT tracing.
	 */
	for (i = 0; i < lf->ndeps; i++)
		if (strncmp(lf->deps[i]->filename, "dtrace", 6) == 0)
			return;

	if (lf->fbt_nentries) {
		/*
		 * This module has some FBT entries allocated; we're afraid
		 * to screw with it.
		 */
		return;
	}

	/*
	 * List the functions in the module and the symbol values.
	 */
	(void) linker_file_function_listall(lf, fbt_provide_module_function, modname);
}