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
struct TYPE_3__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  max_post; } ;
struct mlx5_qp {int /*<<< orphan*/  max_inline_data; TYPE_1__ sq; scalar_t__ rss_qp; } ;
struct ibv_query_qp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_send_wr; } ;
struct ibv_qp_init_attr {TYPE_2__ cap; } ;
struct ibv_qp_attr {TYPE_2__ cap; } ;
struct ibv_qp {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int ENOSYS ; 
 int ibv_cmd_query_qp (struct ibv_qp*,struct ibv_qp_attr*,int,struct ibv_qp_init_attr*,struct ibv_query_qp*,int) ; 
 struct mlx5_qp* to_mqp (struct ibv_qp*) ; 

int mlx5_query_qp(struct ibv_qp *ibqp, struct ibv_qp_attr *attr,
		  int attr_mask, struct ibv_qp_init_attr *init_attr)
{
	struct ibv_query_qp cmd;
	struct mlx5_qp *qp = to_mqp(ibqp);
	int ret;

	if (qp->rss_qp)
		return ENOSYS;

	ret = ibv_cmd_query_qp(ibqp, attr, attr_mask, init_attr, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	init_attr->cap.max_send_wr     = qp->sq.max_post;
	init_attr->cap.max_send_sge    = qp->sq.max_gs;
	init_attr->cap.max_inline_data = qp->max_inline_data;

	attr->cap = init_attr->cap;

	return 0;
}