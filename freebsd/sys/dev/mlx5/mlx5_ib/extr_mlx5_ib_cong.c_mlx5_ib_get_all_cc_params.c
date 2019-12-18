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
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * arg; } ;
struct mlx5_ib_dev {TYPE_1__ congestion; int /*<<< orphan*/  mdev; } ;
typedef  enum mlx5_ib_cong_node_type { ____Placeholder_mlx5_ib_cong_node_type } mlx5_ib_cong_node_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 size_t MLX5_IB_CONG_PARAMS_NUM ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  congestion_parameters ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_query_cong_params (int /*<<< orphan*/ ,int,void*,int) ; 
 int /*<<< orphan*/  mlx5_get_cc_param_val (void*,size_t) ; 
 int mlx5_ib_param_to_node (size_t) ; 
 int /*<<< orphan*/  query_cong_params_out ; 

__attribute__((used)) static int
mlx5_ib_get_all_cc_params(struct mlx5_ib_dev *dev)
{
	int outlen = MLX5_ST_SZ_BYTES(query_cong_params_out);
	enum mlx5_ib_cong_node_type node = 0;
	void *out;
	void *field;
	u32 x;
	int err = 0;

	out = kzalloc(outlen, GFP_KERNEL);
	if (!out)
		return -ENOMEM;

	/* get the current values */
	for (x = 0; x != MLX5_IB_CONG_PARAMS_NUM; x++) {
		if (node != mlx5_ib_param_to_node(x)) {
			node = mlx5_ib_param_to_node(x);

			err = mlx5_cmd_query_cong_params(dev->mdev, node, out, outlen);
			if (err)
				break;
		}
		field = MLX5_ADDR_OF(query_cong_params_out, out, congestion_parameters);
		dev->congestion.arg[x] = mlx5_get_cc_param_val(field, x);
	}
	kfree(out);
	return err;
}