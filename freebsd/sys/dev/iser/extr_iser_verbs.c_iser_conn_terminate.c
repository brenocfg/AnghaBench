#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* wr_id; int /*<<< orphan*/  opcode; } ;
struct TYPE_6__ {int /*<<< orphan*/  flush_lock; int /*<<< orphan*/  flush_cv; TYPE_2__ recv; TYPE_2__ send; } ;
struct ib_conn {TYPE_1__ beacon; int /*<<< orphan*/ * qp; scalar_t__ cma_id; } ;
struct iser_conn {int /*<<< orphan*/  state; struct ib_conn ib_conn; } ;
struct ib_send_wr {int dummy; } ;
struct ib_recv_wr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  close_conns_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_SEND ; 
 void* ISER_BEACON_WRID ; 
 int /*<<< orphan*/  ISER_CONN_TERMINATING ; 
 int /*<<< orphan*/  ISER_CONN_UP ; 
 int /*<<< orphan*/  ISER_DBG (char*,struct iser_conn*) ; 
 int /*<<< orphan*/  ISER_ERR (char*,...) ; 
 int /*<<< orphan*/  ISER_INFO (char*,struct iser_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISER_WARN (char*) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ib_post_recv (int /*<<< orphan*/ *,TYPE_2__*,struct ib_recv_wr**) ; 
 int ib_post_send (int /*<<< orphan*/ *,TYPE_2__*,struct ib_send_wr**) ; 
 TYPE_3__ ig ; 
 int /*<<< orphan*/  iser_conn_state_comp_exch (struct iser_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int rdma_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
iser_conn_terminate(struct iser_conn *iser_conn)
{
	struct ib_conn *ib_conn = &iser_conn->ib_conn;
	struct ib_send_wr *bad_send_wr;
	struct ib_recv_wr *bad_recv_wr;
	int err = 0;

	/* terminate the iser conn only if the conn state is UP */
	if (!iser_conn_state_comp_exch(iser_conn, ISER_CONN_UP,
					   ISER_CONN_TERMINATING))
		return (0);

	ISER_INFO("iser_conn %p state %d\n", iser_conn, iser_conn->state);

	if (ib_conn->qp == NULL) {
		/* HOW can this be??? */
		ISER_WARN("qp wasn't created");
		return (1);
	}

	/*
	 * Todo: This is a temporary workaround.
	 * We serialize the connection closure using global lock in order to
	 * receive all posted beacons completions.
	 * Without Serialization, in case we open many connections (QPs) on
	 * the same CQ, we might miss beacons because of missing interrupts.
	 */
	sx_xlock(&ig.close_conns_mutex);

	/*
	 * In case we didn't already clean up the cma_id (peer initiated
	 * a disconnection), we need to Cause the CMA to change the QP
	 * state to ERROR.
	 */
	if (ib_conn->cma_id) {
		err = rdma_disconnect(ib_conn->cma_id);
		if (err)
			ISER_ERR("Failed to disconnect, conn: 0x%p err %d",
				iser_conn, err);

		mtx_lock(&ib_conn->beacon.flush_lock);
		memset(&ib_conn->beacon.send, 0, sizeof(struct ib_send_wr));
		ib_conn->beacon.send.wr_id = ISER_BEACON_WRID;
		ib_conn->beacon.send.opcode = IB_WR_SEND;
		/* post an indication that all send flush errors were consumed */
		err = ib_post_send(ib_conn->qp, &ib_conn->beacon.send, &bad_send_wr);
		if (err) {
			ISER_ERR("conn %p failed to post send_beacon", ib_conn);
			mtx_unlock(&ib_conn->beacon.flush_lock);
			goto out;
		}

		ISER_DBG("before send cv_wait: %p", iser_conn);
		cv_wait(&ib_conn->beacon.flush_cv, &ib_conn->beacon.flush_lock);
		ISER_DBG("after send cv_wait: %p", iser_conn);

		memset(&ib_conn->beacon.recv, 0, sizeof(struct ib_recv_wr));
		ib_conn->beacon.recv.wr_id = ISER_BEACON_WRID;
		/* post an indication that all recv flush errors were consumed */
		err = ib_post_recv(ib_conn->qp, &ib_conn->beacon.recv, &bad_recv_wr);
		if (err) {
			ISER_ERR("conn %p failed to post recv_beacon", ib_conn);
			mtx_unlock(&ib_conn->beacon.flush_lock);
			goto out;
		}

		ISER_DBG("before recv cv_wait: %p", iser_conn);
		cv_wait(&ib_conn->beacon.flush_cv, &ib_conn->beacon.flush_lock);
		mtx_unlock(&ib_conn->beacon.flush_lock);
		ISER_DBG("after recv cv_wait: %p", iser_conn);
	}
out:
	sx_xunlock(&ig.close_conns_mutex);
	return (1);
}