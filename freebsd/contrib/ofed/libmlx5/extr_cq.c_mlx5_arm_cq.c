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
typedef  int uint32_t ;
struct mlx5_cq {int arm_sn; int cons_index; int cqn; void** dbrec; } ;
struct mlx5_context {int /*<<< orphan*/  lock32; scalar_t__* uar; } ;
struct ibv_cq {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 size_t MLX5_CQ_ARM_DB ; 
 int MLX5_CQ_DB_REQ_NOT ; 
 int MLX5_CQ_DB_REQ_NOT_SOL ; 
 scalar_t__ MLX5_CQ_DOORBELL ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  mlx5_write64 (int*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmio_flush_writes () ; 
 int /*<<< orphan*/  mmio_wc_start () ; 
 struct mlx5_cq* to_mcq (struct ibv_cq*) ; 
 struct mlx5_context* to_mctx (int /*<<< orphan*/ ) ; 

int mlx5_arm_cq(struct ibv_cq *ibvcq, int solicited)
{
	struct mlx5_cq *cq = to_mcq(ibvcq);
	struct mlx5_context *ctx = to_mctx(ibvcq->context);
	uint32_t doorbell[2];
	uint32_t sn;
	uint32_t ci;
	uint32_t cmd;

	sn  = cq->arm_sn & 3;
	ci  = cq->cons_index & 0xffffff;
	cmd = solicited ? MLX5_CQ_DB_REQ_NOT_SOL : MLX5_CQ_DB_REQ_NOT;

	cq->dbrec[MLX5_CQ_ARM_DB] = htobe32(sn << 28 | cmd | ci);

	/*
	 * Make sure that the doorbell record in host memory is
	 * written before ringing the doorbell via PCI WC MMIO.
	 */
	mmio_wc_start();

	doorbell[0] = htobe32(sn << 28 | cmd | ci);
	doorbell[1] = htobe32(cq->cqn);

	mlx5_write64(doorbell, ctx->uar[0] + MLX5_CQ_DOORBELL, &ctx->lock32);

	mmio_flush_writes();

	return 0;
}