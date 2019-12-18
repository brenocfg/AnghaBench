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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_guid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5_GET64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int mlx5_query_nic_vport_context (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mlx5_vzalloc (int) ; 
 TYPE_1__ nic_vport_context ; 
 int /*<<< orphan*/  query_nic_vport_context_out ; 

__attribute__((used)) static int mlx5_query_nic_vport_port_guid(struct mlx5_core_dev *mdev,
					  u64 *port_guid)
{
	u32 *out;
	int outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);
	int err;

	out = mlx5_vzalloc(outlen);
	if (!out)
		return -ENOMEM;

	err = mlx5_query_nic_vport_context(mdev, 0, out, outlen);
	if (err)
		goto out;

	*port_guid = MLX5_GET64(query_nic_vport_context_out, out,
				nic_vport_context.port_guid);

out:
	kvfree(out);
	return err;
}