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
struct mlx4_func {int /*<<< orphan*/  rsvd_uars; int /*<<< orphan*/  rsvd_eqs; int /*<<< orphan*/  max_eq; } ;
struct mlx4_dev_cap {int /*<<< orphan*/  reserved_uars; int /*<<< orphan*/  reserved_eqs; int /*<<< orphan*/  max_eqs; } ;
struct TYPE_2__ {int flags2; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int MLX4_DEV_CAP_FLAG2_SYS_EQS ; 
 int MLX4_QUERY_FUNC_NUM_SYS_EQS ; 
 int mlx4_QUERY_FUNC (struct mlx4_dev*,struct mlx4_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 

__attribute__((used)) static int mlx4_query_func(struct mlx4_dev *dev, struct mlx4_dev_cap *dev_cap)
{
	int err = 0;
	struct mlx4_func func;

	if (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS) {
		err = mlx4_QUERY_FUNC(dev, &func, 0);
		if (err) {
			mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting.\n");
			return err;
		}
		dev_cap->max_eqs = func.max_eq;
		dev_cap->reserved_eqs = func.rsvd_eqs;
		dev_cap->reserved_uars = func.rsvd_uars;
		err |= MLX4_QUERY_FUNC_NUM_SYS_EQS;
	}
	return err;
}