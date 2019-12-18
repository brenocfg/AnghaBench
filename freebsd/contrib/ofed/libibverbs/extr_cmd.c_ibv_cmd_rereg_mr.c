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
typedef  int uint32_t ;
struct ibv_rereg_mr_resp {int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; } ;
struct ibv_rereg_mr {int flags; uintptr_t start; size_t length; int access_flags; int /*<<< orphan*/  pd_handle; int /*<<< orphan*/  hca_va; int /*<<< orphan*/  mr_handle; } ;
struct ibv_pd {TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct ibv_mr {TYPE_1__* context; int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_rereg_mr*,size_t,int /*<<< orphan*/ ,struct ibv_rereg_mr_resp*,size_t) ; 
 int IBV_REREG_MR_CHANGE_PD ; 
 int /*<<< orphan*/  REREG_MR ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_rereg_mr_resp*,size_t) ; 
 int errno ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_rereg_mr*,size_t) ; 

int ibv_cmd_rereg_mr(struct ibv_mr *mr, uint32_t flags, void *addr,
		     size_t length, uint64_t hca_va, int access,
		     struct ibv_pd *pd, struct ibv_rereg_mr *cmd,
		     size_t cmd_sz, struct ibv_rereg_mr_resp *resp,
		     size_t resp_sz)
{
	IBV_INIT_CMD_RESP(cmd, cmd_sz, REREG_MR, resp, resp_sz);

	cmd->mr_handle	  = mr->handle;
	cmd->flags	  = flags;
	cmd->start	  = (uintptr_t)addr;
	cmd->length	  = length;
	cmd->hca_va	  = hca_va;
	cmd->pd_handle	  = (flags & IBV_REREG_MR_CHANGE_PD) ? pd->handle : 0;
	cmd->access_flags = access;

	if (write(mr->context->cmd_fd, cmd, cmd_sz) != cmd_sz)
		return errno;

	(void)VALGRIND_MAKE_MEM_DEFINED(resp, resp_sz);

	mr->lkey    = resp->lkey;
	mr->rkey    = resp->rkey;
	if (flags & IBV_REREG_MR_CHANGE_PD)
		mr->context = pd->context;

	return 0;
}