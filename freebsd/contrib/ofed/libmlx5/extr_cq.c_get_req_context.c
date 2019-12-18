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
typedef  scalar_t__ uint32_t ;
struct mlx5_resource {scalar_t__ rsn; } ;
struct mlx5_qp {int dummy; } ;
struct mlx5_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ mlx5_find_qp (struct mlx5_context*,scalar_t__) ; 
 struct mlx5_resource* mlx5_find_uidx (struct mlx5_context*,scalar_t__) ; 
 struct mlx5_qp* rsc_to_mqp (struct mlx5_resource*) ; 

__attribute__((used)) static inline struct mlx5_qp *get_req_context(struct mlx5_context *mctx,
					      struct mlx5_resource **cur_rsc,
					      uint32_t rsn, int cqe_ver)
{
	if (!*cur_rsc || (rsn != (*cur_rsc)->rsn))
		*cur_rsc = cqe_ver ? mlx5_find_uidx(mctx, rsn) :
				      (struct mlx5_resource *)mlx5_find_qp(mctx, rsn);

	return rsc_to_mqp(*cur_rsc);
}