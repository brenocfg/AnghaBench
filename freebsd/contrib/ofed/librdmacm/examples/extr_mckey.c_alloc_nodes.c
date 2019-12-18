#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int id; int /*<<< orphan*/  cma_id; } ;
struct TYPE_6__ {TYPE_2__* nodes; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ENOMEM ; 
 int connections ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  port_space ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rdma_create_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ ) ; 
 TYPE_1__ test ; 

__attribute__((used)) static int alloc_nodes(void)
{
	int ret, i;

	test.nodes = malloc(sizeof *test.nodes * connections);
	if (!test.nodes) {
		printf("mckey: unable to allocate memory for test nodes\n");
		return -ENOMEM;
	}
	memset(test.nodes, 0, sizeof *test.nodes * connections);

	for (i = 0; i < connections; i++) {
		test.nodes[i].id = i;
		ret = rdma_create_id(test.channel, &test.nodes[i].cma_id,
				     &test.nodes[i], port_space);
		if (ret)
			goto err;
	}
	return 0;
err:
	while (--i >= 0)
		rdma_destroy_id(test.nodes[i].cma_id);
	free(test.nodes);
	return ret;
}