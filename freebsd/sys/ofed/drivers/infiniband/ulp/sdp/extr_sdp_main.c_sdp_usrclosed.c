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
struct sdp_sock {int state; int /*<<< orphan*/  socket; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SDP_NEEDFIN ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
#define  TCPS_CLOSED 133 
#define  TCPS_CLOSE_WAIT 132 
#define  TCPS_ESTABLISHED 131 
 int TCPS_FIN_WAIT_1 ; 
 int TCPS_FIN_WAIT_2 ; 
 int TCPS_LAST_ACK ; 
#define  TCPS_LISTEN 130 
#define  TCPS_SYN_RECEIVED 129 
#define  TCPS_SYN_SENT 128 
 int /*<<< orphan*/  sdp_2msl_wait (struct sdp_sock*) ; 
 struct sdp_sock* sdp_closed (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_destroy_cma (struct sdp_sock*) ; 
 int /*<<< orphan*/  soisdisconnected (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdp_usrclosed(struct sdp_sock *ssk)
{

	SDP_WLOCK_ASSERT(ssk);

	switch (ssk->state) {
	case TCPS_LISTEN:
		ssk->state = TCPS_CLOSED;
		SDP_WUNLOCK(ssk);
		sdp_destroy_cma(ssk);
		SDP_WLOCK(ssk);
		/* FALLTHROUGH */
	case TCPS_CLOSED:
		ssk = sdp_closed(ssk);
		/*
		 * sdp_closed() should never return NULL here as the socket is
		 * still open.
		 */
		KASSERT(ssk != NULL,
		    ("sdp_usrclosed: sdp_closed() returned NULL"));
		break;

	case TCPS_SYN_SENT:
		/* FALLTHROUGH */
	case TCPS_SYN_RECEIVED:
		ssk->flags |= SDP_NEEDFIN;
		break;

	case TCPS_ESTABLISHED:
		ssk->flags |= SDP_NEEDFIN;
		ssk->state = TCPS_FIN_WAIT_1;
		break;

	case TCPS_CLOSE_WAIT:
		ssk->state = TCPS_LAST_ACK;
		break;
	}
	if (ssk->state >= TCPS_FIN_WAIT_2) {
		/* Prevent the connection hanging in FIN_WAIT_2 forever. */
		if (ssk->state == TCPS_FIN_WAIT_2)
			sdp_2msl_wait(ssk);
		else
			soisdisconnected(ssk->socket);
	}
}