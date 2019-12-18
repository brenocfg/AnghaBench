#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mod_depend {int dummy; } ;
typedef  TYPE_1__* modlist_t ;
typedef  TYPE_2__* linker_file_t ;
struct TYPE_7__ {int /*<<< orphan*/  refs; } ;
struct TYPE_6__ {TYPE_2__* container; } ;

/* Variables and functions */
 int /*<<< orphan*/  kld_sx ; 
 int linker_load_module (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,struct mod_depend*,TYPE_2__**) ; 
 TYPE_1__* modlist_lookup2 (char const*,struct mod_depend*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
linker_reference_module(const char *modname, struct mod_depend *verinfo,
    linker_file_t *result)
{
	modlist_t mod;
	int error;

	sx_xlock(&kld_sx);
	if ((mod = modlist_lookup2(modname, verinfo)) != NULL) {
		*result = mod->container;
		(*result)->refs++;
		sx_xunlock(&kld_sx);
		return (0);
	}

	error = linker_load_module(NULL, modname, NULL, verinfo, result);
	sx_xunlock(&kld_sx);
	return (error);
}