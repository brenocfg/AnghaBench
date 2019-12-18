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
struct socket {int /*<<< orphan*/  so_state; } ;
struct sdp_sock {int flags; } ;

/* Variables and functions */
 int SDP_DROPPED ; 
 int SDP_SOCKREF ; 
 int SDP_TIMEWAIT ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  SS_PROTOREF ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 
 int /*<<< orphan*/  sdp_start_disconnect (struct sdp_sock*) ; 

__attribute__((used)) static void
sdp_close(struct socket *so)
{
	struct sdp_sock *ssk;

	ssk = sdp_sk(so);
	SDP_WLOCK(ssk);
	/*
	 * If we have not yet dropped, do it now.
	 */
	if (!(ssk->flags & SDP_TIMEWAIT) &&
	    !(ssk->flags & SDP_DROPPED)) 
		sdp_start_disconnect(ssk);

	/*
	 * If we've still not dropped let the socket layer know we're
	 * holding on to the socket and pcb for a while.
	 */
	if (!(ssk->flags & SDP_DROPPED)) {
		SOCK_LOCK(so);
		so->so_state |= SS_PROTOREF;
		SOCK_UNLOCK(so);
		ssk->flags |= SDP_SOCKREF;
	}
	SDP_WUNLOCK(ssk);
}