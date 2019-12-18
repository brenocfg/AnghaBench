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
struct sdp_sock {int flags; int /*<<< orphan*/  keep2msl; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int SDP_DREQWAIT ; 
 int /*<<< orphan*/  SDP_FIN_WAIT_TIMEOUT ; 
 int SDP_NEEDFIN ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_dreq_timeout ; 
 int /*<<< orphan*/  sdp_post_sends (struct sdp_sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdp_output_disconnect(struct sdp_sock *ssk)
{

	SDP_WLOCK_ASSERT(ssk);
	callout_reset(&ssk->keep2msl, SDP_FIN_WAIT_TIMEOUT,
	    sdp_dreq_timeout, ssk);
	ssk->flags |= SDP_NEEDFIN | SDP_DREQWAIT;
	sdp_post_sends(ssk, M_NOWAIT);
}