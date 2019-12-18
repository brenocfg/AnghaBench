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
struct rdma_cqe_responder {int /*<<< orphan*/  rq_cons; } ;
struct TYPE_2__ {scalar_t__ wqe_cons; } ;
struct qlnxr_qp {TYPE_1__ rq; } ;
struct qlnxr_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  consume_cqe (struct qlnxr_cq*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
try_consume_resp_cqe(struct qlnxr_cq *cq,
	struct qlnxr_qp *qp,
	struct rdma_cqe_responder *resp,
	int *update)
{
	if (le16_to_cpu(resp->rq_cons) == qp->rq.wqe_cons) {
		consume_cqe(cq);
		*update |= 1;
	}
}