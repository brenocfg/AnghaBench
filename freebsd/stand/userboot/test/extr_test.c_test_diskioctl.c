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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
#define  DIOCGMEDIASIZE 129 
#define  DIOCGSECTORSIZE 128 
 int EBADF ; 
 int ENOTTY ; 
 int* disk_fd ; 
 int disk_index ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 

int
test_diskioctl(void *arg, int unit, u_long cmd, void *data)
{
	struct stat sb;

	if (unit > disk_index || disk_fd[unit] == -1)
		return (EBADF);
	switch (cmd) {
	case DIOCGSECTORSIZE:
		*(u_int *)data = 512;
		break;
	case DIOCGMEDIASIZE:
		if (fstat(disk_fd[unit], &sb) == 0)
			*(off_t *)data = sb.st_size;
		else
			return (ENOTTY);
		break;
	default:
		return (ENOTTY);
	}
	return (0);
}