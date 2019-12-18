#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_fpga_device {int /*<<< orphan*/  state_lock; TYPE_2__* mdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  fpga; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mlx5_fpga_get_cap(struct mlx5_fpga_device *fdev, u32 *fpga_caps)
{
	unsigned long flags;

	spin_lock_irqsave(&fdev->state_lock, flags);
	memcpy(fpga_caps, &fdev->mdev->caps.fpga, sizeof(fdev->mdev->caps.fpga));
	spin_unlock_irqrestore(&fdev->state_lock, flags);
}