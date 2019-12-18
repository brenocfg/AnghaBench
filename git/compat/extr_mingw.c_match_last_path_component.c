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
 scalar_t__ fspathncmp (char const*,char const*,size_t) ; 
 scalar_t__ is_dir_sep (char const) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static inline int match_last_path_component(const char *path, size_t *len,
					    const char *component)
{
	size_t component_len = strlen(component);
	if (*len < component_len + 1 ||
	    !is_dir_sep(path[*len - component_len - 1]) ||
	    fspathncmp(path + *len - component_len, component, component_len))
		return 0;
	*len -= component_len + 1;
	/* chomp off repeated dir separators */
	while (*len > 0 && is_dir_sep(path[*len - 1]))
		(*len)--;
	return 1;
}