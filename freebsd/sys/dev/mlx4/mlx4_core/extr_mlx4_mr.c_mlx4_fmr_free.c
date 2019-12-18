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
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;
struct mlx4_fmr {TYPE_1__ mr; scalar_t__ maps; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MLX4_MPT_DISABLED ; 
 int mlx4_mr_free (struct mlx4_dev*,TYPE_1__*) ; 

int mlx4_fmr_free(struct mlx4_dev *dev, struct mlx4_fmr *fmr)
{
	int ret;

	if (fmr->maps)
		return -EBUSY;

	ret = mlx4_mr_free(dev, &fmr->mr);
	if (ret)
		return ret;
	fmr->mr.enabled = MLX4_MPT_DISABLED;

	return 0;
}