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
struct statvfs {int dummy; } ;
struct statfs {int dummy; } ;
typedef  int /*<<< orphan*/  fs ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  copy_statfs_to_statvfs (struct statvfs*,struct statfs*) ; 
 int /*<<< orphan*/  errno ; 
 int fstatfs (int,struct statfs*) ; 
 int /*<<< orphan*/  memset (struct statfs*,int /*<<< orphan*/ ,int) ; 

int fstatvfs(int fd, struct statvfs *buf)
{
#  ifdef HAVE_FSTATFS
	struct statfs fs;

	memset(&fs, 0, sizeof(fs));
	if (fstatfs(fd, &fs) == -1)
		return -1;
	copy_statfs_to_statvfs(buf, &fs);
	return 0;
#  else
	errno = ENOSYS;
	return -1;
#  endif
}