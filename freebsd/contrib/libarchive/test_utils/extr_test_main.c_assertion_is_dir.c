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
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int) ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 
 int /*<<< orphan*/  logprintf (char*,int) ; 
 int lstat (char const*,struct stat*) ; 

int
assertion_is_dir(const char *file, int line, const char *pathname, int mode)
{
	struct stat st;
	int r;

#if defined(_WIN32) && !defined(__CYGWIN__)
	(void)mode; /* UNUSED */
#endif
	assertion_count(file, line);
	r = lstat(pathname, &st);
	if (r != 0) {
		failure_start(file, line, "Dir should exist: %s", pathname);
		failure_finish(NULL);
		return (0);
	}
	if (!S_ISDIR(st.st_mode)) {
		failure_start(file, line, "%s is not a dir", pathname);
		failure_finish(NULL);
		return (0);
	}
#if !defined(_WIN32) || defined(__CYGWIN__)
	/* Windows doesn't handle permissions the same way as POSIX,
	 * so just ignore the mode tests. */
	/* TODO: Can we do better here? */
	if (mode >= 0 && (mode_t)mode != (st.st_mode & 07777)) {
		failure_start(file, line, "Dir %s has wrong mode", pathname);
		logprintf("  Expected: 0%3o\n", mode);
		logprintf("  Found: 0%3o\n", st.st_mode & 07777);
		failure_finish(NULL);
		return (0);
	}
#endif
	return (1);
}