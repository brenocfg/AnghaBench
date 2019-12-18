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
struct nd_pfxrouter {int /*<<< orphan*/  router; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct nd_pfxrouter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IP6NDP ; 
 int /*<<< orphan*/  ND6_WLOCK_ASSERT () ; 
 int /*<<< orphan*/  defrouter_rele (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nd_pfxrouter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_entry ; 

__attribute__((used)) static void
pfxrtr_del(struct nd_pfxrouter *pfr)
{

	ND6_WLOCK_ASSERT();

	LIST_REMOVE(pfr, pfr_entry);
	defrouter_rele(pfr->router);
	free(pfr, M_IP6NDP);
}