#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* sym; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_ALLNOCONFIG_Y ; 
#define  T_OPT_ALLNOCONFIG_Y 131 
#define  T_OPT_DEFCONFIG_LIST 130 
#define  T_OPT_ENV 129 
#define  T_OPT_MODULES 128 
 TYPE_3__* current_entry ; 
 TYPE_1__* modules_sym ; 
 int /*<<< orphan*/  prop_add_env (char*) ; 
 TYPE_1__* sym_defconfig_list ; 
 int /*<<< orphan*/  zconf_error (char*,...) ; 

void menu_add_option(int token, char *arg)
{
	switch (token) {
	case T_OPT_MODULES:
		if (modules_sym)
			zconf_error("symbol '%s' redefines option 'modules'"
				    " already defined by symbol '%s'",
				    current_entry->sym->name,
				    modules_sym->name
				    );
		modules_sym = current_entry->sym;
		break;
	case T_OPT_DEFCONFIG_LIST:
		if (!sym_defconfig_list)
			sym_defconfig_list = current_entry->sym;
		else if (sym_defconfig_list != current_entry->sym)
			zconf_error("trying to redefine defconfig symbol");
		break;
	case T_OPT_ENV:
		prop_add_env(arg);
		break;
	case T_OPT_ALLNOCONFIG_Y:
		current_entry->sym->flags |= SYMBOL_ALLNOCONFIG_Y;
		break;
	}
}