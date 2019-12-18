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
struct rdma_conn_param {int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; } ;
struct cmatest_node {int /*<<< orphan*/  cma_id; } ;
struct TYPE_4__ {TYPE_1__* rai; } ;
struct TYPE_3__ {int /*<<< orphan*/  ai_connect_len; int /*<<< orphan*/  ai_connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  connect_error () ; 
 int init_node (struct cmatest_node*) ; 
 int /*<<< orphan*/  memset (struct rdma_conn_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int post_recvs (struct cmatest_node*) ; 
 int rdma_connect (int /*<<< orphan*/ ,struct rdma_conn_param*) ; 
 TYPE_2__ test ; 
 int verify_test_params (struct cmatest_node*) ; 

__attribute__((used)) static int route_handler(struct cmatest_node *node)
{
	struct rdma_conn_param conn_param;
	int ret;

	ret = verify_test_params(node);
	if (ret)
		goto err;

	ret = init_node(node);
	if (ret)
		goto err;

	ret = post_recvs(node);
	if (ret)
		goto err;

	memset(&conn_param, 0, sizeof conn_param);
	conn_param.private_data = test.rai->ai_connect;
	conn_param.private_data_len = test.rai->ai_connect_len;
	ret = rdma_connect(node->cma_id, &conn_param);
	if (ret) {
		perror("udaddy: failure connecting");
		goto err;
	}
	return 0;
err:
	connect_error();
	return ret;
}