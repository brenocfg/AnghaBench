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
struct mlx5_wqe_umr_ctrl_seg {int flags; int /*<<< orphan*/  mkey_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_MKEY_MASK_FREE ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_wqe_umr_ctrl_seg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_linv_umr_seg(struct mlx5_wqe_umr_ctrl_seg *umr)
{
	memset(umr, 0, sizeof(*umr));
	umr->mkey_mask = cpu_to_be64(MLX5_MKEY_MASK_FREE);
	umr->flags = 1 << 7;
}