#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ETF_hookinfo {void* hook; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;
typedef  TYPE_1__* etf_p ;
struct TYPE_3__ {struct ETF_hookinfo nomatch_hook; scalar_t__ packets_out; scalar_t__ packets_in; struct ETF_hookinfo downstream_hook; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NETGRAPH_ETF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_ETF_HOOK_DOWNSTREAM ; 
 int /*<<< orphan*/  NG_ETF_HOOK_NOMATCH ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (void*,struct ETF_hookinfo*) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 struct ETF_hookinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_etf_newhook(node_p node, hook_p hook, const char *name)
{
	const etf_p etfp = NG_NODE_PRIVATE(node);
	struct ETF_hookinfo *hpriv;

	if (strcmp(name, NG_ETF_HOOK_DOWNSTREAM) == 0) {
		etfp->downstream_hook.hook = hook;
		NG_HOOK_SET_PRIVATE(hook, &etfp->downstream_hook);
		etfp->packets_in = 0;
		etfp->packets_out = 0;
	} else if (strcmp(name, NG_ETF_HOOK_NOMATCH) == 0) {
		etfp->nomatch_hook.hook = hook;
		NG_HOOK_SET_PRIVATE(hook, &etfp->nomatch_hook);
	} else {
		/*
		 * Any other hook name is valid and can
		 * later be associated with a filter rule.
		 */
		hpriv = malloc(sizeof(*hpriv),
			M_NETGRAPH_ETF, M_NOWAIT | M_ZERO);
		if (hpriv == NULL) {
			return (ENOMEM);
		}

		NG_HOOK_SET_PRIVATE(hook, hpriv);
		hpriv->hook = hook;
	}
	return(0);
}