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
struct mlx5_reg_node_desc {int dummy; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_REG_NODE_DESC ; 
 int /*<<< orphan*/  memset (struct mlx5_reg_node_desc*,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_access_reg (int /*<<< orphan*/ ,struct mlx5_reg_node_desc*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_query_mad_ifc_node_desc (struct mlx5_ib_dev*,char*) ; 
 scalar_t__ mlx5_use_mad_ifc (struct mlx5_ib_dev*) ; 

__attribute__((used)) static int mlx5_query_node_desc(struct mlx5_ib_dev *dev, char *node_desc)
{
	struct mlx5_reg_node_desc in;

	if (mlx5_use_mad_ifc(dev))
		return mlx5_query_mad_ifc_node_desc(dev, node_desc);

	memset(&in, 0, sizeof(in));

	return mlx5_core_access_reg(dev->mdev, &in, sizeof(in), node_desc,
				    sizeof(struct mlx5_reg_node_desc),
				    MLX5_REG_NODE_DESC, 0, 0);
}