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
struct unpcb {int unp_flags; struct unpcb* unp_conn; int /*<<< orphan*/  unp_refs; } ;
struct socket {int so_type; } ;

/* Variables and functions */
 int EPROTOTYPE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct unpcb*,int /*<<< orphan*/ ) ; 
 int PRU_CONNECT ; 
#define  SOCK_DGRAM 130 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 int UNP_CONNWAIT ; 
 int UNP_NASCENT ; 
 int /*<<< orphan*/  UNP_PCB_LOCK_ASSERT (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_REF_LIST_LOCK () ; 
 int /*<<< orphan*/  UNP_REF_LIST_UNLOCK () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  soisconnected (struct socket*) ; 
 int /*<<< orphan*/  soisconnecting (struct socket*) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_pcb_hold (struct unpcb*) ; 
 int /*<<< orphan*/  unp_reflink ; 

__attribute__((used)) static int
unp_connect2(struct socket *so, struct socket *so2, int req)
{
	struct unpcb *unp;
	struct unpcb *unp2;

	unp = sotounpcb(so);
	KASSERT(unp != NULL, ("unp_connect2: unp == NULL"));
	unp2 = sotounpcb(so2);
	KASSERT(unp2 != NULL, ("unp_connect2: unp2 == NULL"));

	UNP_PCB_LOCK_ASSERT(unp);
	UNP_PCB_LOCK_ASSERT(unp2);

	if (so2->so_type != so->so_type)
		return (EPROTOTYPE);
	unp2->unp_flags &= ~UNP_NASCENT;
	unp->unp_conn = unp2;
	unp_pcb_hold(unp2);
	unp_pcb_hold(unp);
	switch (so->so_type) {
	case SOCK_DGRAM:
		UNP_REF_LIST_LOCK();
		LIST_INSERT_HEAD(&unp2->unp_refs, unp, unp_reflink);
		UNP_REF_LIST_UNLOCK();
		soisconnected(so);
		break;

	case SOCK_STREAM:
	case SOCK_SEQPACKET:
		unp2->unp_conn = unp;
		if (req == PRU_CONNECT &&
		    ((unp->unp_flags | unp2->unp_flags) & UNP_CONNWAIT))
			soisconnecting(so);
		else
			soisconnected(so);
		soisconnected(so2);
		break;

	default:
		panic("unp_connect2");
	}
	return (0);
}