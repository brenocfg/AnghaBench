#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct ibv_sge {int dummy; } ;
struct TYPE_19__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  swap; int /*<<< orphan*/  compare_add; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_16__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_14__ {int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; TYPE_1__* ah; } ;
struct TYPE_20__ {TYPE_8__ atomic; TYPE_5__ rdma; TYPE_3__ ud; } ;
struct ibv_send_wr {int num_sge; int opcode; struct ibv_send_wr* next; int /*<<< orphan*/  sg_list; TYPE_9__ wr; int /*<<< orphan*/  imm_data; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  wr_id; } ;
struct ibv_qp {scalar_t__ qp_type; TYPE_10__* context; int /*<<< orphan*/  handle; } ;
struct ibv_post_send_resp {unsigned int bad_wr; } ;
struct ibv_post_send {unsigned int wr_count; unsigned int sge_count; int wqe_size; int /*<<< orphan*/  qp_handle; } ;
struct TYPE_17__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  swap; int /*<<< orphan*/  compare_add; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_15__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  ah; } ;
struct TYPE_18__ {TYPE_6__ atomic; TYPE_4__ rdma; TYPE_2__ ud; } ;
struct ibv_kern_send_wr {int num_sge; int opcode; TYPE_7__ wr; int /*<<< orphan*/  imm_data; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  wr_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  handle; } ;
struct TYPE_11__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_post_send*,int,int /*<<< orphan*/ ,struct ibv_post_send_resp*,int) ; 
 scalar_t__ IBV_QPT_UD ; 
#define  IBV_WR_ATOMIC_CMP_AND_SWP 132 
#define  IBV_WR_ATOMIC_FETCH_AND_ADD 131 
#define  IBV_WR_RDMA_READ 130 
#define  IBV_WR_RDMA_WRITE 129 
#define  IBV_WR_RDMA_WRITE_WITH_IMM 128 
 int /*<<< orphan*/  POST_SEND ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_post_send_resp*,int) ; 
 struct ibv_post_send* alloca (int) ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (struct ibv_sge*,int /*<<< orphan*/ ,int) ; 
 int write (int /*<<< orphan*/ ,struct ibv_post_send*,int) ; 

int ibv_cmd_post_send(struct ibv_qp *ibqp, struct ibv_send_wr *wr,
		      struct ibv_send_wr **bad_wr)
{
	struct ibv_post_send     *cmd;
	struct ibv_post_send_resp resp;
	struct ibv_send_wr       *i;
	struct ibv_kern_send_wr  *n, *tmp;
	struct ibv_sge           *s;
	unsigned                  wr_count = 0;
	unsigned                  sge_count = 0;
	int                       cmd_size;
	int                       ret = 0;

	for (i = wr; i; i = i->next) {
		wr_count++;
		sge_count += i->num_sge;
	}

	cmd_size = sizeof *cmd + wr_count * sizeof *n + sge_count * sizeof *s;
	cmd  = alloca(cmd_size);

	IBV_INIT_CMD_RESP(cmd, cmd_size, POST_SEND, &resp, sizeof resp);
	cmd->qp_handle = ibqp->handle;
	cmd->wr_count  = wr_count;
	cmd->sge_count = sge_count;
	cmd->wqe_size  = sizeof *n;

	n = (struct ibv_kern_send_wr *) ((void *) cmd + sizeof *cmd);
	s = (struct ibv_sge *) (n + wr_count);

	tmp = n;
	for (i = wr; i; i = i->next) {
		tmp->wr_id 	= i->wr_id;
		tmp->num_sge 	= i->num_sge;
		tmp->opcode 	= i->opcode;
		tmp->send_flags = i->send_flags;
		tmp->imm_data 	= i->imm_data;
		if (ibqp->qp_type == IBV_QPT_UD) {
			tmp->wr.ud.ah 	       = i->wr.ud.ah->handle;
			tmp->wr.ud.remote_qpn  = i->wr.ud.remote_qpn;
			tmp->wr.ud.remote_qkey = i->wr.ud.remote_qkey;
		} else {
			switch (i->opcode) {
			case IBV_WR_RDMA_WRITE:
			case IBV_WR_RDMA_WRITE_WITH_IMM:
			case IBV_WR_RDMA_READ:
				tmp->wr.rdma.remote_addr =
					i->wr.rdma.remote_addr;
				tmp->wr.rdma.rkey = i->wr.rdma.rkey;
				break;
			case IBV_WR_ATOMIC_CMP_AND_SWP:
			case IBV_WR_ATOMIC_FETCH_AND_ADD:
				tmp->wr.atomic.remote_addr =
					i->wr.atomic.remote_addr;
				tmp->wr.atomic.compare_add =
					i->wr.atomic.compare_add;
				tmp->wr.atomic.swap = i->wr.atomic.swap;
				tmp->wr.atomic.rkey = i->wr.atomic.rkey;
				break;
			default:
				break;
			}
		}

		if (tmp->num_sge) {
			memcpy(s, i->sg_list, tmp->num_sge * sizeof *s);
			s += tmp->num_sge;
		}

		tmp++;
	}

	resp.bad_wr = 0;
	if (write(ibqp->context->cmd_fd, cmd, cmd_size) != cmd_size)
		ret = errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(&resp, sizeof resp);

	wr_count = resp.bad_wr;
	if (wr_count) {
		i = wr;
		while (--wr_count)
			i = i->next;
		*bad_wr = i;
	} else if (ret)
		*bad_wr = wr;

	return ret;
}