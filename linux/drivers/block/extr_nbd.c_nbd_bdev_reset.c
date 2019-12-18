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
struct block_device {int bd_openers; } ;

/* Variables and functions */
 int /*<<< orphan*/  bd_set_size (struct block_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nbd_bdev_reset(struct block_device *bdev)
{
	if (bdev->bd_openers > 1)
		return;
	bd_set_size(bdev, 0);
}