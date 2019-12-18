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
struct sdp_sock {int /*<<< orphan*/  socket; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDPSTATS_COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_dbg_data (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdp_poll_tx (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_prf1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tx_int_count ; 

__attribute__((used)) static void
sdp_tx_irq(struct ib_cq *cq, void *cq_context)
{
	struct sdp_sock *ssk;

	ssk = cq_context;
	sdp_prf1(ssk->socket, NULL, "tx irq");
	sdp_dbg_data(ssk->socket, "Got tx comp interrupt\n");
	SDPSTATS_COUNTER_INC(tx_int_count);
	SDP_WLOCK(ssk);
	sdp_poll_tx(ssk);
	SDP_WUNLOCK(ssk);
}