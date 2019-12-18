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
struct sdp_sock {int /*<<< orphan*/  keep2msl; int /*<<< orphan*/  socket; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_TIMEWAIT ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 int /*<<< orphan*/  TCPS_TIME_WAIT ; 
 int /*<<< orphan*/  TCPTV_MSL ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_2msl_timeout ; 
 int /*<<< orphan*/  soisdisconnected (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdp_2msl_wait(struct sdp_sock *ssk)
{

	SDP_WLOCK_ASSERT(ssk);
	ssk->flags |= SDP_TIMEWAIT;
	ssk->state = TCPS_TIME_WAIT;
	soisdisconnected(ssk->socket);
	callout_reset(&ssk->keep2msl, TCPTV_MSL, sdp_2msl_timeout, ssk);
}