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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_local_lb_selection { ____Placeholder_mlx5_local_lb_selection } mlx5_local_lb_selection ;
struct TYPE_2__ {int /*<<< orphan*/  disable_uc_local_lb; int /*<<< orphan*/  disable_mc_local_lb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_LOCAL_MC_LB ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_query_nic_vport_context (struct mlx5_core_dev*,int /*<<< orphan*/ ,void*,int) ; 
 TYPE_1__ nic_vport_context ; 
 int /*<<< orphan*/  query_nic_vport_context_out ; 

int mlx5_nic_vport_query_local_lb(struct mlx5_core_dev *mdev,
				  enum mlx5_local_lb_selection selection,
				  u8 *value)
{
	void *out;
	int outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);
	int err;

	out = kzalloc(outlen, GFP_KERNEL);
	if (!out)
		return -ENOMEM;

	err = mlx5_query_nic_vport_context(mdev, 0, out, outlen);
	if (err)
		goto done;

	if (selection == MLX5_LOCAL_MC_LB)
		*value = MLX5_GET(query_nic_vport_context_out, out,
				  nic_vport_context.disable_mc_local_lb);
	else
		*value = MLX5_GET(query_nic_vport_context_out, out,
				  nic_vport_context.disable_uc_local_lb);

done:
	kfree(out);
	return err;
}