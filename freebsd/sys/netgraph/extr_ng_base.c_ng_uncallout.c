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
struct callout {int /*<<< orphan*/ * c_arg; int /*<<< orphan*/ * c_func; } ;
typedef  int /*<<< orphan*/ * node_p ;
typedef  int /*<<< orphan*/ * item_p ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * NGI_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ *) ; 
 int callout_stop (struct callout*) ; 
 int /*<<< orphan*/  ng_callout_trampoline ; 

int
ng_uncallout(struct callout *c, node_p node)
{
	item_p item;
	int rval;

	KASSERT(c != NULL, ("ng_uncallout: NULL callout"));
	KASSERT(node != NULL, ("ng_uncallout: NULL node"));

	rval = callout_stop(c);
	item = c->c_arg;
	/* Do an extra check */
	if ((rval > 0) && (c->c_func == &ng_callout_trampoline) &&
	    (item != NULL) && (NGI_NODE(item) == node)) {
		/*
		 * We successfully removed it from the queue before it ran
		 * So now we need to unreference everything that was
		 * given extra references. (NG_FREE_ITEM does this).
		 */
		NG_FREE_ITEM(item);
	}
	c->c_arg = NULL;

	/*
	 * Callers only want to know if the callout was cancelled and
	 * not draining or stopped.
	 */
	return (rval > 0);
}