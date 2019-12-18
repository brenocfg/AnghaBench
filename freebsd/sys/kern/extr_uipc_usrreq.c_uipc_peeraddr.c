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
uipc_peeraddr(struct socket *so, struct sockaddr **nam)
{
	struct unpcb *unp, *unp2;
	const struct sockaddr *sa;

	unp = sotounpcb(so);
	KASSERT(unp != NULL, ("uipc_peeraddr: unp == NULL"));

	*nam = malloc(sizeof(struct sockaddr_un), M_SONAME, M_WAITOK);
	UNP_LINK_RLOCK();
	/*
	 * XXX: It seems that this test always fails even when connection is
	 * established.  So, this else clause is added as workaround to
	 * return PF_LOCAL sockaddr.
	 */
	unp2 = unp->unp_conn;
	if (unp2 != NULL) {
		UNP_PCB_LOCK(unp2);
		if (unp2->unp_addr != NULL)
			sa = (struct sockaddr *) unp2->unp_addr;
		else
			sa = &sun_noname;
		bcopy(sa, *nam, sa->sa_len);
		UNP_PCB_UNLOCK(unp2);
	} else {
		sa = &sun_noname;
		bcopy(sa, *nam, sa->sa_len);
	}
	UNP_LINK_RUNLOCK();
	return (0);
}