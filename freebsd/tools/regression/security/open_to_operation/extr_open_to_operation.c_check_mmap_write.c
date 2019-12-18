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

/* Variables and functions */
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int O_ACCMODE ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  PROT_WRITE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  getpagesize () ; 
 char* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notok_mode (char const*,char*,int) ; 
 int /*<<< orphan*/  ok_mode (char const*,char*,int) ; 
 int open (char const*,int) ; 

__attribute__((used)) static void
check_mmap_write(const char *testname, const char *path, const int *modes,
    int modes_count)
{
	int fd, i, mode;
	char *addr;

	/*
	 * mmap() will always fail for directories (ideally) as they are
	 * always open O_RDONLY.  Check for O_WRONLY or O_RDWR to permit a
	 * write mapping.  This variant does a MAP_SHARED mapping, but we
	 * are also interested in MAP_PRIVATE.
	 */
	for (i = 0; i < modes_count; i++) {
		mode = modes[i];
		fd = open(path, mode);
		if (fd < 0) {
			notok_mode(testname, "open", mode);
			continue;
		}
		addr = mmap(NULL, getpagesize(), PROT_WRITE, MAP_SHARED, fd,
		    0);
		if (addr == MAP_FAILED) {
			if ((mode & O_ACCMODE) == O_WRONLY ||
			    (mode & O_ACCMODE) == O_RDWR)
				notok_mode(testname, "mmap failed",
				    mode);
			else
				ok_mode(testname, "mmap failed", mode);
		} else {
			if ((mode & O_ACCMODE) == O_WRONLY ||
			    (mode & O_ACCMODE) == O_RDWR)
				ok_mode(testname, "mmap succeeded",
				    mode);
			else
				notok_mode(testname, "mmap succeeded", mode);
			(void)munmap(addr, getpagesize());
		}
		close(fd);
	}
}