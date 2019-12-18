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
typedef  int /*<<< orphan*/  uint64_t ;
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint64_t
ldi_get_size(void *priv)
{
	struct stat sb;
	int fd;

	fd = *(int *)priv;
	if (fstat(fd, &sb) != 0)
		return (0);
	if (S_ISCHR(sb.st_mode) && ioctl(fd, DIOCGMEDIASIZE, &sb.st_size) != 0)
		return (0);
	return (sb.st_size);
}