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
struct sdp_sock {int flags; int /*<<< orphan*/ * socket; } ;

/* Variables and functions */
 int SDP_DESTROY ; 
 int SDP_DISCON ; 
 int SDP_DREQWAIT ; 
 int SDP_DROPPED ; 
 int SDP_TIMEWAIT ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  panic (char*,struct sdp_sock*) ; 
 int /*<<< orphan*/ * sdp_closed (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_output_reset (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_pcbfree (struct sdp_sock*) ; 

__attribute__((used)) static void
sdp_shutdown_task(void *data, int pending)
{
	struct sdp_sock *ssk;

	ssk = data;
	SDP_WLOCK(ssk);
	/*
	 * I don't think this can race with another call to pcbfree()
	 * because SDP_TIMEWAIT protects it.  SDP_DESTROY may be redundant.
	 */
	if (ssk->flags & SDP_DESTROY)
		panic("sdp_shutdown_task: Racing with pcbfree for ssk %p",
		    ssk);
	if (ssk->flags & SDP_DISCON)
		sdp_output_reset(ssk);
	/* We have to clear this so sdp_detach() will call pcbfree(). */
	ssk->flags &= ~(SDP_TIMEWAIT | SDP_DREQWAIT);
	if ((ssk->flags & SDP_DROPPED) == 0 &&
	    sdp_closed(ssk) == NULL)
		return;
	if (ssk->socket == NULL) {
		sdp_pcbfree(ssk);
		return;
	}
	SDP_WUNLOCK(ssk);
}