#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ai_port_space; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  STEP_CREATE_ID ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  channel ; 
 int connections ; 
 scalar_t__ dst_addr ; 
 int /*<<< orphan*/  end_perf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_4__ hints ; 
 TYPE_1__* nodes ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rdma_create_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_perf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_nodes(void)
{
	int ret, i;

	nodes = calloc(sizeof *nodes, connections);
	if (!nodes)
		return -ENOMEM;

	printf("creating id\n");
	start_time(STEP_CREATE_ID);
	for (i = 0; i < connections; i++) {
		start_perf(&nodes[i], STEP_CREATE_ID);
		if (dst_addr) {
			ret = rdma_create_id(channel, &nodes[i].id, &nodes[i],
					     hints.ai_port_space);
			if (ret)
				goto err;
		}
		end_perf(&nodes[i], STEP_CREATE_ID);
	}
	end_time(STEP_CREATE_ID);
	return 0;

err:
	while (--i >= 0)
		rdma_destroy_id(nodes[i].id);
	free(nodes);
	return ret;
}