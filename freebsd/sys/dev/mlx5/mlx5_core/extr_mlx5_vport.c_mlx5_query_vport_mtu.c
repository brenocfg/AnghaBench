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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int mlx5_query_nic_vport_context (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlx5_vzalloc (int /*<<< orphan*/ ) ; 
 TYPE_1__ nic_vport_context ; 
 int /*<<< orphan*/  query_nic_vport_context_out ; 

int mlx5_query_vport_mtu(struct mlx5_core_dev *mdev, int *mtu)
{
	u32 *out;
	u32 outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);
	int err;

	out = mlx5_vzalloc(outlen);
	if (!out)
		return -ENOMEM;

	err = mlx5_query_nic_vport_context(mdev, 0, out, outlen);
	if (err)
		goto out;

	*mtu = MLX5_GET(query_nic_vport_context_out, out,
			nic_vport_context.mtu);

out:
	kvfree(out);
	return err;
}