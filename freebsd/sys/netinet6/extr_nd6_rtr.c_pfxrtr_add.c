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
struct nd_prefix {int /*<<< orphan*/  ndpr_advrtrs; } ;
struct nd_pfxrouter {struct nd_defrouter* router; } ;
struct nd_defrouter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct nd_pfxrouter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IP6NDP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  ND6_RLOCK () ; 
 int /*<<< orphan*/  ND6_RUNLOCK () ; 
 int /*<<< orphan*/  ND6_UNLOCK_ASSERT () ; 
 int /*<<< orphan*/  ND6_WLOCK () ; 
 int /*<<< orphan*/  ND6_WUNLOCK () ; 
 int /*<<< orphan*/  defrouter_ref (struct nd_defrouter*) ; 
 int /*<<< orphan*/  defrouter_rele (struct nd_defrouter*) ; 
 int /*<<< orphan*/  free (struct nd_pfxrouter*,int /*<<< orphan*/ ) ; 
 struct nd_pfxrouter* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfr_entry ; 
 int /*<<< orphan*/  pfxlist_onlink_check () ; 
 int /*<<< orphan*/ * pfxrtr_lookup (struct nd_prefix*,struct nd_defrouter*) ; 

__attribute__((used)) static void
pfxrtr_add(struct nd_prefix *pr, struct nd_defrouter *dr)
{
	struct nd_pfxrouter *new;
	bool update;

	ND6_UNLOCK_ASSERT();

	ND6_RLOCK();
	if (pfxrtr_lookup(pr, dr) != NULL) {
		ND6_RUNLOCK();
		return;
	}
	ND6_RUNLOCK();

	new = malloc(sizeof(*new), M_IP6NDP, M_NOWAIT | M_ZERO);
	if (new == NULL)
		return;
	defrouter_ref(dr);
	new->router = dr;

	ND6_WLOCK();
	if (pfxrtr_lookup(pr, dr) == NULL) {
		LIST_INSERT_HEAD(&pr->ndpr_advrtrs, new, pfr_entry);
		update = true;
	} else {
		/* We lost a race to add the reference. */
		defrouter_rele(dr);
		free(new, M_IP6NDP);
		update = false;
	}
	ND6_WUNLOCK();

	if (update)
		pfxlist_onlink_check();
}