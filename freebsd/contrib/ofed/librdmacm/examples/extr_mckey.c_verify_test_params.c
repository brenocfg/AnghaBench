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
struct ibv_port_attr {int active_mtu; } ;
struct cmatest_node {TYPE_1__* cma_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_num; int /*<<< orphan*/  verbs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ibv_query_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibv_port_attr*) ; 
 scalar_t__ message_count ; 
 int message_size ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int verify_test_params(struct cmatest_node *node)
{
	struct ibv_port_attr port_attr;
	int ret;

	ret = ibv_query_port(node->cma_id->verbs, node->cma_id->port_num,
			     &port_attr);
	if (ret)
		return ret;

	if (message_count && message_size > (1 << (port_attr.active_mtu + 7))) {
		printf("mckey: message_size %d is larger than active mtu %d\n",
		       message_size, 1 << (port_attr.active_mtu + 7));
		return -EINVAL;
	}

	return 0;
}