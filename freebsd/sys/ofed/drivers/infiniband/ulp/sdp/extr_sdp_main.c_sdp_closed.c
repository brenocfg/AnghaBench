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
struct socket {int so_state; } ;
struct sdp_sock {int flags; struct socket* socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int SDP_DROPPED ; 
 int SDP_SOCKREF ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int SS_PROTOREF ; 
 int /*<<< orphan*/  sofree (struct socket*) ; 
 int /*<<< orphan*/  soisdisconnected (struct socket*) ; 

__attribute__((used)) static struct sdp_sock *
sdp_closed(struct sdp_sock *ssk)
{
	struct socket *so;

	SDP_WLOCK_ASSERT(ssk);

	ssk->flags |= SDP_DROPPED;
	so = ssk->socket;
	soisdisconnected(so);
	if (ssk->flags & SDP_SOCKREF) {
		KASSERT(so->so_state & SS_PROTOREF,
		    ("sdp_closed: !SS_PROTOREF"));
		ssk->flags &= ~SDP_SOCKREF;
		SDP_WUNLOCK(ssk);
		SOCK_LOCK(so);
		so->so_state &= ~SS_PROTOREF;
		sofree(so);
		return (NULL);
	}
	return (ssk);
}