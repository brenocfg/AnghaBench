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
struct mlx4_cqe {int dummy; } ;
struct mlx4_cq {int dummy; } ;
struct ibv_cq_ex {int dummy; } ;

/* Variables and functions */
 int CQ_EMPTY ; 
 int ENOENT ; 
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 int mlx4_get_next_cqe (struct mlx4_cq*,struct mlx4_cqe**) ; 
 int mlx4_parse_lazy_cqe (struct mlx4_cq*,struct mlx4_cqe*) ; 
 struct mlx4_cq* to_mcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_next_poll(struct ibv_cq_ex *ibcq)
{
	struct mlx4_cq *cq = to_mcq(ibv_cq_ex_to_cq(ibcq));
	struct mlx4_cqe *cqe;
	int err;

	err = mlx4_get_next_cqe(cq, &cqe);
	if (err == CQ_EMPTY)
		return ENOENT;

	return mlx4_parse_lazy_cqe(cq, cqe);
}