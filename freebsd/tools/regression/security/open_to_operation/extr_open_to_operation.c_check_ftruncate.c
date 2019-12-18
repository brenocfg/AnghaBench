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
struct stat {scalar_t__ st_size; } ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ ftruncate (int,scalar_t__) ; 
 int /*<<< orphan*/  notok_mode (char const*,char*,int) ; 
 int /*<<< orphan*/  ok_mode (char const*,char*,int) ; 
 int open (char const*,int) ; 

__attribute__((used)) static void
check_ftruncate(const char *testname, const char *path, const int *modes,
    int modes_count)
{
	struct stat sb;
	int fd, i, mode;

	/*
	 * ftruncate() should work as long as long as (mode & O_ACCMODE) is
	 * O_RDWR or O_WRONLY.
	 *
	 * Directories should never be writable, so this test should always
	 * pass for directories...
	 */
	for (i = 0; i < modes_count; i++) {
		mode = modes[i];
		fd = open(path, mode);
		if (fd < 0) {
			notok_mode(testname, "open", mode);
			notok_mode(testname, "truncate1 skipped", mode);
			notok_mode(testname, "truncate2 skipped", mode);
			notok_mode(testname, "truncate3 skipped", mode);
			continue;
		}
		if (fstat(fd, &sb) < 0) {
			notok_mode(testname, "fstat", mode);
			notok_mode(testname, "truncate1 skipped", mode);
			notok_mode(testname, "truncate2 skipped", mode);
			notok_mode(testname, "truncate3 skipped", mode);
			close(fd);
			continue;
		}
		ok_mode(testname, "setup", mode);

		/* Truncate to grow file. */
		if (ftruncate(fd, sb.st_size + 1) == 0) {
			if (((mode & O_ACCMODE) == O_WRONLY) ||
			    ((mode & O_ACCMODE) == O_RDWR))
				ok_mode(testname, "truncate1 succeeded",
				    mode);
			else {
				notok_mode(testname, "truncate1 succeeded",
				    mode);
				notok_mode(testname, "truncate2 skipped",
				    mode);
				notok_mode(testname, "truncate3 skipped",
				    mode);
				close(fd);
				continue;
			}
		} else {
			if (((mode & O_ACCMODE) == O_WRONLY) ||
			    ((mode & O_ACCMODE) == O_RDWR)) {
				notok_mode(testname, "truncate1 failed",
				    mode);
				notok_mode(testname, "truncate2 skipped",
				    mode);
				notok_mode(testname, "truncate3 skipped",
				    mode);
				close(fd);
				continue;
			} else
				ok_mode(testname, "truncate1 failed", mode);
		}

		/* Truncate to same size. */
		if (ftruncate(fd, sb.st_size + 1) == 0) {
			if (((mode & O_ACCMODE) == O_WRONLY) ||
			    ((mode & O_ACCMODE) == O_RDWR))
				ok_mode(testname, "truncate2 succeeded",
				    mode);
			else {
				notok_mode(testname, "truncate2 succeeded",
				    mode);
				notok_mode(testname, "truncate3 skipped",
				    mode);
				close(fd);
				continue;
			}
		} else {
			if (((mode & O_ACCMODE) == O_WRONLY) ||
			    ((mode & O_ACCMODE) == O_RDWR)) {
				notok_mode(testname, "truncate2 failed",
				    mode);
				notok_mode(testname, "truncate3 skipped",
				    mode);
				close(fd);
				continue;
			} else
				ok_mode(testname, "truncate2 failed", mode);
		}

		/* Truncate to shrink. */
		if (ftruncate(fd, sb.st_size) == 0) {
			if (((mode & O_ACCMODE) == O_WRONLY) ||
			    ((mode & O_ACCMODE) == O_RDWR))
				ok_mode(testname, "truncate3 succeeded",
				    mode);
			else
				notok_mode(testname, "truncate3 succeeded",
				    mode);
		} else {
			if (((mode & O_ACCMODE) == O_WRONLY) ||
			    ((mode & O_ACCMODE) == O_RDWR))
				notok_mode(testname, "truncate3 failed",
				    mode);
			else
				ok_mode(testname, "truncate3 failed", mode);
		}
		close(fd);
	}
}