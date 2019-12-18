#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * hook_p ;
typedef  TYPE_1__* bt3c_softc_p ;
struct TYPE_2__ {int /*<<< orphan*/ * hook; int /*<<< orphan*/  outq; int /*<<< orphan*/  inq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IF_DRAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_bt3c_disconnect(hook_p hook)
{
	bt3c_softc_p	sc = (bt3c_softc_p) NG_NODE_PRIVATE(NG_HOOK_NODE(hook));

	/*
	 * We need to check for sc != NULL because we can be called from
	 * bt3c_pccard_detach() via ng_rmnode_self()
	 */

	if (sc != NULL) {
		if (hook != sc->hook)
			return (EINVAL);

		IF_DRAIN(&sc->inq);
		IF_DRAIN(&sc->outq);

		sc->hook = NULL;
	}

	return (0);
}