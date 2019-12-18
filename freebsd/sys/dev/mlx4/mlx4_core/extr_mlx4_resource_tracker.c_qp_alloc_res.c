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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int alloc_res_qp_mask; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  RES_OP_MAP_ICM 129 
#define  RES_OP_RESERVE 128 
 int /*<<< orphan*/  RES_QP ; 
 int /*<<< orphan*/  RES_QP_MAPPED ; 
 int __mlx4_qp_alloc_icm (struct mlx4_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mlx4_qp_release_range (struct mlx4_dev*,int,int) ; 
 int __mlx4_qp_reserve_range (struct mlx4_dev*,int,int,int*,int) ; 
 int add_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_reserved (struct mlx4_dev*,int) ; 
 int get_param_h (int /*<<< orphan*/ *) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int mlx4_grant_resource (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_release_resource (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int qp_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  res_abort_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_param_l (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  valid_reserved (struct mlx4_dev*,int,int) ; 

__attribute__((used)) static int qp_alloc_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			u64 in_param, u64 *out_param)
{
	int err;
	int count;
	int align;
	int base;
	int qpn;
	u8 flags;

	switch (op) {
	case RES_OP_RESERVE:
		count = get_param_l(&in_param) & 0xffffff;
		/* Turn off all unsupported QP allocation flags that the
		 * slave tries to set.
		 */
		flags = (get_param_l(&in_param) >> 24) & dev->caps.alloc_res_qp_mask;
		align = get_param_h(&in_param);
		err = mlx4_grant_resource(dev, slave, RES_QP, count, 0);
		if (err)
			return err;

		err = __mlx4_qp_reserve_range(dev, count, align, &base, flags);
		if (err) {
			mlx4_release_resource(dev, slave, RES_QP, count, 0);
			return err;
		}

		err = add_res_range(dev, slave, base, count, RES_QP, 0);
		if (err) {
			mlx4_release_resource(dev, slave, RES_QP, count, 0);
			__mlx4_qp_release_range(dev, base, count);
			return err;
		}
		set_param_l(out_param, base);
		break;
	case RES_OP_MAP_ICM:
		qpn = get_param_l(&in_param) & 0x7fffff;
		if (valid_reserved(dev, slave, qpn)) {
			err = add_res_range(dev, slave, qpn, 1, RES_QP, 0);
			if (err)
				return err;
		}

		err = qp_res_start_move_to(dev, slave, qpn, RES_QP_MAPPED,
					   NULL, 1);
		if (err)
			return err;

		if (!fw_reserved(dev, qpn)) {
			err = __mlx4_qp_alloc_icm(dev, qpn, GFP_KERNEL);
			if (err) {
				res_abort_move(dev, slave, RES_QP, qpn);
				return err;
			}
		}

		res_end_move(dev, slave, RES_QP, qpn);
		break;

	default:
		err = -EINVAL;
		break;
	}
	return err;
}