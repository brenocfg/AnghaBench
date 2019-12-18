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
struct TYPE_2__ {int fw_pages; int* pages_per_func; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
typedef  int s64 ;

/* Variables and functions */
 int MAX_RECLAIM_TIME_MSECS ; 
 int jiffies ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  time_after (int,int) ; 

s64 mlx5_wait_for_reclaim_vfs_pages(struct mlx5_core_dev *dev)
{
	int end = jiffies + msecs_to_jiffies(MAX_RECLAIM_TIME_MSECS);
	s64 prevpages = 0;
	s64 npages = 0;

	while (!time_after(jiffies, end)) {
		/* exclude own function, VFs only */
		npages = dev->priv.fw_pages - dev->priv.pages_per_func[0];
		if (!npages)
			break;

		if (npages != prevpages)
			end = end + msecs_to_jiffies(100);

		prevpages = npages;
		msleep(1);
	}

	if (npages)
		mlx5_core_warn(dev, "FW did not return all VFs pages, will cause to memory leak\n");

	return -npages;
}