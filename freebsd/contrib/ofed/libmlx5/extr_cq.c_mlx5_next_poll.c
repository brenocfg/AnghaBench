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
struct mlx5_cqe64 {int dummy; } ;
struct mlx5_cq {int /*<<< orphan*/  flags; } ;
struct ibv_cq_ex {int dummy; } ;
typedef  enum polling_mode { ____Placeholder_polling_mode } polling_mode ;

/* Variables and functions */
 int CQ_EMPTY ; 
 int ENOENT ; 
 int /*<<< orphan*/  MLX5_CQ_FLAGS_EMPTY_DURING_POLL ; 
 int POLLING_MODE_STALL_ADAPTIVE ; 
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 int mlx5_get_next_cqe (struct mlx5_cq*,struct mlx5_cqe64**,void**) ; 
 int mlx5_parse_lazy_cqe (struct mlx5_cq*,struct mlx5_cqe64*,void*,int) ; 
 struct mlx5_cq* to_mcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mlx5_next_poll(struct ibv_cq_ex *ibcq,
				 enum polling_mode stall,
				 int cqe_version)
{
	struct mlx5_cq *cq = to_mcq(ibv_cq_ex_to_cq(ibcq));
	struct mlx5_cqe64 *cqe64;
	void *cqe;
	int err;

	err = mlx5_get_next_cqe(cq, &cqe64, &cqe);
	if (err == CQ_EMPTY) {
		if (stall == POLLING_MODE_STALL_ADAPTIVE)
			cq->flags |= MLX5_CQ_FLAGS_EMPTY_DURING_POLL;

		return ENOENT;
	}

	return mlx5_parse_lazy_cqe(cq, cqe64, cqe, cqe_version);
}