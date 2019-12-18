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
struct uufsd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct uufsd*,char*) ; 
 int sbread (struct uufsd*) ; 
 int /*<<< orphan*/  ufs_disk_close (struct uufsd*) ; 
 int ufs_disk_fillout_blank (struct uufsd*,char const*) ; 

int
ufs_disk_fillout(struct uufsd *disk, const char *name)
{
	if (ufs_disk_fillout_blank(disk, name) == -1) {
		return (-1);
	}
	if (sbread(disk) == -1) {
		ERROR(disk, "could not read superblock to fill out disk");
		ufs_disk_close(disk);
		return (-1);
	}
	return (0);
}