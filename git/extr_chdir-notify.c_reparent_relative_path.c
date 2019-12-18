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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_absolute_path (char const*) ; 
 char const* remove_leading_path (char*,char const*) ; 
 char* xstrdup (char const*) ; 
 char* xstrfmt (char*,char const*,char const*) ; 

char *reparent_relative_path(const char *old_cwd,
			     const char *new_cwd,
			     const char *path)
{
	char *ret, *full;

	if (is_absolute_path(path))
		return xstrdup(path);

	full = xstrfmt("%s/%s", old_cwd, path);
	ret = xstrdup(remove_leading_path(full, new_cwd));
	free(full);

	return ret;
}