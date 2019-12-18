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
typedef  int uint64_t ;
struct mlx5dv_context {int comp_mask; int /*<<< orphan*/  cqe_comp_caps; int /*<<< orphan*/  flags; scalar_t__ version; } ;
struct mlx5_context {scalar_t__ cqe_version; int vendor_cap_flags; int /*<<< orphan*/  cqe_comp_caps; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5DV_CONTEXT_FLAGS_CQE_V1 ; 
 int /*<<< orphan*/  MLX5DV_CONTEXT_FLAGS_MPW ; 
 int MLX5DV_CONTEXT_MASK_CQE_COMPRESION ; 
 scalar_t__ MLX5_CQE_VERSION_V1 ; 
 int MLX5_VENDOR_CAP_FLAGS_MPW ; 
 struct mlx5_context* to_mctx (struct ibv_context*) ; 

int mlx5dv_query_device(struct ibv_context *ctx_in,
			 struct mlx5dv_context *attrs_out)
{
	struct mlx5_context *mctx = to_mctx(ctx_in);
	uint64_t comp_mask_out = 0;

	attrs_out->version   = 0;
	attrs_out->flags     = 0;

	if (mctx->cqe_version == MLX5_CQE_VERSION_V1)
		attrs_out->flags |= MLX5DV_CONTEXT_FLAGS_CQE_V1;

	if (mctx->vendor_cap_flags & MLX5_VENDOR_CAP_FLAGS_MPW)
		attrs_out->flags |= MLX5DV_CONTEXT_FLAGS_MPW;

	if (attrs_out->comp_mask & MLX5DV_CONTEXT_MASK_CQE_COMPRESION) {
		attrs_out->cqe_comp_caps = mctx->cqe_comp_caps;
		comp_mask_out |= MLX5DV_CONTEXT_MASK_CQE_COMPRESION;
	}

	attrs_out->comp_mask = comp_mask_out;

	return 0;
}