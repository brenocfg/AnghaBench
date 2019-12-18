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
struct protosw {int /*<<< orphan*/  (* pr_fasttimo ) () ;} ;
struct epoch_tracker {int dummy; } ;
struct domain {struct protosw* dom_protoswNPROTOSW; struct protosw* dom_protosw; struct domain* dom_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),int /*<<< orphan*/ *) ; 
 struct domain* domains ; 
 int hz ; 
 int /*<<< orphan*/  pffast_callout ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void
pffasttimo(void *arg)
{
	struct epoch_tracker et;
	struct domain *dp;
	struct protosw *pr;

	NET_EPOCH_ENTER(et);
	for (dp = domains; dp; dp = dp->dom_next)
		for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
			if (pr->pr_fasttimo)
				(*pr->pr_fasttimo)();
	NET_EPOCH_EXIT(et);
	callout_reset(&pffast_callout, hz/5, pffasttimo, NULL);
}