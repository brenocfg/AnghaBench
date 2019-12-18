#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  STEP_DESTROY ; 
 int connections ; 
 int /*<<< orphan*/  end_perf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_time (int /*<<< orphan*/ ) ; 
 TYPE_1__* nodes ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rdma_destroy_id (scalar_t__) ; 
 int /*<<< orphan*/  start_perf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_nodes(void)
{
	int i;

	printf("destroying id\n");
	start_time(STEP_DESTROY);
	for (i = 0; i < connections; i++) {
		start_perf(&nodes[i], STEP_DESTROY);
		if (nodes[i].id)
			rdma_destroy_id(nodes[i].id);
		end_perf(&nodes[i], STEP_DESTROY);
	}
	end_time(STEP_DESTROY);
}