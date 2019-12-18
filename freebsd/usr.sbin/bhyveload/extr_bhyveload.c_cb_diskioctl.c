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
typedef  int u_long ;
typedef  int u_int ;
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
#define  DIOCGMEDIASIZE 129 
#define  DIOCGSECTORSIZE 128 
 int EBADF ; 
 int ENOTTY ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * disk_fd ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 
 int ndisks ; 

__attribute__((used)) static int
cb_diskioctl(void *arg, int unit, u_long cmd, void *data)
{
	struct stat sb;

	if (unit < 0 || unit >= ndisks)
		return (EBADF);

	switch (cmd) {
	case DIOCGSECTORSIZE:
		*(u_int *)data = 512;
		break;
	case DIOCGMEDIASIZE:
		if (fstat(disk_fd[unit], &sb) != 0)
			return (ENOTTY);
		if (S_ISCHR(sb.st_mode) &&
		    ioctl(disk_fd[unit], DIOCGMEDIASIZE, &sb.st_size) != 0)
				return (ENOTTY);
		*(off_t *)data = sb.st_size;
		break;
	default:
		return (ENOTTY);
	}

	return (0);
}