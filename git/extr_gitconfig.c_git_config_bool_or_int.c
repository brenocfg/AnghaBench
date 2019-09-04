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
 int git_config_int (char const*,char const*) ; 
 int git_parse_maybe_bool_text (char const*) ; 

int git_config_bool_or_int(const char *name, const char *value, int *is_bool)
{
	int v = git_parse_maybe_bool_text(value);
	if (0 <= v) {
		*is_bool = 1;
		return v;
	}
	*is_bool = 0;
	return git_config_int(name, value);
}