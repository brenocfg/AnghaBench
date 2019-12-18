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
struct unpcb {int /*<<< orphan*/ * unp_socket; int /*<<< orphan*/  unp_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNP_PCB_LOCK_ASSERT (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_LOCK_DESTROY (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct unpcb*) ; 
 int /*<<< orphan*/  unp_zone ; 

__attribute__((used)) static int
unp_pcb_rele(struct unpcb *unp)
{
	int freed;

	UNP_PCB_LOCK_ASSERT(unp);
	MPASS(unp->unp_refcount);
	if ((freed = refcount_release(&unp->unp_refcount))) {
		/* we got here with having detached? */
		MPASS(unp->unp_socket == NULL);
		UNP_PCB_UNLOCK(unp);
		UNP_PCB_LOCK_DESTROY(unp);
		uma_zfree(unp_zone, unp);
	}
	return (freed);
}