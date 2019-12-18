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
struct socket {int so_options; scalar_t__ so_linger; int /*<<< orphan*/  so_rcv; } ;
struct sdp_sock {scalar_t__ state; int flags; struct socket* socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int SDP_DROPPED ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 int SO_LINGER ; 
 scalar_t__ TCPS_ESTABLISHED ; 
 int /*<<< orphan*/  sbflush (int /*<<< orphan*/ *) ; 
 int sbused (int /*<<< orphan*/ *) ; 
 struct sdp_sock* sdp_closed (struct sdp_sock*) ; 
 struct sdp_sock* sdp_drop (struct sdp_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_output_disconnect (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_output_reset (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_stop_keepalive_timer (struct socket*) ; 
 int /*<<< orphan*/  sdp_usrclosed (struct sdp_sock*) ; 
 int /*<<< orphan*/  soisdisconnecting (struct socket*) ; 

__attribute__((used)) static void
sdp_start_disconnect(struct sdp_sock *ssk)
{
	struct socket *so;
	int unread;

	so = ssk->socket;
	SDP_WLOCK_ASSERT(ssk);
	sdp_stop_keepalive_timer(so);
	/*
	 * Neither sdp_closed() nor sdp_drop() should return NULL, as the
	 * socket is still open.
	 */
	if (ssk->state < TCPS_ESTABLISHED) {
		ssk = sdp_closed(ssk);
		KASSERT(ssk != NULL,
		    ("sdp_start_disconnect: sdp_close() returned NULL"));
	} else if ((so->so_options & SO_LINGER) && so->so_linger == 0) {
		ssk = sdp_drop(ssk, 0);
		KASSERT(ssk != NULL,
		    ("sdp_start_disconnect: sdp_drop() returned NULL"));
	} else {
		soisdisconnecting(so);
		unread = sbused(&so->so_rcv);
		sbflush(&so->so_rcv);
		sdp_usrclosed(ssk);
		if (!(ssk->flags & SDP_DROPPED)) {
			if (unread)
				sdp_output_reset(ssk);
			else
				sdp_output_disconnect(ssk);
		}
	}
}