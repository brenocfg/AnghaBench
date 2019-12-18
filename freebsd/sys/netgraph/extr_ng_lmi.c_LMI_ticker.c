#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_5__ {int flags; scalar_t__ liv_per_full; int liv_rate; int /*<<< orphan*/  handle; int /*<<< orphan*/  livs; } ;

/* Variables and functions */
 int NG_LMI_POLL_RATE ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int SCF_AUTO ; 
 int hz ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int),int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngauto_state_machine (TYPE_1__*) ; 
 int /*<<< orphan*/  nglmi_inquire (TYPE_1__*,int) ; 

__attribute__((used)) static void
LMI_ticker(node_p node, hook_p hook, void *arg1, int arg2)
{
	sc_p sc = NG_NODE_PRIVATE(node);

	if (sc->flags & SCF_AUTO) {
		ngauto_state_machine(sc);
		ng_callout(&sc->handle, node, NULL, NG_LMI_POLL_RATE * hz,
		    LMI_ticker, NULL, 0);
	} else {
		if (sc->livs++ >= sc->liv_per_full) {
			nglmi_inquire(sc, 1);
			/* sc->livs = 0; *//* do this when we get the answer! */
		} else {
			nglmi_inquire(sc, 0);
		}
		ng_callout(&sc->handle, node, NULL, sc->liv_rate * hz,
		    LMI_ticker, NULL, 0);
	}
}