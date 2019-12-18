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
struct cmatest_node {int /*<<< orphan*/  cma_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  connect_error () ; 
 int init_node (struct cmatest_node*) ; 
 int /*<<< orphan*/  is_sender ; 
 int /*<<< orphan*/  perror (char*) ; 
 int post_recvs (struct cmatest_node*) ; 
 int rdma_join_multicast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmatest_node*) ; 
 TYPE_1__ test ; 
 int verify_test_params (struct cmatest_node*) ; 

__attribute__((used)) static int addr_handler(struct cmatest_node *node)
{
	int ret;

	ret = verify_test_params(node);
	if (ret)
		goto err;

	ret = init_node(node);
	if (ret)
		goto err;

	if (!is_sender) {
		ret = post_recvs(node);
		if (ret)
			goto err;
	}

	ret = rdma_join_multicast(node->cma_id, test.dst_addr, node);
	if (ret) {
		perror("mckey: failure joining");
		goto err;
	}
	return 0;
err:
	connect_error();
	return ret;
}