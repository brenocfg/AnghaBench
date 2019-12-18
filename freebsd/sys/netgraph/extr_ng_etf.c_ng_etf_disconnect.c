#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct filter {scalar_t__ match_hook; } ;
typedef  scalar_t__ hook_p ;
typedef  TYPE_3__* etf_p ;
struct TYPE_6__ {scalar_t__ hook; } ;
struct TYPE_5__ {scalar_t__ hook; } ;
struct TYPE_7__ {TYPE_2__ nomatch_hook; TYPE_1__ downstream_hook; int /*<<< orphan*/ * hashtable; } ;

/* Variables and functions */
 int HASHSIZE ; 
 struct filter* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct filter* LIST_NEXT (struct filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_ETF ; 
 int /*<<< orphan*/  NG_HOOK_NODE (scalar_t__) ; 
 struct filter* NG_HOOK_PRIVATE (scalar_t__) ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_etf_disconnect(hook_p hook)
{
	const etf_p etfp = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	int i;
	struct filter *fil1, *fil2;

	/* purge any rules that refer to this filter */
	for (i = 0; i < HASHSIZE; i++) {
		fil1 = LIST_FIRST(&etfp->hashtable[i]);
		while (fil1 != NULL) {
			fil2 = LIST_NEXT(fil1, next);
			if (fil1->match_hook == hook) {
				LIST_REMOVE(fil1, next);
				free(fil1, M_NETGRAPH_ETF);
			}
			fil1 = fil2;
		}
	}
		
	/* If it's not one of the special hooks, then free it */
	if (hook == etfp->downstream_hook.hook) {
		etfp->downstream_hook.hook = NULL;
	} else if (hook == etfp->nomatch_hook.hook) {
		etfp->nomatch_hook.hook = NULL;
	} else {
		if (NG_HOOK_PRIVATE(hook)) /* Paranoia */
			free(NG_HOOK_PRIVATE(hook), M_NETGRAPH_ETF);
	}

	NG_HOOK_SET_PRIVATE(hook, NULL);

	if ((NG_NODE_NUMHOOKS(NG_HOOK_NODE(hook)) == 0)
	&& (NG_NODE_IS_VALID(NG_HOOK_NODE(hook)))) /* already shutting down? */
		ng_rmnode_self(NG_HOOK_NODE(hook));
	return (0);
}