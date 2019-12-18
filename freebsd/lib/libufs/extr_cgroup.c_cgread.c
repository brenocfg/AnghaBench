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
struct TYPE_2__ {scalar_t__ fs_ncg; } ;
struct uufsd {scalar_t__ d_ccg; TYPE_1__ d_fs; } ;

/* Variables and functions */
 int cgread1 (struct uufsd*,int /*<<< orphan*/ ) ; 

int
cgread(struct uufsd *disk)
{

	if (disk->d_ccg >= disk->d_fs.fs_ncg)
		return (0);
	return (cgread1(disk, disk->d_ccg++));
}