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
struct nd_prefix {int /*<<< orphan*/  ndpr_advrtrs; int /*<<< orphan*/  ndpr_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_IP6NDP ; 
 int /*<<< orphan*/  free (struct nd_prefix*,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

void
nd6_prefix_rele(struct nd_prefix *pr)
{

	if (refcount_release(&pr->ndpr_refcnt)) {
		KASSERT(LIST_EMPTY(&pr->ndpr_advrtrs),
		    ("prefix %p has advertising routers", pr));
		free(pr, M_IP6NDP);
	}
}