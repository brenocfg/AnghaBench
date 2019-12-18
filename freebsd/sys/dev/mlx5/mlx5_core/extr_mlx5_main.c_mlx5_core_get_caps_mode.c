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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct mlx5_core_dev {int /*<<< orphan*/ * hca_caps_cur; int /*<<< orphan*/ * hca_caps_max; } ;
typedef  int /*<<< orphan*/  in ;
typedef  enum mlx5_cap_type { ____Placeholder_mlx5_cap_type } mlx5_cap_type ;
typedef  enum mlx5_cap_mode { ____Placeholder_mlx5_cap_mode } mlx5_cap_mode ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HCA_CAP_OPMOD_GET_CUR 129 
#define  HCA_CAP_OPMOD_GET_MAX 128 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_CMD_OP_QUERY_HCA_CAP ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_UN_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capability ; 
 int /*<<< orphan*/  hca_cap_union ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_cmd_exec (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,void*,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int,int,...) ; 
 int /*<<< orphan*/  op_mod ; 
 int /*<<< orphan*/  opcode ; 
 int /*<<< orphan*/  query_hca_cap_in ; 
 int /*<<< orphan*/  query_hca_cap_out ; 

__attribute__((used)) static int mlx5_core_get_caps_mode(struct mlx5_core_dev *dev,
				   enum mlx5_cap_type cap_type,
				   enum mlx5_cap_mode cap_mode)
{
	u8 in[MLX5_ST_SZ_BYTES(query_hca_cap_in)];
	int out_sz = MLX5_ST_SZ_BYTES(query_hca_cap_out);
	void *out, *hca_caps;
	u16 opmod = (cap_type << 1) | (cap_mode & 0x01);
	int err;

	memset(in, 0, sizeof(in));
	out = kzalloc(out_sz, GFP_KERNEL);

	MLX5_SET(query_hca_cap_in, in, opcode, MLX5_CMD_OP_QUERY_HCA_CAP);
	MLX5_SET(query_hca_cap_in, in, op_mod, opmod);
	err = mlx5_cmd_exec(dev, in, sizeof(in), out, out_sz);
	if (err) {
		mlx5_core_warn(dev,
			       "QUERY_HCA_CAP : type(%x) opmode(%x) Failed(%d)\n",
			       cap_type, cap_mode, err);
		goto query_ex;
	}

	hca_caps =  MLX5_ADDR_OF(query_hca_cap_out, out, capability);

	switch (cap_mode) {
	case HCA_CAP_OPMOD_GET_MAX:
		memcpy(dev->hca_caps_max[cap_type], hca_caps,
		       MLX5_UN_SZ_BYTES(hca_cap_union));
		break;
	case HCA_CAP_OPMOD_GET_CUR:
		memcpy(dev->hca_caps_cur[cap_type], hca_caps,
		       MLX5_UN_SZ_BYTES(hca_cap_union));
		break;
	default:
		mlx5_core_warn(dev,
			       "Tried to query dev cap type(%x) with wrong opmode(%x)\n",
			       cap_type, cap_mode);
		err = -EINVAL;
		break;
	}
query_ex:
	kfree(out);
	return err;
}