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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct mlx5_srq {int dummy; } ;
struct mlx5_resource {int dummy; } ;
struct mlx5_context {int dummy; } ;

/* Variables and functions */
 int get_qp_ctx (struct mlx5_context*,struct mlx5_resource**,scalar_t__) ; 
 int get_resp_ctx_v1 (struct mlx5_context*,struct mlx5_resource**,struct mlx5_srq**,scalar_t__,int*) ; 
 int get_srq_ctx (struct mlx5_context*,struct mlx5_srq**,scalar_t__) ; 

__attribute__((used)) static inline int get_cur_rsc(struct mlx5_context *mctx,
			      int cqe_ver,
			      uint32_t qpn,
			      uint32_t srqn_uidx,
			      struct mlx5_resource **cur_rsc,
			      struct mlx5_srq **cur_srq,
			      uint8_t *is_srq)
{
	int err;

	if (cqe_ver) {
		err = get_resp_ctx_v1(mctx, cur_rsc, cur_srq, srqn_uidx,
				      is_srq);
	} else {
		if (srqn_uidx) {
			*is_srq = 1;
			err = get_srq_ctx(mctx, cur_srq, srqn_uidx);
		} else {
			err = get_qp_ctx(mctx, cur_rsc, qpn);
		}
	}

	return err;

}