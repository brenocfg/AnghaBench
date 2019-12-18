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
struct sdp_sock {int flags; int /*<<< orphan*/  keep2msl; TYPE_1__* socket; } ;
struct TYPE_2__ {int so_options; } ;

/* Variables and functions */
 int SDP_DROPPED ; 
 int /*<<< orphan*/  SDP_KEEPALIVE_TIME ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int SO_KEEPALIVE ; 
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_deactivate (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_post_keepalive (struct sdp_sock*) ; 

__attribute__((used)) static void
sdp_keepalive_timeout(void *data)
{
	struct sdp_sock *ssk;

	ssk = data;
	/* Callout canceled. */
        if (!callout_active(&ssk->keep2msl))
                return;
	/* Callout rescheduled as a different kind of timer. */
	if (callout_pending(&ssk->keep2msl))
		goto out;
        callout_deactivate(&ssk->keep2msl);
	if (ssk->flags & SDP_DROPPED ||
	    (ssk->socket->so_options & SO_KEEPALIVE) == 0)
		goto out;
	sdp_post_keepalive(ssk);
	callout_reset(&ssk->keep2msl, SDP_KEEPALIVE_TIME,
	    sdp_keepalive_timeout, ssk);
out:
	SDP_WUNLOCK(ssk);
}