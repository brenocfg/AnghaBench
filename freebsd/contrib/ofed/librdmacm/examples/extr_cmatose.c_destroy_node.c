#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cmatest_node {TYPE_1__* cma_id; scalar_t__ pd; scalar_t__ mem; int /*<<< orphan*/  mr; scalar_t__* cq; } ;
struct TYPE_3__ {scalar_t__ qp; } ;

/* Variables and functions */
 size_t RECV_CQ_INDEX ; 
 size_t SEND_CQ_INDEX ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  ibv_dealloc_pd (scalar_t__) ; 
 int /*<<< orphan*/  ibv_dereg_mr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_cq (scalar_t__) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_1__*) ; 
 int /*<<< orphan*/  rdma_destroy_qp (TYPE_1__*) ; 

__attribute__((used)) static void destroy_node(struct cmatest_node *node)
{
	if (!node->cma_id)
		return;

	if (node->cma_id->qp)
		rdma_destroy_qp(node->cma_id);

	if (node->cq[SEND_CQ_INDEX])
		ibv_destroy_cq(node->cq[SEND_CQ_INDEX]);

	if (node->cq[RECV_CQ_INDEX])
		ibv_destroy_cq(node->cq[RECV_CQ_INDEX]);

	if (node->mem) {
		ibv_dereg_mr(node->mr);
		free(node->mem);
	}

	if (node->pd)
		ibv_dealloc_pd(node->pd);

	/* Destroy the RDMA ID after all device resources */
	rdma_destroy_id(node->cma_id);
}