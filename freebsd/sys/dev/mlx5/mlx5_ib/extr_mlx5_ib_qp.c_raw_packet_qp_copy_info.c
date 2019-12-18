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
struct mlx5_ib_sq {int /*<<< orphan*/ * doorbell; int /*<<< orphan*/ * sq; } ;
struct mlx5_ib_rq {int /*<<< orphan*/ * doorbell; int /*<<< orphan*/ * rq; } ;
struct mlx5_ib_raw_packet_qp {struct mlx5_ib_rq rq; struct mlx5_ib_sq sq; } ;
struct mlx5_ib_qp {int /*<<< orphan*/  db; int /*<<< orphan*/  rq; int /*<<< orphan*/  sq; } ;

/* Variables and functions */

__attribute__((used)) static void raw_packet_qp_copy_info(struct mlx5_ib_qp *qp,
				    struct mlx5_ib_raw_packet_qp *raw_packet_qp)
{
	struct mlx5_ib_sq *sq = &raw_packet_qp->sq;
	struct mlx5_ib_rq *rq = &raw_packet_qp->rq;

	sq->sq = &qp->sq;
	rq->rq = &qp->rq;
	sq->doorbell = &qp->db;
	rq->doorbell = &qp->db;
}