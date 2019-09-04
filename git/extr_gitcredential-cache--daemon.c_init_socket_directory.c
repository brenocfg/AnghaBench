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
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  die_errno (char*,char*) ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/  permissions_advice ; 
 scalar_t__ safe_create_leading_directories_const (char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void init_socket_directory(const char *path)
{
	struct stat st;
	char *path_copy = xstrdup(path);
	char *dir = dirname(path_copy);

	if (!stat(dir, &st)) {
		if (st.st_mode & 077)
			die(_(permissions_advice), dir);
	} else {
		/*
		 * We must be sure to create the directory with the correct mode,
		 * not just chmod it after the fact; otherwise, there is a race
		 * condition in which somebody can chdir to it, sleep, then try to open
		 * our protected socket.
		 */
		if (safe_create_leading_directories_const(dir) < 0)
			die_errno("unable to create directories for '%s'", dir);
		if (mkdir(dir, 0700) < 0)
			die_errno("unable to mkdir '%s'", dir);
	}

	if (chdir(dir))
		/*
		 * We don't actually care what our cwd is; we chdir here just to
		 * be a friendly daemon and avoid tying up our original cwd.
		 * If this fails, it's OK to just continue without that benefit.
		 */
		;

	free(path_copy);
}