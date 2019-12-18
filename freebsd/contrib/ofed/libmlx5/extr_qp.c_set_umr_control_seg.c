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
typedef  int /*<<< orphan*/  uint32_t ;
struct mlx5_wqe_umr_ctrl_seg {int flags; void* klm_octowords; int /*<<< orphan*/  mkey_mask; int /*<<< orphan*/  rsvd1; int /*<<< orphan*/  rsvd0; scalar_t__ translation_offset; } ;
struct mlx5_qp {int dummy; } ;
struct ibv_mw_bind_info {scalar_t__ length; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum ibv_mw_type { ____Placeholder_ibv_mw_type } ibv_mw_type ;

/* Variables and functions */
 int IBV_MW_TYPE_2 ; 
 int MLX5_WQE_UMR_CTRL_FLAG_CHECK_FREE ; 
 int MLX5_WQE_UMR_CTRL_FLAG_CHECK_QPN ; 
 int MLX5_WQE_UMR_CTRL_FLAG_INLINE ; 
 int MLX5_WQE_UMR_CTRL_FLAG_TRNSLATION_OFFSET ; 
 int MLX5_WQE_UMR_CTRL_MKEY_MASK_ACCESS_ATOMIC ; 
 int MLX5_WQE_UMR_CTRL_MKEY_MASK_ACCESS_LOCAL_WRITE ; 
 int MLX5_WQE_UMR_CTRL_MKEY_MASK_ACCESS_REMOTE_READ ; 
 int MLX5_WQE_UMR_CTRL_MKEY_MASK_ACCESS_REMOTE_WRITE ; 
 int MLX5_WQE_UMR_CTRL_MKEY_MASK_FREE ; 
 int MLX5_WQE_UMR_CTRL_MKEY_MASK_LEN ; 
 int MLX5_WQE_UMR_CTRL_MKEY_MASK_MKEY ; 
 int MLX5_WQE_UMR_CTRL_MKEY_MASK_QPN ; 
 int MLX5_WQE_UMR_CTRL_MKEY_MASK_START_ADDR ; 
 void* get_klm_octo (int) ; 
 int /*<<< orphan*/  htobe64 (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void set_umr_control_seg(struct mlx5_qp *qp, enum ibv_mw_type type,
				       int32_t rkey, struct ibv_mw_bind_info *bind_info,
				       uint32_t qpn, void **seg, int *size)
{
	struct mlx5_wqe_umr_ctrl_seg		*ctrl = *seg;

	ctrl->flags = MLX5_WQE_UMR_CTRL_FLAG_TRNSLATION_OFFSET |
		MLX5_WQE_UMR_CTRL_FLAG_INLINE;
	ctrl->mkey_mask = htobe64(MLX5_WQE_UMR_CTRL_MKEY_MASK_FREE |
				     MLX5_WQE_UMR_CTRL_MKEY_MASK_MKEY);
	ctrl->translation_offset = 0;
	memset(ctrl->rsvd0, 0, sizeof(ctrl->rsvd0));
	memset(ctrl->rsvd1, 0, sizeof(ctrl->rsvd1));

	if (type == IBV_MW_TYPE_2)
		ctrl->mkey_mask |= htobe64(MLX5_WQE_UMR_CTRL_MKEY_MASK_QPN);

	if (bind_info->length) {
		ctrl->klm_octowords = get_klm_octo(1);
		if (type == IBV_MW_TYPE_2)
			ctrl->flags |=  MLX5_WQE_UMR_CTRL_FLAG_CHECK_FREE;
		ctrl->mkey_mask |= htobe64(MLX5_WQE_UMR_CTRL_MKEY_MASK_LEN	|
					      MLX5_WQE_UMR_CTRL_MKEY_MASK_START_ADDR |
					      MLX5_WQE_UMR_CTRL_MKEY_MASK_ACCESS_LOCAL_WRITE |
					      MLX5_WQE_UMR_CTRL_MKEY_MASK_ACCESS_REMOTE_READ |
					      MLX5_WQE_UMR_CTRL_MKEY_MASK_ACCESS_REMOTE_WRITE |
					      MLX5_WQE_UMR_CTRL_MKEY_MASK_ACCESS_ATOMIC);
	} else {
		ctrl->klm_octowords = get_klm_octo(0);
		if (type == IBV_MW_TYPE_2)
			ctrl->flags |= MLX5_WQE_UMR_CTRL_FLAG_CHECK_QPN;
	}

	*seg += sizeof(struct mlx5_wqe_umr_ctrl_seg);
	*size += sizeof(struct mlx5_wqe_umr_ctrl_seg) / 16;
}