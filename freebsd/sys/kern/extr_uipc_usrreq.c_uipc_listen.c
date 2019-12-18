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
struct unpcb {int /*<<< orphan*/  unp_peercred; int /*<<< orphan*/ * unp_conn; int /*<<< orphan*/ * unp_vnode; } ;
struct thread {int dummy; } ;
struct socket {scalar_t__ so_type; } ;

/* Variables and functions */
 int EDESTADDRREQ ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 scalar_t__ SOCK_SEQPACKET ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int /*<<< orphan*/  cru2xt (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  solisten_proto (struct socket*,int) ; 
 int solisten_proto_check (struct socket*) ; 
 struct unpcb* sotounpcb (struct socket*) ; 

__attribute__((used)) static int
uipc_listen(struct socket *so, int backlog, struct thread *td)
{
	struct unpcb *unp;
	int error;

	if (so->so_type != SOCK_STREAM && so->so_type != SOCK_SEQPACKET)
		return (EOPNOTSUPP);

	unp = sotounpcb(so);
	KASSERT(unp != NULL, ("uipc_listen: unp == NULL"));

	UNP_PCB_LOCK(unp);
	if (unp->unp_vnode == NULL) {
		/* Already connected or not bound to an address. */
		error = unp->unp_conn != NULL ? EINVAL : EDESTADDRREQ;
		UNP_PCB_UNLOCK(unp);
		return (error);
	}

	SOCK_LOCK(so);
	error = solisten_proto_check(so);
	if (error == 0) {
		cru2xt(td, &unp->unp_peercred);
		solisten_proto(so, backlog);
	}
	SOCK_UNLOCK(so);
	UNP_PCB_UNLOCK(unp);
	return (error);
}