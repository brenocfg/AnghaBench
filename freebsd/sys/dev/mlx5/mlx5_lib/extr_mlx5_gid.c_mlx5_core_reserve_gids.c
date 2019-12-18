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
struct TYPE_3__ {unsigned int start; scalar_t__ count; } ;
struct TYPE_4__ {TYPE_1__ reserved_gids; } ;
struct mlx5_core_dev {TYPE_2__ roce; int /*<<< orphan*/  intf_state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  MLX5_INTERFACE_STATE_UP ; 
 scalar_t__ MLX5_MAX_RESERVED_GIDS ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,unsigned int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mlx5_core_reserve_gids(struct mlx5_core_dev *dev, unsigned int count)
{
	if (test_bit(MLX5_INTERFACE_STATE_UP, &dev->intf_state)) {
		mlx5_core_err(dev, "Cannot reserve GIDs when interfaces are up\n");
		return -EPERM;
	}
	if (dev->roce.reserved_gids.start < count) {
		mlx5_core_warn(dev, "GID table exhausted attempting to reserve %d more GIDs\n",
			       count);
		return -ENOMEM;
	}
	if (dev->roce.reserved_gids.count + count > MLX5_MAX_RESERVED_GIDS) {
		mlx5_core_warn(dev, "Unable to reserve %d more GIDs\n", count);
		return -ENOMEM;
	}

	dev->roce.reserved_gids.start -= count;
	dev->roce.reserved_gids.count += count;
	mlx5_core_dbg(dev, "Reserved %u GIDs starting at %u\n",
		      dev->roce.reserved_gids.count,
		      dev->roce.reserved_gids.start);
	return 0;
}