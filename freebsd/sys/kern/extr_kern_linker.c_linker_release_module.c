#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mod_depend {int dummy; } ;
typedef  TYPE_1__* modlist_t ;
typedef  int /*<<< orphan*/ * linker_file_t ;
struct TYPE_3__ {int /*<<< orphan*/ * container; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LINKER_UNLOAD_NORMAL ; 
 int /*<<< orphan*/  kld_sx ; 
 int linker_file_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* modlist_lookup2 (char const*,struct mod_depend*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
linker_release_module(const char *modname, struct mod_depend *verinfo,
    linker_file_t lf)
{
	modlist_t mod;
	int error;

	sx_xlock(&kld_sx);
	if (lf == NULL) {
		KASSERT(modname != NULL,
		    ("linker_release_module: no file or name"));
		mod = modlist_lookup2(modname, verinfo);
		if (mod == NULL) {
			sx_xunlock(&kld_sx);
			return (ESRCH);
		}
		lf = mod->container;
	} else
		KASSERT(modname == NULL && verinfo == NULL,
		    ("linker_release_module: both file and name"));
	error =	linker_file_unload(lf, LINKER_UNLOAD_NORMAL);
	sx_xunlock(&kld_sx);
	return (error);
}