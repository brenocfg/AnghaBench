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
struct unpcb {int /*<<< orphan*/ * unp_addr; struct unpcb* unp_conn; } ;
struct socket {int dummy; } ;
struct sockaddr_un {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UNP_LINK_RLOCK () ; 
 int /*<<< orphan*/  UNP_LINK_RUNLOCK () ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int /*<<< orphan*/  bcopy (struct sockaddr const*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 struct sockaddr* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 struct sockaddr sun_noname ; 

__attribute__((used)) static int
uipc_accept(struct socket *so, struct sockaddr **nam)
{
	struct unpcb *unp, *unp2;
	const struct sockaddr *sa;

	/*
	 * Pass back name of connected socket, if it was bound and we are
	 * still connected (our peer may have closed already!).
	 */
	unp = sotounpcb(so);
	KASSERT(unp != NULL, ("uipc_accept: unp == NULL"));

	*nam = malloc(sizeof(struct sockaddr_un), M_SONAME, M_WAITOK);
	UNP_LINK_RLOCK();
	unp2 = unp->unp_conn;
	if (unp2 != NULL && unp2->unp_addr != NULL) {
		UNP_PCB_LOCK(unp2);
		sa = (struct sockaddr *) unp2->unp_addr;
		bcopy(sa, *nam, sa->sa_len);
		UNP_PCB_UNLOCK(unp2);
	} else {
		sa = &sun_noname;
		bcopy(sa, *nam, sa->sa_len);
	}
	UNP_LINK_RUNLOCK();
	return (0);
}