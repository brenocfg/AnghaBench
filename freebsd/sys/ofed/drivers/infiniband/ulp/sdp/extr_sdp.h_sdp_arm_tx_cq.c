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
struct TYPE_2__ {int /*<<< orphan*/  cq; } ;
struct sdp_sock {TYPE_1__ tx_ring; int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 int /*<<< orphan*/  ib_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_dbg_data (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_prf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tx_credits (struct sdp_sock*) ; 
 int /*<<< orphan*/  tx_ring_posted (struct sdp_sock*) ; 

__attribute__((used)) static inline void sdp_arm_tx_cq(struct sdp_sock *ssk)
{
	sdp_prf(ssk->socket, NULL, "Arming TX cq");
	sdp_dbg_data(ssk->socket, "Arming TX cq. credits: %d, posted: %d\n",
		tx_credits(ssk), tx_ring_posted(ssk));

	ib_req_notify_cq(ssk->tx_ring.cq, IB_CQ_NEXT_COMP);
}