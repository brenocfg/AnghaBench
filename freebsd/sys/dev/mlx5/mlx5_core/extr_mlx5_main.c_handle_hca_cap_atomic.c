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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_ATOMIC_REQ_MODE_HOST_ENDIANNESS ; 
 int MLX5_CAP_ATOMIC (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_SET_HCA_CAP_OP_MOD_ATOMIC ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic ; 
 int /*<<< orphan*/  atomic_caps ; 
 int /*<<< orphan*/  atomic_req_8B_endianess_mode ; 
 int /*<<< orphan*/  capability ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_get_caps (struct mlx5_core_dev*,int (*) (struct mlx5_core_dev*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  op_mod ; 
 int set_caps (struct mlx5_core_dev*,void*,int) ; 
 int /*<<< orphan*/  set_hca_cap_in ; 
 int /*<<< orphan*/  supported_atomic_req_8B_endianess_mode_1 ; 

__attribute__((used)) static int handle_hca_cap_atomic(struct mlx5_core_dev *dev)
{
	void *set_ctx;
	void *set_hca_cap;
	int set_sz = MLX5_ST_SZ_BYTES(set_hca_cap_in);
	int req_endianness;
	int err;

	if (MLX5_CAP_GEN(dev, atomic)) {
		err = mlx5_core_get_caps(dev, MLX5_CAP_ATOMIC);
		if (err)
			return err;
	} else {
		return 0;
	}

	req_endianness =
		MLX5_CAP_ATOMIC(dev,
				supported_atomic_req_8B_endianess_mode_1);

	if (req_endianness != MLX5_ATOMIC_REQ_MODE_HOST_ENDIANNESS)
		return 0;

	set_ctx = kzalloc(set_sz, GFP_KERNEL);
	if (!set_ctx)
		return -ENOMEM;

	MLX5_SET(set_hca_cap_in, set_ctx, op_mod,
		 MLX5_SET_HCA_CAP_OP_MOD_ATOMIC << 1);
	set_hca_cap = MLX5_ADDR_OF(set_hca_cap_in, set_ctx, capability);

	/* Set requestor to host endianness */
	MLX5_SET(atomic_caps, set_hca_cap, atomic_req_8B_endianess_mode,
		 MLX5_ATOMIC_REQ_MODE_HOST_ENDIANNESS);

	err = set_caps(dev, set_ctx, set_sz);

	kfree(set_ctx);
	return err;
}