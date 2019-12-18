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
struct sdp_sock {TYPE_1__ rx_ring; int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 int /*<<< orphan*/  ib_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_dbg_data (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdp_prf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline void sdp_arm_rx_cq(struct sdp_sock *ssk)
{
	sdp_prf(ssk->socket, NULL, "Arming RX cq");
	sdp_dbg_data(ssk->socket, "Arming RX cq\n");

	ib_req_notify_cq(ssk->rx_ring.cq, IB_CQ_NEXT_COMP);
}