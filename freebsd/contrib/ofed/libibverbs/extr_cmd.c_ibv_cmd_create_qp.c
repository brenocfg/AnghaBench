#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_sge; } ;
struct ibv_qp_init_attr {TYPE_5__ cap; TYPE_3__* srq; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_all; TYPE_2__* recv_cq; TYPE_1__* send_cq; } ;
struct ibv_qp {TYPE_4__* context; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  handle; } ;
struct ibv_pd {TYPE_4__* context; int /*<<< orphan*/  handle; } ;
struct ibv_create_qp_resp_v4 {int dummy; } ;
struct ibv_create_qp_resp_v3 {int dummy; } ;
struct ibv_create_qp_resp {int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  qpn; int /*<<< orphan*/  qp_handle; } ;
struct ibv_create_qp {uintptr_t user_handle; int is_srq; scalar_t__ reserved; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_all; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  srq_handle; int /*<<< orphan*/  recv_cq_handle; int /*<<< orphan*/  send_cq_handle; int /*<<< orphan*/  pd_handle; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmd_fd; } ;
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_QP ; 
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_create_qp*,size_t,int /*<<< orphan*/ ,struct ibv_create_qp_resp*,size_t) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_create_qp_resp*,size_t) ; 
 int abi_ver ; 
 int errno ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t) ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_create_qp*,size_t) ; 

int ibv_cmd_create_qp(struct ibv_pd *pd,
		      struct ibv_qp *qp, struct ibv_qp_init_attr *attr,
		      struct ibv_create_qp *cmd, size_t cmd_size,
		      struct ibv_create_qp_resp *resp, size_t resp_size)
{
	IBV_INIT_CMD_RESP(cmd, cmd_size, CREATE_QP, resp, resp_size);

	cmd->user_handle     = (uintptr_t) qp;
	cmd->pd_handle       = pd->handle;
	cmd->send_cq_handle  = attr->send_cq->handle;
	cmd->recv_cq_handle  = attr->recv_cq->handle;
	cmd->srq_handle      = attr->srq ? attr->srq->handle : 0;
	cmd->max_send_wr     = attr->cap.max_send_wr;
	cmd->max_recv_wr     = attr->cap.max_recv_wr;
	cmd->max_send_sge    = attr->cap.max_send_sge;
	cmd->max_recv_sge    = attr->cap.max_recv_sge;
	cmd->max_inline_data = attr->cap.max_inline_data;
	cmd->sq_sig_all	     = attr->sq_sig_all;
	cmd->qp_type 	     = attr->qp_type;
	cmd->is_srq 	     = !!attr->srq;
	cmd->reserved	     = 0;

	if (write(pd->context->cmd_fd, cmd, cmd_size) != cmd_size)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(resp, resp_size);

	qp->handle 		  = resp->qp_handle;
	qp->qp_num 		  = resp->qpn;
	qp->context		  = pd->context;

	if (abi_ver > 3) {
		attr->cap.max_recv_sge    = resp->max_recv_sge;
		attr->cap.max_send_sge    = resp->max_send_sge;
		attr->cap.max_recv_wr     = resp->max_recv_wr;
		attr->cap.max_send_wr     = resp->max_send_wr;
		attr->cap.max_inline_data = resp->max_inline_data;
	}

	if (abi_ver == 4) {
		struct ibv_create_qp_resp_v4 *resp_v4 =
			(struct ibv_create_qp_resp_v4 *) resp;

		memmove((void *) resp + sizeof *resp,
			(void *) resp_v4 + sizeof *resp_v4,
			resp_size - sizeof *resp);
	} else if (abi_ver <= 3) {
		struct ibv_create_qp_resp_v3 *resp_v3 =
			(struct ibv_create_qp_resp_v3 *) resp;

		memmove((void *) resp + sizeof *resp,
			(void *) resp_v3 + sizeof *resp_v3,
			resp_size - sizeof *resp);
	}

	return 0;
}