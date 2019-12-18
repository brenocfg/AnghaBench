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
typedef  size_t pkg_config_key ;
struct TYPE_2__ {scalar_t__ type; char* value; char* val; } ;

/* Variables and functions */
 scalar_t__ PKG_CONFIG_BOOL ; 
 scalar_t__ boolstr_to_bool (char const*) ; 
 TYPE_1__* c ; 

int
config_bool(pkg_config_key k, bool *val)
{
	const char *value;

	if (c[k].type != PKG_CONFIG_BOOL)
		return (-1);

	*val = false;

	if (c[k].value != NULL)
		value = c[k].value;
	else
		value = c[k].val;

	if (boolstr_to_bool(value))
		*val = true;

	return (0);
}