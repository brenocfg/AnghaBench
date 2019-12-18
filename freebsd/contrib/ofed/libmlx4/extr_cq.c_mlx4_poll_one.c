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
struct mlx4_qp {int dummy; } ;
struct mlx4_cqe {int dummy; } ;
struct mlx4_cq {int dummy; } ;
struct ibv_wc {int dummy; } ;

/* Variables and functions */
 int CQ_EMPTY ; 
 int mlx4_get_next_cqe (struct mlx4_cq*,struct mlx4_cqe**) ; 
 int mlx4_parse_cqe (struct mlx4_cq*,struct mlx4_cqe*,struct mlx4_qp**,struct ibv_wc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mlx4_poll_one(struct mlx4_cq *cq,
			 struct mlx4_qp **cur_qp,
			 struct ibv_wc *wc)
{
	struct mlx4_cqe *cqe;
	int err;

	err = mlx4_get_next_cqe(cq, &cqe);
	if (err == CQ_EMPTY)
		return err;

	return mlx4_parse_cqe(cq, cqe, cur_qp, wc, 0);
}