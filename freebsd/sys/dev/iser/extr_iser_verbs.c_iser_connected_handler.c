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
struct rdma_cm_id {TYPE_1__* qp; struct iser_conn* context; } ;
struct iser_conn {int /*<<< orphan*/  up_cv; int /*<<< orphan*/  state; } ;
struct ib_qp_init_attr {int dummy; } ;
struct ib_qp_attr {int /*<<< orphan*/  dest_qp_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_CONN_UP ; 
 int /*<<< orphan*/  ISER_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_query_qp (TYPE_1__*,struct ib_qp_attr*,int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 

__attribute__((used)) static void
iser_connected_handler(struct rdma_cm_id *cma_id)
{
	struct iser_conn *iser_conn;
	struct ib_qp_attr attr;
	struct ib_qp_init_attr init_attr;

	iser_conn = cma_id->context;

	(void)ib_query_qp(cma_id->qp, &attr, ~0, &init_attr);

	ISER_INFO("remote qpn:%x my qpn:%x",
		  attr.dest_qp_num, cma_id->qp->qp_num);

	iser_conn->state = ISER_CONN_UP;

	cv_signal(&iser_conn->up_cv);
}