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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ends_with (char const*,char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int is_executable(const char *name)
{
	struct stat st;

	if (stat(name, &st) || /* stat, not lstat */
	    !S_ISREG(st.st_mode))
		return 0;

#if defined(GIT_WINDOWS_NATIVE)
	/*
	 * On Windows there is no executable bit. The file extension
	 * indicates whether it can be run as an executable, and Git
	 * has special-handling to detect scripts and launch them
	 * through the indicated script interpreter. We test for the
	 * file extension first because virus scanners may make
	 * it quite expensive to open many files.
	 */
	if (ends_with(name, ".exe"))
		return S_IXUSR;

{
	/*
	 * Now that we know it does not have an executable extension,
	 * peek into the file instead.
	 */
	char buf[3] = { 0 };
	int n;
	int fd = open(name, O_RDONLY);
	st.st_mode &= ~S_IXUSR;
	if (fd >= 0) {
		n = read(fd, buf, 2);
		if (n == 2)
			/* look for a she-bang */
			if (!strcmp(buf, "#!"))
				st.st_mode |= S_IXUSR;
		close(fd);
	}
}
#endif
	return st.st_mode & S_IXUSR;
}