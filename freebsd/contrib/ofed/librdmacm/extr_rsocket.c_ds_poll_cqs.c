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
struct rsocket {size_t rmsg_tail; int rq_size; struct ds_qp* qp_list; scalar_t__ sqe_avail; scalar_t__ rqe_avail; struct ds_smsg* smsg_free; scalar_t__ sbuf; struct ds_rmsg* dmsg; } ;
struct ibv_wc {scalar_t__ status; int /*<<< orphan*/  wr_id; scalar_t__ byte_len; } ;
struct ibv_grh {int dummy; } ;
struct ds_smsg {struct ds_smsg* next; } ;
struct ds_rmsg {scalar_t__ length; scalar_t__ offset; struct ds_qp* qp; } ;
struct ds_qp {TYPE_1__* cm_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  recv_cq; } ;

/* Variables and functions */
 scalar_t__ IBV_WC_SUCCESS ; 
 struct ds_qp* ds_next_qp (struct ds_qp*) ; 
 int /*<<< orphan*/  ds_post_recv (struct rsocket*,struct ds_qp*,scalar_t__) ; 
 scalar_t__ ds_valid_recv (struct ds_qp*,struct ibv_wc*) ; 
 int ibv_poll_cq (int /*<<< orphan*/ ,int,struct ibv_wc*) ; 
 scalar_t__ rs_wr_data (int /*<<< orphan*/ ) ; 
 scalar_t__ rs_wr_is_recv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds_poll_cqs(struct rsocket *rs)
{
	struct ds_qp *qp;
	struct ds_smsg *smsg;
	struct ds_rmsg *rmsg;
	struct ibv_wc wc;
	int ret, cnt;

	if (!(qp = rs->qp_list))
		return;

	do {
		cnt = 0;
		do {
			ret = ibv_poll_cq(qp->cm_id->recv_cq, 1, &wc);
			if (ret <= 0) {
				qp = ds_next_qp(qp);
				continue;
			}

			if (rs_wr_is_recv(wc.wr_id)) {
				if (rs->rqe_avail && wc.status == IBV_WC_SUCCESS &&
				    ds_valid_recv(qp, &wc)) {
					rs->rqe_avail--;
					rmsg = &rs->dmsg[rs->rmsg_tail];
					rmsg->qp = qp;
					rmsg->offset = rs_wr_data(wc.wr_id);
					rmsg->length = wc.byte_len - sizeof(struct ibv_grh);
					if (++rs->rmsg_tail == rs->rq_size + 1)
						rs->rmsg_tail = 0;
				} else {
					ds_post_recv(rs, qp, rs_wr_data(wc.wr_id));
				}
			} else {
				smsg = (struct ds_smsg *) (rs->sbuf + rs_wr_data(wc.wr_id));
				smsg->next = rs->smsg_free;
				rs->smsg_free = smsg;
				rs->sqe_avail++;
			}

			qp = ds_next_qp(qp);
			if (!rs->rqe_avail && rs->sqe_avail) {
				rs->qp_list = qp;
				return;
			}
			cnt++;
		} while (qp != rs->qp_list);
	} while (cnt);
}