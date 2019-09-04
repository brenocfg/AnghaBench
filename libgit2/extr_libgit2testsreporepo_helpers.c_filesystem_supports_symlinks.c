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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ p_lstat (char const*,struct stat*) ; 
 scalar_t__ p_symlink (char*,char const*) ; 
 int /*<<< orphan*/  p_unlink (char const*) ; 

int filesystem_supports_symlinks(const char *path)
{
	struct stat st;
	bool support = 0;

	if (p_symlink("target", path) == 0) {
		if (p_lstat(path, &st) == 0 && S_ISLNK(st.st_mode))
			support = 1;

		p_unlink(path);
	}

	return support;
}