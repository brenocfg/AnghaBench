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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 
 int lstat (char const*,struct stat*) ; 
 size_t readlink (char const*,char*,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
is_symlink(const char *file, int line,
    const char *pathname, const char *contents)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	(void)pathname; /* UNUSED */
	(void)contents; /* UNUSED */
	assertion_count(file, line);
	/* Windows sort-of has real symlinks, but they're only usable
	 * by privileged users and are crippled even then, so there's
	 * really not much point in bothering with this. */
	return (0);
#else
	char buff[300];
	struct stat st;
	ssize_t linklen;
	int r;

	assertion_count(file, line);
	r = lstat(pathname, &st);
	if (r != 0) {
		failure_start(file, line,
		    "Symlink should exist: %s", pathname);
		failure_finish(NULL);
		return (0);
	}
	if (!S_ISLNK(st.st_mode))
		return (0);
	if (contents == NULL)
		return (1);
	linklen = readlink(pathname, buff, sizeof(buff));
	if (linklen < 0) {
		failure_start(file, line, "Can't read symlink %s", pathname);
		failure_finish(NULL);
		return (0);
	}
	buff[linklen] = '\0';
	if (strcmp(buff, contents) != 0)
		return (0);
	return (1);
#endif
}