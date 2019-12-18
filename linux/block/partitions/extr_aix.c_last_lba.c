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
typedef  int u64 ;
struct block_device {TYPE_1__* bd_inode; } ;
struct TYPE_2__ {int i_size; } ;

/* Variables and functions */

__attribute__((used)) static u64 last_lba(struct block_device *bdev)
{
	if (!bdev || !bdev->bd_inode)
		return 0;
	return (bdev->bd_inode->i_size >> 9) - 1ULL;
}