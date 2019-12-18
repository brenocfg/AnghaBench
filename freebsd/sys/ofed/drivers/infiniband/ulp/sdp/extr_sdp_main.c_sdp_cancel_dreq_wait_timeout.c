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
struct sdp_sock {int /*<<< orphan*/  flags; int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_DREQWAIT ; 
 int /*<<< orphan*/  sdp_2msl_wait (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_dbg (int /*<<< orphan*/ ,char*) ; 

void
sdp_cancel_dreq_wait_timeout(struct sdp_sock *ssk)
{
	sdp_dbg(ssk->socket, "cancelling dreq wait timeout\n");
	ssk->flags &= ~SDP_DREQWAIT;
	sdp_2msl_wait(ssk);
}