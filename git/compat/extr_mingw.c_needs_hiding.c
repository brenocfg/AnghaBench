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
 scalar_t__ HIDE_DOTFILES_DOTGITONLY ; 
 scalar_t__ HIDE_DOTFILES_FALSE ; 
 scalar_t__ HIDE_DOTFILES_TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ hide_dotfiles ; 
 scalar_t__ is_dir_sep (char const) ; 
 int /*<<< orphan*/  strncasecmp (char*,char const*,int) ; 
 int /*<<< orphan*/  win32_skip_dos_drive_prefix (char**) ; 

__attribute__((used)) static inline int needs_hiding(const char *path)
{
	const char *basename;

	if (hide_dotfiles == HIDE_DOTFILES_FALSE)
		return 0;

	/* We cannot use basename(), as it would remove trailing slashes */
	win32_skip_dos_drive_prefix((char **)&path);
	if (!*path)
		return 0;

	for (basename = path; *path; path++)
		if (is_dir_sep(*path)) {
			do {
				path++;
			} while (is_dir_sep(*path));
			/* ignore trailing slashes */
			if (*path)
				basename = path;
			else
				break;
		}

	if (hide_dotfiles == HIDE_DOTFILES_TRUE)
		return *basename == '.';

	assert(hide_dotfiles == HIDE_DOTFILES_DOTGITONLY);
	return !strncasecmp(".git", basename, 4) &&
		(!basename[4] || is_dir_sep(basename[4]));
}