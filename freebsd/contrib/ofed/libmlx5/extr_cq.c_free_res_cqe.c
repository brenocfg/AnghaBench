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
struct mlx5_srq {int dummy; } ;
struct mlx5_cqe64 {int /*<<< orphan*/  wqe_counter; int /*<<< orphan*/  srqn_uidx; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ is_equal_rsn (struct mlx5_cqe64*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_equal_uidx (struct mlx5_cqe64*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_responder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_srq_wqe (struct mlx5_srq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dv_get_cqe_opcode (struct mlx5_cqe64*) ; 

__attribute__((used)) static inline int free_res_cqe(struct mlx5_cqe64 *cqe64, uint32_t rsn,
			       struct mlx5_srq *srq, int cqe_version)
{
	if (cqe_version) {
		if (is_equal_uidx(cqe64, rsn)) {
			if (srq && is_responder(mlx5dv_get_cqe_opcode(cqe64)))
				mlx5_free_srq_wqe(srq,
						  be16toh(cqe64->wqe_counter));
			return 1;
		}
	} else {
		if (is_equal_rsn(cqe64, rsn)) {
			if (srq && (be32toh(cqe64->srqn_uidx) & 0xffffff))
				mlx5_free_srq_wqe(srq,
						  be16toh(cqe64->wqe_counter));
			return 1;
		}
	}

	return 0;
}