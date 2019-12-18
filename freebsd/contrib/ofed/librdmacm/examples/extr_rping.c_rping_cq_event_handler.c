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
struct rping_cb {int /*<<< orphan*/  sem; int /*<<< orphan*/  state; int /*<<< orphan*/  rq_wr; int /*<<< orphan*/  qp; int /*<<< orphan*/  server; int /*<<< orphan*/  cq; } ;
struct ibv_wc {scalar_t__ status; int opcode; } ;
struct ibv_recv_wr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (char*) ; 
 int /*<<< orphan*/  ERROR ; 
#define  IBV_WC_RDMA_READ 131 
#define  IBV_WC_RDMA_WRITE 130 
#define  IBV_WC_RECV 129 
#define  IBV_WC_SEND 128 
 scalar_t__ IBV_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  RDMA_READ_COMPLETE ; 
 int /*<<< orphan*/  RDMA_WRITE_COMPLETE ; 
 int client_recv (struct rping_cb*,struct ibv_wc*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int ibv_poll_cq (int /*<<< orphan*/ ,int,struct ibv_wc*) ; 
 int ibv_post_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ibv_recv_wr**) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int server_recv (struct rping_cb*,struct ibv_wc*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int rping_cq_event_handler(struct rping_cb *cb)
{
	struct ibv_wc wc;
	struct ibv_recv_wr *bad_wr;
	int ret;
	int flushed = 0;

	while ((ret = ibv_poll_cq(cb->cq, 1, &wc)) == 1) {
		ret = 0;

		if (wc.status) {
			if (wc.status == IBV_WC_WR_FLUSH_ERR) {
				flushed = 1;
				continue;

			}
			fprintf(stderr,
				"cq completion failed status %d\n",
				wc.status);
			ret = -1;
			goto error;
		}

		switch (wc.opcode) {
		case IBV_WC_SEND:
			DEBUG_LOG("send completion\n");
			break;

		case IBV_WC_RDMA_WRITE:
			DEBUG_LOG("rdma write completion\n");
			cb->state = RDMA_WRITE_COMPLETE;
			sem_post(&cb->sem);
			break;

		case IBV_WC_RDMA_READ:
			DEBUG_LOG("rdma read completion\n");
			cb->state = RDMA_READ_COMPLETE;
			sem_post(&cb->sem);
			break;

		case IBV_WC_RECV:
			DEBUG_LOG("recv completion\n");
			ret = cb->server ? server_recv(cb, &wc) :
					   client_recv(cb, &wc);
			if (ret) {
				fprintf(stderr, "recv wc error: %d\n", ret);
				goto error;
			}

			ret = ibv_post_recv(cb->qp, &cb->rq_wr, &bad_wr);
			if (ret) {
				fprintf(stderr, "post recv error: %d\n", ret);
				goto error;
			}
			sem_post(&cb->sem);
			break;

		default:
			DEBUG_LOG("unknown!!!!! completion\n");
			ret = -1;
			goto error;
		}
	}
	if (ret) {
		fprintf(stderr, "poll error %d\n", ret);
		goto error;
	}
	return flushed;

error:
	cb->state = ERROR;
	sem_post(&cb->sem);
	return ret;
}