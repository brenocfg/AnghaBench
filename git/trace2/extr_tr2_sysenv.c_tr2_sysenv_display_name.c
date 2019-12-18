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
struct TYPE_2__ {char const* env_var_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
 int TR2_SYSENV_MUST_BE_LAST ; 
 TYPE_1__* tr2_sysenv_settings ; 

const char *tr2_sysenv_display_name(enum tr2_sysenv_variable var)
{
	if (var >= TR2_SYSENV_MUST_BE_LAST)
		BUG("tr2_sysenv_get invalid var '%d'", var);

	return tr2_sysenv_settings[var].env_var_name;
}