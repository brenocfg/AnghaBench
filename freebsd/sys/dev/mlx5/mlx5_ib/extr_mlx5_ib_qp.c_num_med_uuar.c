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
struct mlx5_uuar_info {int num_uars; int num_low_latency_uuars; } ;

/* Variables and functions */
 int MLX5_NON_FP_BF_REGS_PER_PAGE ; 

__attribute__((used)) static int num_med_uuar(struct mlx5_uuar_info *uuari)
{
	int n;

	n = uuari->num_uars * MLX5_NON_FP_BF_REGS_PER_PAGE -
		uuari->num_low_latency_uuars - 1;

	return n >= 0 ? n : 0;
}