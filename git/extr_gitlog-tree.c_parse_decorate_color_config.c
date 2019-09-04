#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int LOOKUP_CONFIG (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  color_decorate_slots ; 
 int color_parse (char const*,int /*<<< orphan*/ ) ; 
 int config_error_nonbool (char const*) ; 
 int /*<<< orphan*/ * decoration_colors ; 

int parse_decorate_color_config(const char *var, const char *slot_name, const char *value)
{
	int slot = LOOKUP_CONFIG(color_decorate_slots, slot_name);
	if (slot < 0)
		return 0;
	if (!value)
		return config_error_nonbool(var);
	return color_parse(value, decoration_colors[slot]);
}