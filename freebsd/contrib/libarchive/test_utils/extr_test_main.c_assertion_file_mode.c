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
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,...) ; 
 int lstat (char const*,struct stat*) ; 

int
assertion_file_mode(const char *file, int line, const char *pathname, int expected_mode)
{
	int mode;
	int r;

	assertion_count(file, line);
#if defined(_WIN32) && !defined(__CYGWIN__)
	failure_start(file, line, "assertFileMode not yet implemented for Windows");
	(void)mode; /* UNUSED */
	(void)r; /* UNUSED */
	(void)pathname; /* UNUSED */
	(void)expected_mode; /* UNUSED */
#else
	{
		struct stat st;
		r = lstat(pathname, &st);
		mode = (int)(st.st_mode & 0777);
	}
	if (r == 0 && mode == expected_mode)
			return (1);
	failure_start(file, line, "File %s has mode %o, expected %o",
	    pathname, mode, expected_mode);
#endif
	failure_finish(NULL);
	return (0);
}