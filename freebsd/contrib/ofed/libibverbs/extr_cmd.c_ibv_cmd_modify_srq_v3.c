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
struct ibv_srq_attr {int /*<<< orphan*/  srq_limit; int /*<<< orphan*/  max_wr; } ;
struct ibv_srq {TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct ibv_modify_srq_v3 {int attr_mask; scalar_t__ reserved; scalar_t__ max_sge; int /*<<< orphan*/  srq_limit; int /*<<< orphan*/  max_wr; int /*<<< orphan*/  srq_handle; int /*<<< orphan*/  driver_data; } ;
struct ibv_modify_srq {int /*<<< orphan*/  driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_INIT_CMD (struct ibv_modify_srq_v3*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODIFY_SRQ ; 
 struct ibv_modify_srq_v3* alloca (size_t) ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_modify_srq_v3*,size_t) ; 

__attribute__((used)) static int ibv_cmd_modify_srq_v3(struct ibv_srq *srq,
				 struct ibv_srq_attr *srq_attr,
				 int srq_attr_mask,
				 struct ibv_modify_srq *new_cmd,
				 size_t new_cmd_size)
{
	struct ibv_modify_srq_v3 *cmd;
	size_t cmd_size;

	cmd_size = sizeof *cmd + new_cmd_size - sizeof *new_cmd;
	cmd      = alloca(cmd_size);
	memcpy(cmd->driver_data, new_cmd->driver_data, new_cmd_size - sizeof *new_cmd);

	IBV_INIT_CMD(cmd, cmd_size, MODIFY_SRQ);

	cmd->srq_handle	= srq->handle;
	cmd->attr_mask	= srq_attr_mask;
	cmd->max_wr	= srq_attr->max_wr;
	cmd->srq_limit	= srq_attr->srq_limit;
	cmd->max_sge	= 0;
	cmd->reserved	= 0;

	if (write(srq->context->cmd_fd, cmd, cmd_size) != cmd_size)
		return errno;

	return 0;
}