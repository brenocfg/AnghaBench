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
 scalar_t__ EEXIST ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 scalar_t__ mkdir (char const*,int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

__attribute__((used)) static void
make_dir(const char *path, int mode)
{
	struct stat sb;

	if (lstat(path, &sb) == 0) {
		if (S_ISDIR(sb.st_mode))
			return;
		/*
		 * Normally, we should either ask the user about removing
		 * the non-directory of the same name as a directory we
		 * wish to create, or respect the -n or -o command-line
		 * options.  However, this may lead to a later failure or
		 * even compromise (if this non-directory happens to be a
		 * symlink to somewhere unsafe), so we don't.
		 */

		/*
		 * Don't check unlink() result; failure will cause mkdir()
		 * to fail later, which we will catch.
		 */
		(void)unlink(path);
	}
	if (mkdir(path, mode) != 0 && errno != EEXIST)
		error("mkdir('%s')", path);
}