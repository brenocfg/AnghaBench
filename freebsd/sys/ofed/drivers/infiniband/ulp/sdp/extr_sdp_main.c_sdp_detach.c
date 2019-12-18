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
struct socket {int dummy; } ;
struct sdp_sock {int flags; scalar_t__ state; TYPE_1__* socket; } ;
struct TYPE_2__ {int /*<<< orphan*/ * so_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int SDP_DREQWAIT ; 
 int SDP_DROPPED ; 
 int SDP_TIMEWAIT ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 scalar_t__ TCPS_SYN_SENT ; 
 int /*<<< orphan*/  panic (char*,struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_pcbfree (struct sdp_sock*) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 

__attribute__((used)) static void
sdp_detach(struct socket *so)
{
	struct sdp_sock *ssk;

	ssk = sdp_sk(so);
	SDP_WLOCK(ssk);
	KASSERT(ssk->socket != NULL, ("sdp_detach: socket is NULL"));
	ssk->socket->so_pcb = NULL;
	ssk->socket = NULL;
	if (ssk->flags & (SDP_TIMEWAIT | SDP_DREQWAIT))
		SDP_WUNLOCK(ssk);
	else if (ssk->flags & SDP_DROPPED || ssk->state < TCPS_SYN_SENT)
		sdp_pcbfree(ssk);
	else
		panic("sdp_detach: Unexpected state, ssk %p.\n", ssk);
}