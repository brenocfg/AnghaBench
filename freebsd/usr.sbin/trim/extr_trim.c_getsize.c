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
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_IOERR ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int O_DIRECT ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int opendev (char const*,int) ; 

__attribute__((used)) static off_t
getsize(const char *path)
{
	struct stat sb;
	off_t mediasize;
	int fd;

	fd = opendev(path, O_RDONLY | O_DIRECT);

	if (fstat(fd, &sb) < 0)
		err(EX_IOERR, "fstat failed: %s", path);

	if (S_ISREG(sb.st_mode) || S_ISDIR(sb.st_mode)) {
		close(fd);
		return (sb.st_size);
	}

	if (!S_ISCHR(sb.st_mode) && !S_ISBLK(sb.st_mode))
		errx(EX_DATAERR,
			"invalid type of the file "
			"(not regular, directory nor special device): %s",
			path);

	if (ioctl(fd, DIOCGMEDIASIZE, &mediasize) < 0)
		err(EX_UNAVAILABLE,
			"ioctl(DIOCGMEDIASIZE) failed, probably not a disk: "
			"%s", path);

	close(fd);
	return (mediasize);
}