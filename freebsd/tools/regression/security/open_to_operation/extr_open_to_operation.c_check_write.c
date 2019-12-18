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
typedef  scalar_t__ (* write_fn ) (int,char*,int) ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  notok_mode (char const*,char*,int) ; 
 int /*<<< orphan*/  ok_mode (char const*,char*,int) ; 
 int open (char const*,int) ; 

__attribute__((used)) static void
check_write(const char *testname, write_fn fn, const char *path,
    const int *modes, int modes_count)
{
	int fd, i, mode;
	char ch;

	/*
	 * write() should never succeed for directories, but especially
	 * because they can only be opened read-only.  write() on files
	 * should succeed for O_WRONLY and O_RDWR descriptors.
	 */

	for (i = 0; i < modes_count; i++) {
		mode = modes[i];
		fd = open(path, mode);
		if (fd < 0) {
			notok_mode(testname, "open", mode);
			continue;
		}
		if (fn(fd, &ch, sizeof(ch)) < 0) {
			if ((mode & O_ACCMODE) == O_WRONLY ||
			    (mode & O_ACCMODE) == O_RDWR)
				notok_mode(testname, "write failed", mode);
			else
				ok_mode(testname, "write failed", mode);
		} else {
			if (!((mode & O_ACCMODE) == O_WRONLY ||
			    (mode & O_ACCMODE) == O_RDWR))
				notok_mode(testname, "write succeeded", mode);
			else
				ok_mode(testname, "write succeeded", mode);
		}
		close(fd);
	}
}