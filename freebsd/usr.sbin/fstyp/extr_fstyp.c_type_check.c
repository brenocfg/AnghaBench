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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int fstat (int,struct stat*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
type_check(const char *path, FILE *fp)
{
	int error, fd;
	off_t mediasize;
	struct stat sb;

	fd = fileno(fp);

	error = fstat(fd, &sb);
	if (error != 0)
		err(1, "%s: fstat", path);

	if (S_ISREG(sb.st_mode))
		return;

	error = ioctl(fd, DIOCGMEDIASIZE, &mediasize);
	if (error != 0)
		errx(1, "%s: not a disk", path);
}