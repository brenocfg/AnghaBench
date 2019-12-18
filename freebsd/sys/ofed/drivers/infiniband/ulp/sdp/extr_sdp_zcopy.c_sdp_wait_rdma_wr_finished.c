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
struct socket {int /*<<< orphan*/  sk_sleep; } ;
struct TYPE_4__ {TYPE_1__* rdma_inflight; } ;
struct sdp_sock {struct socket* socket; TYPE_2__ tx_ring; int /*<<< orphan*/  qp_active; } ;
struct TYPE_3__ {int /*<<< orphan*/  busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posts_handler_get (struct sdp_sock*) ; 
 int /*<<< orphan*/  posts_handler_put (struct sdp_sock*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_dbg_data (struct socket*,char*) ; 
 int /*<<< orphan*/  sdp_prf1 (struct socket*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sdp_warn (struct socket*,char*) ; 
 int /*<<< orphan*/  sk_wait_event (struct socket*,long*,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void sdp_wait_rdma_wr_finished(struct sdp_sock *ssk)
{
	struct socket *sk = ssk->socket;
	long timeo = HZ * 5; /* Timeout for for RDMA read */
	DEFINE_WAIT(wait);

	sdp_dbg_data(sk, "Sleep till RDMA wr finished.\n");
	while (1) {
		prepare_to_wait(sk->sk_sleep, &wait, TASK_UNINTERRUPTIBLE);

		if (!ssk->tx_ring.rdma_inflight->busy) {
			sdp_dbg_data(sk, "got rdma cqe\n");
			break;
		}

		if (!ssk->qp_active) {
			sdp_dbg_data(sk, "QP destroyed\n");
			break;
		}

		if (!timeo) {
			sdp_warn(sk, "Panic: Timed out waiting for RDMA read\n");
			WARN_ON(1);
			break;
		}

		posts_handler_put(ssk);

		sdp_prf1(sk, NULL, "Going to sleep");
		sk_wait_event(sk, &timeo, 
			!ssk->tx_ring.rdma_inflight->busy);
		sdp_prf1(sk, NULL, "Woke up");
		sdp_dbg_data(ssk->socket, "woke up sleepers\n");

		posts_handler_get(ssk);
	}

	finish_wait(sk->sk_sleep, &wait);

	sdp_dbg_data(sk, "Finished waiting\n");
}