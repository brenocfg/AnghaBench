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
struct ctxinfo {int dlci; scalar_t__ flags; int /*<<< orphan*/ * hook; } ;
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_3__ {int /*<<< orphan*/  datahooks; scalar_t__* ALT; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 struct ctxinfo* NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngfrm_disconnect(hook_p hook)
{
	const sc_p sc = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	struct ctxinfo *const cp = NG_HOOK_PRIVATE(hook);
	int dlci;

	/* If it's a regular dlci hook, then free resources etc.. */
	if (cp != NULL) {
		cp->hook = NULL;
		dlci = cp->dlci;
		if (dlci != -1)
			sc->ALT[dlci] = 0;
		cp->flags = 0;
		sc->datahooks--;
	}
	if ((NG_NODE_NUMHOOKS(NG_HOOK_NODE(hook)) == 0)
	&& (NG_NODE_IS_VALID(NG_HOOK_NODE(hook))))
		ng_rmnode_self(NG_HOOK_NODE(hook));
	return (0);
}