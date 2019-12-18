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
 scalar_t__ is_dir_sep (char const) ; 
 scalar_t__ only_spaces_and_periods (char const*,size_t,int) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 

int is_ntfs_dotgit(const char *name)
{
	size_t len;

	for (len = 0; ; len++)
		if (!name[len] || name[len] == '\\' || is_dir_sep(name[len])) {
			if (only_spaces_and_periods(name, len, 4) &&
					!strncasecmp(name, ".git", 4))
				return 1;
			if (only_spaces_and_periods(name, len, 5) &&
					!strncasecmp(name, "git~1", 5))
				return 1;
			if (name[len] != '\\')
				return 0;
			name += len + 1;
			len = -1;
		}
}