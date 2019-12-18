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
struct unpcb {int /*<<< orphan*/ * unp_addr; } ;
struct socket {int dummy; } ;
struct sockaddr_un {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int /*<<< orphan*/  bcopy (struct sockaddr const*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 struct sockaddr* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 struct sockaddr sun_noname ; 

__attribute__((used)) static int
uipc_sockaddr(struct socket *so, struct sockaddr **nam)
{
	struct unpcb *unp;
	const struct sockaddr *sa;

	unp = sotounpcb(so);
	KASSERT(unp != NULL, ("uipc_sockaddr: unp == NULL"));

	*nam = malloc(sizeof(struct sockaddr_un), M_SONAME, M_WAITOK);
	UNP_PCB_LOCK(unp);
	if (unp->unp_addr != NULL)
		sa = (struct sockaddr *) unp->unp_addr;
	else
		sa = &sun_noname;
	bcopy(sa, *nam, sa->sa_len);
	UNP_PCB_UNLOCK(unp);
	return (0);
}