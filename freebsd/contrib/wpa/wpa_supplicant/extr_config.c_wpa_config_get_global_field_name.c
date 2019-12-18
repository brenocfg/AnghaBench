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
struct TYPE_2__ {char const* name; int /*<<< orphan*/  param1; } ;

/* Variables and functions */
 unsigned int NUM_GLOBAL_FIELDS ; 
 TYPE_1__* global_fields ; 

const char * wpa_config_get_global_field_name(unsigned int i, int *no_var)
{
	if (i >= NUM_GLOBAL_FIELDS)
		return NULL;

	if (no_var)
		*no_var = !global_fields[i].param1;
	return global_fields[i].name;
}