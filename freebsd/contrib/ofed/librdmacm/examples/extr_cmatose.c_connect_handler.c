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
struct rdma_cm_id {struct cmatest_node* context; } ;
struct cmatest_node {struct rdma_cm_id* cma_id; } ;
struct TYPE_2__ {scalar_t__ conn_index; struct cmatest_node* nodes; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  connect_error () ; 
 scalar_t__ connections ; 
 int init_node (struct cmatest_node*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int post_recvs (struct cmatest_node*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rdma_accept (struct rdma_cm_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_reject (struct rdma_cm_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ test ; 

__attribute__((used)) static int connect_handler(struct rdma_cm_id *cma_id)
{
	struct cmatest_node *node;
	int ret;

	if (test.conn_index == connections) {
		ret = -ENOMEM;
		goto err1;
	}
	node = &test.nodes[test.conn_index++];

	node->cma_id = cma_id;
	cma_id->context = node;

	ret = init_node(node);
	if (ret)
		goto err2;

	ret = post_recvs(node);
	if (ret)
		goto err2;

	ret = rdma_accept(node->cma_id, NULL);
	if (ret) {
		perror("cmatose: failure accepting");
		goto err2;
	}
	return 0;

err2:
	node->cma_id = NULL;
	connect_error();
err1:
	printf("cmatose: failing connection request\n");
	rdma_reject(cma_id, NULL, 0);
	return ret;
}