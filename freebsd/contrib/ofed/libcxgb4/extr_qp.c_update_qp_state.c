#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ibv_query_qp {int dummy; } ;
struct ibv_qp_init_attr {int dummy; } ;
struct ibv_qp_attr {int /*<<< orphan*/  qp_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct c4iw_qp {TYPE_1__ ibv_qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_QP_STATE ; 
 int /*<<< orphan*/  assert (int) ; 
 int ibv_cmd_query_qp (TYPE_1__*,struct ibv_qp_attr*,int /*<<< orphan*/ ,struct ibv_qp_init_attr*,struct ibv_query_qp*,int) ; 

__attribute__((used)) static void update_qp_state(struct c4iw_qp *qhp)
{
	struct ibv_query_qp cmd;
	struct ibv_qp_attr attr;
	struct ibv_qp_init_attr iattr;
	int ret;

	ret = ibv_cmd_query_qp(&qhp->ibv_qp, &attr, IBV_QP_STATE, &iattr,
			       &cmd, sizeof cmd);
	assert(!ret);
	if (!ret)
		qhp->ibv_qp.state = attr.qp_state;
}