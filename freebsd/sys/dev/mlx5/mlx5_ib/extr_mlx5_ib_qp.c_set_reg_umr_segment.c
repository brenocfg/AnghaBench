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
struct mlx5_wqe_umr_ctrl_seg {int /*<<< orphan*/  flags; int /*<<< orphan*/  mkey_mask; void* bsf_octowords; void* klm_octowords; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;
struct mlx5_umr_wr {TYPE_1__ target; int /*<<< orphan*/  npages; } ;
struct ib_send_wr {int send_flags; int /*<<< orphan*/  num_sge; } ;

/* Variables and functions */
 int MLX5_IB_SEND_UMR_FAIL_IF_FREE ; 
 int MLX5_IB_SEND_UMR_UNREG ; 
 int MLX5_IB_SEND_UMR_UPDATE_ACCESS ; 
 int MLX5_IB_SEND_UMR_UPDATE_MTT ; 
 int MLX5_IB_SEND_UMR_UPDATE_PD ; 
 int MLX5_IB_SEND_UMR_UPDATE_TRANSLATION ; 
 int /*<<< orphan*/  MLX5_UMR_CHECK_FREE ; 
 int /*<<< orphan*/  MLX5_UMR_CHECK_NOT_FREE ; 
 int /*<<< orphan*/  MLX5_UMR_INLINE ; 
 int /*<<< orphan*/  MLX5_UMR_TRANSLATION_OFFSET_EN ; 
 void* get_klm_octo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_umr_reg_mr_mask () ; 
 int /*<<< orphan*/  get_umr_unreg_mr_mask () ; 
 int /*<<< orphan*/  get_umr_update_access_mask () ; 
 int /*<<< orphan*/  get_umr_update_mtt_mask () ; 
 int /*<<< orphan*/  get_umr_update_pd_mask () ; 
 int /*<<< orphan*/  get_umr_update_translation_mask () ; 
 int /*<<< orphan*/  memset (struct mlx5_wqe_umr_ctrl_seg*,int /*<<< orphan*/ ,int) ; 
 struct mlx5_umr_wr* umr_wr (struct ib_send_wr*) ; 

__attribute__((used)) static void set_reg_umr_segment(struct mlx5_wqe_umr_ctrl_seg *umr,
				struct ib_send_wr *wr)
{
	struct mlx5_umr_wr *umrwr = umr_wr(wr);

	memset(umr, 0, sizeof(*umr));

	if (wr->send_flags & MLX5_IB_SEND_UMR_FAIL_IF_FREE)
		umr->flags = MLX5_UMR_CHECK_FREE; /* fail if free */
	else
		umr->flags = MLX5_UMR_CHECK_NOT_FREE; /* fail if not free */

	if (!(wr->send_flags & MLX5_IB_SEND_UMR_UNREG)) {
		umr->klm_octowords = get_klm_octo(umrwr->npages);
		if (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_MTT) {
			umr->mkey_mask = get_umr_update_mtt_mask();
			umr->bsf_octowords = get_klm_octo(umrwr->target.offset);
			umr->flags |= MLX5_UMR_TRANSLATION_OFFSET_EN;
		}
		if (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_TRANSLATION)
			umr->mkey_mask |= get_umr_update_translation_mask();
		if (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_ACCESS)
			umr->mkey_mask |= get_umr_update_access_mask();
		if (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_PD)
			umr->mkey_mask |= get_umr_update_pd_mask();
		if (!umr->mkey_mask)
			umr->mkey_mask = get_umr_reg_mr_mask();
	} else {
		umr->mkey_mask = get_umr_unreg_mr_mask();
	}

	if (!wr->num_sge)
		umr->flags |= MLX5_UMR_INLINE;
}