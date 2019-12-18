#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; int /*<<< orphan*/  srq_limit; } ;
struct ibv_srq_init_attr {TYPE_2__ attr; } ;
struct ibv_srq {TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct ibv_pd {TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct ibv_create_srq_resp_v5 {int dummy; } ;
struct ibv_create_srq_resp {int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; int /*<<< orphan*/  srq_handle; } ;
struct ibv_create_srq {uintptr_t user_handle; int /*<<< orphan*/  srq_limit; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; int /*<<< orphan*/  pd_handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_SRQ ; 
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_create_srq*,size_t,int /*<<< orphan*/ ,struct ibv_create_srq_resp*,size_t) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_create_srq_resp*,size_t) ; 
 int abi_ver ; 
 int errno ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t) ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_create_srq*,size_t) ; 

int ibv_cmd_create_srq(struct ibv_pd *pd,
		       struct ibv_srq *srq, struct ibv_srq_init_attr *attr,
		       struct ibv_create_srq *cmd, size_t cmd_size,
		       struct ibv_create_srq_resp *resp, size_t resp_size)
{
	IBV_INIT_CMD_RESP(cmd, cmd_size, CREATE_SRQ, resp, resp_size);
	cmd->user_handle = (uintptr_t) srq;
	cmd->pd_handle 	 = pd->handle;
	cmd->max_wr      = attr->attr.max_wr;
	cmd->max_sge     = attr->attr.max_sge;
	cmd->srq_limit   = attr->attr.srq_limit;

	if (write(pd->context->cmd_fd, cmd, cmd_size) != cmd_size)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(resp, resp_size);

	srq->handle  = resp->srq_handle;
	srq->context = pd->context;

	if (abi_ver > 5) {
		attr->attr.max_wr = resp->max_wr;
		attr->attr.max_sge = resp->max_sge;
	} else {
		struct ibv_create_srq_resp_v5 *resp_v5 =
			(struct ibv_create_srq_resp_v5 *) resp;

		memmove((void *) resp + sizeof *resp,
			(void *) resp_v5 + sizeof *resp_v5,
			resp_size - sizeof *resp);
	}

	return 0;
}