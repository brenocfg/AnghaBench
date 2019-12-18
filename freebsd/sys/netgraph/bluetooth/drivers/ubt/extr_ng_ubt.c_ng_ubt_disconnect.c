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
struct ubt_softc {int /*<<< orphan*/  sc_scoq; int /*<<< orphan*/  sc_aclq; int /*<<< orphan*/  sc_cmdq; int /*<<< orphan*/ * sc_hook; } ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_BT_MBUFQ_DRAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 struct ubt_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UBT_FLAG_T_STOP_ALL ; 
 int /*<<< orphan*/  UBT_NG_LOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_NG_UNLOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  ubt_task_schedule (struct ubt_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_ubt_disconnect(hook_p hook)
{
	struct ubt_softc	*sc = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));

	UBT_NG_LOCK(sc);

	if (hook != sc->sc_hook) {
		UBT_NG_UNLOCK(sc);

		return (EINVAL);
	}

	sc->sc_hook = NULL;

	/* Kick off task to stop all USB xfers */
	ubt_task_schedule(sc, UBT_FLAG_T_STOP_ALL);

	/* Drain queues */
	NG_BT_MBUFQ_DRAIN(&sc->sc_cmdq);
	NG_BT_MBUFQ_DRAIN(&sc->sc_aclq);
	NG_BT_MBUFQ_DRAIN(&sc->sc_scoq);

	UBT_NG_UNLOCK(sc);

	return (0);
}