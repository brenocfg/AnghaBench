#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct mlx5_srq {int dummy; } ;
struct mlx5_resource {scalar_t__ rsn; int type; } ;
struct TYPE_3__ {int /*<<< orphan*/  srq; } ;
struct TYPE_4__ {TYPE_1__ qp; } ;
struct mlx5_qp {TYPE_2__ verbs_qp; } ;
struct mlx5_context {int dummy; } ;

/* Variables and functions */
 int CQ_OK ; 
 int CQ_POLL_ERR ; 
#define  MLX5_RSC_TYPE_QP 130 
#define  MLX5_RSC_TYPE_RWQ 129 
#define  MLX5_RSC_TYPE_XSRQ 128 
 struct mlx5_resource* mlx5_find_uidx (struct mlx5_context*,scalar_t__) ; 
 struct mlx5_qp* rsc_to_mqp (struct mlx5_resource*) ; 
 struct mlx5_srq* rsc_to_msrq (struct mlx5_resource*) ; 
 struct mlx5_srq* to_msrq (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int get_resp_ctx_v1(struct mlx5_context *mctx,
				  struct mlx5_resource **cur_rsc,
				  struct mlx5_srq **cur_srq,
				  uint32_t uidx, uint8_t *is_srq)
{
	struct mlx5_qp *mqp;

	if (!*cur_rsc || (uidx != (*cur_rsc)->rsn)) {
		*cur_rsc = mlx5_find_uidx(mctx, uidx);
		if (unlikely(!*cur_rsc))
			return CQ_POLL_ERR;
	}

	switch ((*cur_rsc)->type) {
	case MLX5_RSC_TYPE_QP:
		mqp = rsc_to_mqp(*cur_rsc);
		if (mqp->verbs_qp.qp.srq) {
			*cur_srq = to_msrq(mqp->verbs_qp.qp.srq);
			*is_srq = 1;
		}
		break;
	case MLX5_RSC_TYPE_XSRQ:
		*cur_srq = rsc_to_msrq(*cur_rsc);
		*is_srq = 1;
		break;
	case MLX5_RSC_TYPE_RWQ:
		break;
	default:
		return CQ_POLL_ERR;
	}

	return CQ_OK;
}