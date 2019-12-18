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
struct unpcb {struct unpcb* unp_conn; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK_ASSERT (struct unpcb*) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_drop (struct unpcb*) ; 
 int /*<<< orphan*/  unp_pcb_hold (struct unpcb*) ; 

__attribute__((used)) static void
uipc_abort(struct socket *so)
{
	struct unpcb *unp, *unp2;

	unp = sotounpcb(so);
	KASSERT(unp != NULL, ("uipc_abort: unp == NULL"));
	UNP_PCB_UNLOCK_ASSERT(unp);

	UNP_PCB_LOCK(unp);
	unp2 = unp->unp_conn;
	if (unp2 != NULL) {
		unp_pcb_hold(unp2);
		UNP_PCB_UNLOCK(unp);
		unp_drop(unp2);
	} else
		UNP_PCB_UNLOCK(unp);
}