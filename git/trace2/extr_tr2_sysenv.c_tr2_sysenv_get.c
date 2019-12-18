#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum tr2_sysenv_variable { ____Placeholder_tr2_sysenv_variable } tr2_sysenv_variable ;
struct TYPE_2__ {int getenv_called; char const* value; int /*<<< orphan*/  env_var_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
 int TR2_SYSENV_MUST_BE_LAST ; 
 int /*<<< orphan*/  free (char const*) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 TYPE_1__* tr2_sysenv_settings ; 
 char const* xstrdup (char const*) ; 

const char *tr2_sysenv_get(enum tr2_sysenv_variable var)
{
	if (var >= TR2_SYSENV_MUST_BE_LAST)
		BUG("tr2_sysenv_get invalid var '%d'", var);

	if (!tr2_sysenv_settings[var].getenv_called) {
		const char *v = getenv(tr2_sysenv_settings[var].env_var_name);
		if (v && *v) {
			free(tr2_sysenv_settings[var].value);
			tr2_sysenv_settings[var].value = xstrdup(v);
		}
		tr2_sysenv_settings[var].getenv_called = 1;
	}

	return tr2_sysenv_settings[var].value;
}