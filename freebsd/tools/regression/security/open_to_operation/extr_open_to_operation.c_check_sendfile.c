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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  notok_mode (char const*,char*,int) ; 
 int /*<<< orphan*/  ok_mode (char const*,char*,int) ; 
 int open (char const*,int) ; 
 scalar_t__ sendfile (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
check_sendfile(const char *testname, const char *path, int isdir,
    const int *modes, int modes_count)
{
	int fd, i, mode, sv[2];
	off_t sent;

	/*
	 * sendfile() should work only on files, and only when the access mode
	 * is O_RDONLY or O_RDWR.
	 */
	for (i = 0; i < modes_count; i++) {
		mode = modes[i];
		fd = open(path, mode);
		if (fd < 0) {
			notok_mode(testname, "open", mode);
			continue;
		}
		if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sv) < 0) {
			notok_mode(testname, "socketpair", mode);
			continue;
		}
		if (sendfile(fd, sv[0], 0, 1, NULL, &sent, 0) == 0) {
			if (isdir)
				notok_mode(testname, "directory succeeded",
				    mode);
			else if (((mode & O_ACCMODE) == O_RDONLY) ||
			    ((mode & O_ACCMODE) == O_RDWR))
				ok_mode(testname, "succeeded", mode);
			else
				notok_mode(testname, "succeeded", mode);
		} else {
			if (isdir)
				ok_mode(testname, "directory failed", mode);
			else if (((mode & O_ACCMODE) == O_RDONLY) ||
			    ((mode & O_ACCMODE) == O_RDWR))
				notok_mode(testname, "failed", mode);
			else
				ok_mode(testname, "failed", mode);
		}
		close(sv[0]);
		close(sv[1]);
		close(fd);
	}
}