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
struct ibv_flow {TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct ibv_destroy_flow {int /*<<< orphan*/  flow_handle; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROY_FLOW ; 
 int /*<<< orphan*/  IBV_INIT_CMD_EX (struct ibv_destroy_flow*,int,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct ibv_flow*) ; 
 int /*<<< orphan*/  memset (struct ibv_destroy_flow*,int /*<<< orphan*/ ,int) ; 
 int write (int /*<<< orphan*/ ,struct ibv_destroy_flow*,int) ; 

int ibv_cmd_destroy_flow(struct ibv_flow *flow_id)
{
	struct ibv_destroy_flow cmd;
	int ret = 0;

	memset(&cmd, 0, sizeof(cmd));
	IBV_INIT_CMD_EX(&cmd, sizeof(cmd), DESTROY_FLOW);
	cmd.flow_handle = flow_id->handle;

	if (write(flow_id->context->cmd_fd, &cmd, sizeof(cmd)) != sizeof(cmd))
		ret = errno;
	free(flow_id);
	return ret;
}