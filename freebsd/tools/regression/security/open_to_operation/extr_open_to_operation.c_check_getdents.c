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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ getdents (int,char*,int) ; 
 int /*<<< orphan*/  notok_mode (char const*,char*,int) ; 
 int /*<<< orphan*/  ok_mode (char const*,char*,int) ; 
 int open (char const*,int) ; 

__attribute__((used)) static void
check_getdents(const char *testname, const char *path, int isdir,
    const int *modes, int modes_count)
{
	int fd, i, mode;
	char buf[8192];

	/*
	 * getdents() should always work on directories and never on files,
	 * assuming directories are always opened for read (which they are).
	 */
	for (i = 0; i < modes_count; i++) {
		mode = modes[i];
		fd = open(path, mode);
		if (fd < 0) {
			notok_mode(testname, "open", mode);
			continue;
		}
		if (getdents(fd, buf, sizeof(buf)) >= 0) {
			if (isdir && ((mode & O_ACCMODE) == O_RDONLY))
				ok_mode(testname, "directory succeeded",
				    mode);
			else if (isdir)
				notok_mode(testname, "directory succeeded",
				    mode);
			else
				notok_mode(testname, "file succeeded", mode);
		} else {
			if (isdir && ((mode & O_ACCMODE) == O_RDONLY))
				notok_mode(testname, "directory failed",
				    mode);
			else if (isdir)
				ok_mode(testname, "directory failed", mode);
			else
				ok_mode(testname, "file failed", mode);
		}
		close(fd);
	}
}