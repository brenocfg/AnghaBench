#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cmatest_node {int /*<<< orphan*/  cma_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_OPTION_ID ; 
 int /*<<< orphan*/  RDMA_OPTION_ID_TOS ; 
 int /*<<< orphan*/  connect_error () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int rdma_resolve_route (int /*<<< orphan*/ ,int) ; 
 int rdma_set_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ set_tos ; 
 int /*<<< orphan*/  tos ; 

__attribute__((used)) static int addr_handler(struct cmatest_node *node)
{
	int ret;

	if (set_tos) {
		ret = rdma_set_option(node->cma_id, RDMA_OPTION_ID,
				      RDMA_OPTION_ID_TOS, &tos, sizeof tos);
		if (ret)
			perror("cmatose: set TOS option failed");
	}

	ret = rdma_resolve_route(node->cma_id, 2000);
	if (ret) {
		perror("cmatose: resolve route failed");
		connect_error();
	}
	return ret;
}