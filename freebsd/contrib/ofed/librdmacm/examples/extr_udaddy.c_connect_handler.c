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
struct rdma_conn_param {int /*<<< orphan*/  qp_num; } ;
struct rdma_cm_id {TYPE_1__* qp; struct cmatest_node* context; } ;
struct cmatest_node {int connected; struct rdma_cm_id* cma_id; } ;
struct TYPE_4__ {scalar_t__ conn_index; int /*<<< orphan*/  connects_left; struct cmatest_node* nodes; } ;
struct TYPE_3__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  connect_error () ; 
 scalar_t__ connections ; 
 int init_node (struct cmatest_node*) ; 
 int /*<<< orphan*/  memset (struct rdma_conn_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int post_recvs (struct cmatest_node*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rdma_accept (struct rdma_cm_id*,struct rdma_conn_param*) ; 
 int /*<<< orphan*/  rdma_reject (struct rdma_cm_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ test ; 
 int verify_test_params (struct cmatest_node*) ; 

__attribute__((used)) static int connect_handler(struct rdma_cm_id *cma_id)
{
	struct cmatest_node *node;
	struct rdma_conn_param conn_param;
	int ret;

	if (test.conn_index == connections) {
		ret = -ENOMEM;
		goto err1;
	}
	node = &test.nodes[test.conn_index++];

	node->cma_id = cma_id;
	cma_id->context = node;

	ret = verify_test_params(node);
	if (ret)
		goto err2;

	ret = init_node(node);
	if (ret)
		goto err2;

	ret = post_recvs(node);
	if (ret)
		goto err2;

	memset(&conn_param, 0, sizeof conn_param);
	conn_param.qp_num = node->cma_id->qp->qp_num;
	ret = rdma_accept(node->cma_id, &conn_param);
	if (ret) {
		perror("udaddy: failure accepting");
		goto err2;
	}
	node->connected = 1;
	test.connects_left--;
	return 0;

err2:
	node->cma_id = NULL;
	connect_error();
err1:
	printf("udaddy: failing connection request\n");
	rdma_reject(cma_id, NULL, 0);
	return ret;
}