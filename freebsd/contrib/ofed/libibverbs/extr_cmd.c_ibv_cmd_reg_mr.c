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
typedef  int /*<<< orphan*/  uint64_t ;
struct ibv_reg_mr_resp {int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; int /*<<< orphan*/  mr_handle; } ;
struct ibv_reg_mr {uintptr_t start; size_t length; int access_flags; int /*<<< orphan*/  pd_handle; int /*<<< orphan*/  hca_va; } ;
struct ibv_pd {TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct ibv_mr {TYPE_1__* context; int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_reg_mr*,size_t,int /*<<< orphan*/ ,struct ibv_reg_mr_resp*,size_t) ; 
 int /*<<< orphan*/  REG_MR ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_reg_mr_resp*,size_t) ; 
 int errno ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_reg_mr*,size_t) ; 

int ibv_cmd_reg_mr(struct ibv_pd *pd, void *addr, size_t length,
		   uint64_t hca_va, int access,
		   struct ibv_mr *mr, struct ibv_reg_mr *cmd,
		   size_t cmd_size,
		   struct ibv_reg_mr_resp *resp, size_t resp_size)
{

	IBV_INIT_CMD_RESP(cmd, cmd_size, REG_MR, resp, resp_size);

	cmd->start 	  = (uintptr_t) addr;
	cmd->length 	  = length;
	cmd->hca_va 	  = hca_va;
	cmd->pd_handle 	  = pd->handle;
	cmd->access_flags = access;

	if (write(pd->context->cmd_fd, cmd, cmd_size) != cmd_size)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(resp, resp_size);

	mr->handle  = resp->mr_handle;
	mr->lkey    = resp->lkey;
	mr->rkey    = resp->rkey;
	mr->context = pd->context;

	return 0;
}