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
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct sdp_sock {TYPE_1__ tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_deactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdp_poll_tx (struct sdp_sock*) ; 

__attribute__((used)) static void
sdp_poll_tx_timeout(void *data)
{
	struct sdp_sock *ssk = (struct sdp_sock *)data;

	if (!callout_active(&ssk->tx_ring.timer))
		return;
	callout_deactivate(&ssk->tx_ring.timer);
	sdp_poll_tx(ssk);
}