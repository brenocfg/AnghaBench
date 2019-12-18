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
 scalar_t__ PKG_CONFIG_STRING ; 
 TYPE_1__* c ; 

int
config_string(pkg_config_key k, const char **val)
{
	if (c[k].type != PKG_CONFIG_STRING)
		return (-1);

	if (c[k].value != NULL)
		*val = c[k].value;
	else
		*val = c[k].val;

	return (0);
}