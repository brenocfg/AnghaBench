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
struct unpcb {struct unpcb* unp_conn; struct socket* unp_socket; } ;
struct socket {int /*<<< orphan*/  so_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int /*<<< orphan*/  unp_disconnect (struct unpcb*,struct unpcb*) ; 
 int /*<<< orphan*/  unp_pcb_hold (struct unpcb*) ; 
 int /*<<< orphan*/  unp_pcb_owned_lock2 (struct unpcb*,struct unpcb*,int) ; 
 scalar_t__ unp_pcb_rele (struct unpcb*) ; 

__attribute__((used)) static void
unp_drop(struct unpcb *unp)
{
	struct socket *so = unp->unp_socket;
	struct unpcb *unp2;
	int freed;

	/*
	 * Regardless of whether the socket's peer dropped the connection
	 * with this socket by aborting or disconnecting, POSIX requires
	 * that ECONNRESET is returned.
	 */
	/* acquire a reference so that unp isn't freed from underneath us */

	UNP_PCB_LOCK(unp);
	if (so)
		so->so_error = ECONNRESET;
	unp2 = unp->unp_conn;
	if (unp2 == unp) {
		unp_disconnect(unp, unp2);
	} else if (unp2 != NULL) {
		unp_pcb_hold(unp2);
		unp_pcb_owned_lock2(unp, unp2, freed);
		unp_disconnect(unp, unp2);
		if (unp_pcb_rele(unp2) == 0)
			UNP_PCB_UNLOCK(unp2);
	}
	if (unp_pcb_rele(unp) == 0)
		UNP_PCB_UNLOCK(unp);
}