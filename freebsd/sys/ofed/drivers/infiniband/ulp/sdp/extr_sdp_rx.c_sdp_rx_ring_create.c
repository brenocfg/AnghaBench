#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct sdp_sock {TYPE_2__ rx_ring; int /*<<< orphan*/  socket; int /*<<< orphan*/  rx_comp_work; } ;
struct ib_device {int dummy; } ;
struct ib_cq_init_attr {int cqe; int /*<<< orphan*/  flags; int /*<<< orphan*/  comp_vector; } ;
struct ib_cq {int dummy; } ;
struct TYPE_4__ {struct ib_cq* cq; } ;
struct TYPE_6__ {TYPE_1__ rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct ib_cq*) ; 
 int /*<<< orphan*/  M_SDP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PTR_ERR (struct ib_cq*) ; 
 int SDP_RX_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ib_cq* ib_create_cq (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdp_sock*,struct ib_cq_init_attr*) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_arm_rx_cq (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdp_rx_comp_work ; 
 int /*<<< orphan*/  sdp_rx_cq_event_handler ; 
 int /*<<< orphan*/  sdp_rx_irq ; 
 TYPE_3__* sdp_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_warn (int /*<<< orphan*/ ,char*,int) ; 

int
sdp_rx_ring_create(struct sdp_sock *ssk, struct ib_device *device)
{
	struct ib_cq_init_attr rx_cq_attr = {
		.cqe = SDP_RX_SIZE,
		.comp_vector = 0,
		.flags = 0,
	};
	struct ib_cq *rx_cq;
	int rc = 0;

	sdp_dbg(ssk->socket, "rx ring created");
	INIT_WORK(&ssk->rx_comp_work, sdp_rx_comp_work);
	atomic_set(&ssk->rx_ring.head, 1);
	atomic_set(&ssk->rx_ring.tail, 1);

	ssk->rx_ring.buffer = malloc(sizeof(*ssk->rx_ring.buffer) * SDP_RX_SIZE,
	    M_SDP, M_WAITOK);

	rx_cq = ib_create_cq(device, sdp_rx_irq, sdp_rx_cq_event_handler,
	    ssk, &rx_cq_attr);
	if (IS_ERR(rx_cq)) {
		rc = PTR_ERR(rx_cq);
		sdp_warn(ssk->socket, "Unable to allocate RX CQ: %d.\n", rc);
		goto err_cq;
	}

	sdp_sk(ssk->socket)->rx_ring.cq = rx_cq;
	sdp_arm_rx_cq(ssk);

	return 0;

err_cq:
	free(ssk->rx_ring.buffer, M_SDP);
	ssk->rx_ring.buffer = NULL;
	return rc;
}