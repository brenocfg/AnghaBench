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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sdp_sock {int flags; scalar_t__ lport; int /*<<< orphan*/  id; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int SDP_DROPPED ; 
 int SDP_TIMEWAIT ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  TCPS_LISTEN ; 
 int rdma_listen (int /*<<< orphan*/ ,int) ; 
 int sdp_pcbbind (struct sdp_sock*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 
 int /*<<< orphan*/  solisten_proto (struct socket*,int) ; 
 int solisten_proto_check (struct socket*) ; 

__attribute__((used)) static int
sdp_listen(struct socket *so, int backlog, struct thread *td)
{
	int error = 0;
	struct sdp_sock *ssk;

	ssk = sdp_sk(so);
	SDP_WLOCK(ssk);
	if (ssk->flags & (SDP_TIMEWAIT | SDP_DROPPED)) {
		error = EINVAL;
		goto out;
	}
	if (error == 0 && ssk->lport == 0)
		error = sdp_pcbbind(ssk, (struct sockaddr *)0, td->td_ucred);
	SOCK_LOCK(so);
	if (error == 0)
		error = solisten_proto_check(so);
	if (error == 0) {
		solisten_proto(so, backlog);
		ssk->state = TCPS_LISTEN;
	}
	SOCK_UNLOCK(so);

out:
	SDP_WUNLOCK(ssk);
	if (error == 0)
		error = -rdma_listen(ssk->id, backlog);
	return (error);
}