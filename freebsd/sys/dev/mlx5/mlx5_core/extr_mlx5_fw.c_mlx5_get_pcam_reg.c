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
struct TYPE_2__ {int /*<<< orphan*/  pcam; } ;
struct mlx5_core_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_PCAM_FEATURE_ENHANCED_FEATURES ; 
 int /*<<< orphan*/  MLX5_PCAM_REGS_5000_TO_507F ; 
 int mlx5_query_pcam_reg (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_get_pcam_reg(struct mlx5_core_dev *dev)
{
	return mlx5_query_pcam_reg(dev, dev->caps.pcam,
				   MLX5_PCAM_FEATURE_ENHANCED_FEATURES,
				   MLX5_PCAM_REGS_5000_TO_507F);
}