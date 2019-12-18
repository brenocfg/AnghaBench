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
struct mlx5_mr {int dummy; } ;
struct ibv_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mlx5_mr*) ; 
 int ibv_cmd_dereg_mr (struct ibv_mr*) ; 
 struct mlx5_mr* to_mmr (struct ibv_mr*) ; 

int mlx5_dereg_mr(struct ibv_mr *ibmr)
{
	int ret;
	struct mlx5_mr *mr = to_mmr(ibmr);

	ret = ibv_cmd_dereg_mr(ibmr);
	if (ret)
		return ret;

	free(mr);
	return 0;
}