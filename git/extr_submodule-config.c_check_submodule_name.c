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

int check_submodule_name(const char *name)
{
	/* Disallow empty names */
	if (!*name)
		return -1;

	/*
	 * Look for '..' as a path component. Check both '/' and '\\' as
	 * separators rather than is_dir_sep(), because we want the name rules
	 * to be consistent across platforms.
	 */
	goto in_component; /* always start inside component */
	while (*name) {
		char c = *name++;
		if (c == '/' || c == '\\') {
in_component:
			if (name[0] == '.' && name[1] == '.' &&
			    (!name[2] || name[2] == '/' || name[2] == '\\'))
				return -1;
		}
	}

	return 0;
}