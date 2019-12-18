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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGDELETE ; 
 scalar_t__ EOPNOTSUPP ; 
 int O_DIRECT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  candelete (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ getsize (char const*) ; 
 int ioctl (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int opendev (char const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
trim(const char *path, off_t offset, off_t length, bool dryrun, bool verbose)
{
	off_t arg[2];
	int error, fd;

	if (length == 0)
		length = getsize(path);

	if (verbose)
		printf("trim %s offset %ju length %ju\n",
		    path, (uintmax_t)offset, (uintmax_t)length);

	if (dryrun) {
		printf("dry run: add -f to actually perform the operation\n");
		return (0);
	}

	fd = opendev(path, O_WRONLY | O_DIRECT);
	arg[0] = offset;
	arg[1] = length;

	error = ioctl(fd, DIOCGDELETE, arg);
	if (error < 0) {
		if (errno == EOPNOTSUPP && verbose && !candelete(fd))
			warnx("%s: TRIM/UNMAP not supported by driver", path);
		else
			warn("ioctl(DIOCGDELETE) failed: %s", path);
	}
	close(fd);
	return (error);
}