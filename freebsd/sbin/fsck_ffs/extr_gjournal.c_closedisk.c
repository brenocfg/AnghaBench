#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fs_clean; } ;

/* Variables and functions */
 int /*<<< orphan*/  devnam ; 
 int /*<<< orphan*/ * diskp ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* fs ; 
 int sbwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ufs_disk_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
closedisk(void)
{

	fs->fs_clean = 1;
	if (sbwrite(diskp, 0) == -1)
		err(1, "sbwrite(%s)", devnam);
	if (ufs_disk_close(diskp) == -1)
		err(1, "ufs_disk_close(%s)", devnam);
	free(diskp);
	diskp = NULL;
	fs = NULL;
}