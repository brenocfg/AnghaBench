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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmp_icase (char const,char const) ; 
 scalar_t__ is_dir_sep (char const) ; 

int dir_inside_of(const char *subdir, const char *dir)
{
	int offset = 0;

	assert(dir && subdir && *dir && *subdir);

	while (*dir && *subdir && !cmp_icase(*dir, *subdir)) {
		dir++;
		subdir++;
		offset++;
	}

	/* hel[p]/me vs hel[l]/yeah */
	if (*dir && *subdir)
		return -1;

	if (!*subdir)
		return !*dir ? offset : -1; /* same dir */

	/* foo/[b]ar vs foo/[] */
	if (is_dir_sep(dir[-1]))
		return is_dir_sep(subdir[-1]) ? offset : -1;

	/* foo[/]bar vs foo[] */
	return is_dir_sep(*subdir) ? offset + 1 : -1;
}