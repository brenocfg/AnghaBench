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
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_ib_dev {TYPE_2__* dev; } ;
struct gid_entry {int dummy; } ;
struct TYPE_3__ {int flags2; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int MLX4_DEV_CAP_FLAG2_ROCE_V1_V2 ; 
 int mlx4_ib_update_gids_v1 (struct gid_entry*,struct mlx4_ib_dev*,int /*<<< orphan*/ ) ; 
 int mlx4_ib_update_gids_v1_v2 (struct gid_entry*,struct mlx4_ib_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_ib_update_gids(struct gid_entry *gids,
			       struct mlx4_ib_dev *ibdev,
			       u8 port_num)
{
	if (ibdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ROCE_V1_V2)
		return mlx4_ib_update_gids_v1_v2(gids, ibdev, port_num);

	return mlx4_ib_update_gids_v1(gids, ibdev, port_num);
}