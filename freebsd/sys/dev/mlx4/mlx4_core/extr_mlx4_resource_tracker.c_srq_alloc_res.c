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
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RES_OP_RESERVE_AND_MAP 128 
 int /*<<< orphan*/  RES_SRQ ; 
 int __mlx4_srq_alloc_icm (struct mlx4_dev*,int*) ; 
 int /*<<< orphan*/  __mlx4_srq_free_icm (struct mlx4_dev*,int) ; 
 int add_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_grant_resource (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_release_resource (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_param_l (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int srq_alloc_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			 u64 in_param, u64 *out_param)
{
	int srqn;
	int err;

	switch (op) {
	case RES_OP_RESERVE_AND_MAP:
		err = mlx4_grant_resource(dev, slave, RES_SRQ, 1, 0);
		if (err)
			break;

		err = __mlx4_srq_alloc_icm(dev, &srqn);
		if (err) {
			mlx4_release_resource(dev, slave, RES_SRQ, 1, 0);
			break;
		}

		err = add_res_range(dev, slave, srqn, 1, RES_SRQ, 0);
		if (err) {
			mlx4_release_resource(dev, slave, RES_SRQ, 1, 0);
			__mlx4_srq_free_icm(dev, srqn);
			break;
		}

		set_param_l(out_param, srqn);
		break;

	default:
		err = -EINVAL;
	}

	return err;
}