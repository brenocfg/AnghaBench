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
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct uufsd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct uufsd*,char*) ; 
 int berase_helper (struct uufsd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ufs_disk_write (struct uufsd*) ; 

int
berase(struct uufsd *disk, ufs2_daddr_t blockno, ufs2_daddr_t size)
{
	int rv;

	ERROR(disk, NULL);
	rv = ufs_disk_write(disk);
	if (rv == -1) {
		ERROR(disk, "failed to open disk for writing");
		return(rv);
	}
	return (berase_helper(disk, blockno, size));
}