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
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;
typedef  TYPE_1__* bt3c_softc_p ;
struct TYPE_2__ {int /*<<< orphan*/  inq; int /*<<< orphan*/  stat; int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_BT3C_STAT_IERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 scalar_t__ NG_HOOK_IS_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  _IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 

__attribute__((used)) static void
bt3c_forward(node_p node, hook_p hook, void *arg1, int arg2)
{
	bt3c_softc_p	 sc = (bt3c_softc_p) NG_NODE_PRIVATE(node);
	struct mbuf	*m = NULL;
	int		 error;

	if (sc == NULL)
		return;

	if (sc->hook != NULL && NG_HOOK_IS_VALID(sc->hook)) {
		for (;;) {
			IF_DEQUEUE(&sc->inq, m);
			if (m == NULL)
				break;

			NG_SEND_DATA_ONLY(error, sc->hook, m);
			if (error != 0)
				NG_BT3C_STAT_IERROR(sc->stat);
		}
	} else {
		IF_LOCK(&sc->inq);
		for (;;) {
			_IF_DEQUEUE(&sc->inq, m);
			if (m == NULL)
				break;

			NG_BT3C_STAT_IERROR(sc->stat);
			NG_FREE_M(m);
		}
		IF_UNLOCK(&sc->inq);
	}
}