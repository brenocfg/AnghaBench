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
struct mlx5_wqe_umr_ctrl_seg {int /*<<< orphan*/  mkey_mask; int /*<<< orphan*/  klm_octowords; int /*<<< orphan*/  flags; } ;
struct mlx5_ib_mr {int ndescs; scalar_t__ access_mode; } ;

/* Variables and functions */
 scalar_t__ MLX5_ACCESS_MODE_KLM ; 
 int /*<<< orphan*/  MLX5_UMR_CHECK_NOT_FREE ; 
 int /*<<< orphan*/  frwr_mkey_mask () ; 
 int /*<<< orphan*/  get_klm_octo (int) ; 
 int /*<<< orphan*/  memset (struct mlx5_wqe_umr_ctrl_seg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_reg_umr_seg(struct mlx5_wqe_umr_ctrl_seg *umr,
				struct mlx5_ib_mr *mr)
{
	int ndescs = mr->ndescs;

	memset(umr, 0, sizeof(*umr));

	if (mr->access_mode == MLX5_ACCESS_MODE_KLM)
		/* KLMs take twice the size of MTTs */
		ndescs *= 2;

	umr->flags = MLX5_UMR_CHECK_NOT_FREE;
	umr->klm_octowords = get_klm_octo(ndescs);
	umr->mkey_mask = frwr_mkey_mask();
}