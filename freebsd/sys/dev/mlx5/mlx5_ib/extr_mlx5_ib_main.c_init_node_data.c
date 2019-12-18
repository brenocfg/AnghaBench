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
struct TYPE_2__ {int /*<<< orphan*/  node_guid; int /*<<< orphan*/  node_desc; } ;
struct mlx5_ib_dev {TYPE_1__ ib_dev; } ;

/* Variables and functions */
 int mlx5_query_node_desc (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_query_node_guid (struct mlx5_ib_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_node_data(struct mlx5_ib_dev *dev)
{
	int err;

	err = mlx5_query_node_desc(dev, dev->ib_dev.node_desc);
	if (err)
		return err;

	return mlx5_query_node_guid(dev, &dev->ib_dev.node_guid);
}