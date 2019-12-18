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
struct TYPE_2__ {int /*<<< orphan*/ * buffer; scalar_t__ poll_cnt; struct ib_cq* cq; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; int /*<<< orphan*/  timer; } ;
struct sdp_sock {TYPE_1__ tx_ring; int /*<<< orphan*/  socket; int /*<<< orphan*/  lock; int /*<<< orphan*/  nagle_timer; } ;
struct ib_device {int dummy; } ;
struct ib_cq_init_attr {int cqe; int /*<<< orphan*/  flags; int /*<<< orphan*/  comp_vector; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ib_cq*) ; 
 int /*<<< orphan*/  M_SDP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PTR_ERR (struct ib_cq*) ; 
 int SDP_TX_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_init_rw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ib_cq* ib_create_cq (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdp_sock*,struct ib_cq_init_attr*) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_arm_tx_cq (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdp_tx_cq_event_handler ; 
 int /*<<< orphan*/  sdp_tx_irq ; 
 int /*<<< orphan*/  sdp_warn (int /*<<< orphan*/ ,char*,int) ; 

int
sdp_tx_ring_create(struct sdp_sock *ssk, struct ib_device *device)
{
	struct ib_cq_init_attr tx_cq_attr = {
		.cqe = SDP_TX_SIZE,
		.comp_vector = 0,
		.flags = 0,
	};
	struct ib_cq *tx_cq;
	int rc = 0;

	sdp_dbg(ssk->socket, "tx ring create\n");
	callout_init_rw(&ssk->tx_ring.timer, &ssk->lock, 0);
	callout_init_rw(&ssk->nagle_timer, &ssk->lock, 0);
	atomic_set(&ssk->tx_ring.head, 1);
	atomic_set(&ssk->tx_ring.tail, 1);

	ssk->tx_ring.buffer = malloc(sizeof(*ssk->tx_ring.buffer) * SDP_TX_SIZE,
	    M_SDP, M_WAITOK);

	tx_cq = ib_create_cq(device, sdp_tx_irq, sdp_tx_cq_event_handler,
			  ssk, &tx_cq_attr);
	if (IS_ERR(tx_cq)) {
		rc = PTR_ERR(tx_cq);
		sdp_warn(ssk->socket, "Unable to allocate TX CQ: %d.\n", rc);
		goto err_cq;
	}
	ssk->tx_ring.cq = tx_cq;
	ssk->tx_ring.poll_cnt = 0;
	sdp_arm_tx_cq(ssk);

	return 0;

err_cq:
	free(ssk->tx_ring.buffer, M_SDP);
	ssk->tx_ring.buffer = NULL;
	return rc;
}