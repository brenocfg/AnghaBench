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
struct uufsd {int d_mine; int d_fd; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct uufsd*,char*) ; 
 int MINE_WRITE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ufs_disk_write(struct uufsd *disk)
{
	int fd;

	ERROR(disk, NULL);

	if (disk->d_mine & MINE_WRITE)
		return (0);

	fd = open(disk->d_name, O_RDWR);
	if (fd < 0) {
		ERROR(disk, "failed to open disk for writing");
		return (-1);
	}

	close(disk->d_fd);
	disk->d_fd = fd;
	disk->d_mine |= MINE_WRITE;

	return (0);
}