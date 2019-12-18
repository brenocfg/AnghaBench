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
struct mlx5_uuar_info {TYPE_1__* uars; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int MLX5_BF_REGS_PER_PAGE ; 

__attribute__((used)) static int uuarn_to_uar_index(struct mlx5_uuar_info *uuari, int uuarn)
{
	return uuari->uars[uuarn / MLX5_BF_REGS_PER_PAGE].index;
}