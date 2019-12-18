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
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RES_COUNTER ; 
 int RES_OP_RESERVE ; 
 int __mlx4_counter_alloc (struct mlx4_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __mlx4_counter_free (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int add_res_range (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int mlx4_grant_resource (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_release_resource (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_param_l (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int counter_alloc_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			     u64 in_param, u64 *out_param, int port)
{
	u32 index;
	int err;

	if (op != RES_OP_RESERVE)
		return -EINVAL;

	err = mlx4_grant_resource(dev, slave, RES_COUNTER, 1, 0);
	if (err)
		return err;

	err = __mlx4_counter_alloc(dev, &index);
	if (err) {
		mlx4_release_resource(dev, slave, RES_COUNTER, 1, 0);
		return err;
	}

	err = add_res_range(dev, slave, index, 1, RES_COUNTER, port);
	if (err) {
		__mlx4_counter_free(dev, index);
		mlx4_release_resource(dev, slave, RES_COUNTER, 1, 0);
	} else {
		set_param_l(out_param, index);
	}

	return err;
}