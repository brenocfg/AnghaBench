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
struct ibv_create_cq_resp {int /*<<< orphan*/  cqe; int /*<<< orphan*/  cq_handle; } ;
struct ibv_create_cq {uintptr_t user_handle; int cqe; int comp_vector; int comp_channel; scalar_t__ reserved; } ;
struct ibv_cq {struct ibv_context* context; int /*<<< orphan*/  cqe; int /*<<< orphan*/  handle; } ;
struct ibv_context {int /*<<< orphan*/  cmd_fd; } ;
struct ibv_comp_channel {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_CQ ; 
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_create_cq*,size_t,int /*<<< orphan*/ ,struct ibv_create_cq_resp*,size_t) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_create_cq_resp*,size_t) ; 
 int errno ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_create_cq*,size_t) ; 

int ibv_cmd_create_cq(struct ibv_context *context, int cqe,
		      struct ibv_comp_channel *channel,
		      int comp_vector, struct ibv_cq *cq,
		      struct ibv_create_cq *cmd, size_t cmd_size,
		      struct ibv_create_cq_resp *resp, size_t resp_size)
{
	IBV_INIT_CMD_RESP(cmd, cmd_size, CREATE_CQ, resp, resp_size);
	cmd->user_handle   = (uintptr_t) cq;
	cmd->cqe           = cqe;
	cmd->comp_vector   = comp_vector;
	cmd->comp_channel  = channel ? channel->fd : -1;
	cmd->reserved      = 0;

	if (write(context->cmd_fd, cmd, cmd_size) != cmd_size)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(resp, resp_size);

	cq->handle  = resp->cq_handle;
	cq->cqe     = resp->cqe;
	cq->context = context;

	return 0;
}