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
struct rum_softc {size_t cmdq_first; struct rum_cmdq* cmdq; } ;
struct rum_cmdq {int /*<<< orphan*/  rvp_id; int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (struct rum_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RUM_CMDQ_LOCK (struct rum_softc*) ; 
 int RUM_CMDQ_SIZE ; 
 int /*<<< orphan*/  RUM_CMDQ_UNLOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  memset (struct rum_cmdq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct rum_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rum_cmdq_cb(void *arg, int pending)
{
	struct rum_softc *sc = arg;
	struct rum_cmdq *rc;

	RUM_CMDQ_LOCK(sc);
	while (sc->cmdq[sc->cmdq_first].func != NULL) {
		rc = &sc->cmdq[sc->cmdq_first];
		RUM_CMDQ_UNLOCK(sc);

		RUM_LOCK(sc);
		rc->func(sc, &rc->data, rc->rvp_id);
		RUM_UNLOCK(sc);

		RUM_CMDQ_LOCK(sc);
		memset(rc, 0, sizeof (*rc));
		sc->cmdq_first = (sc->cmdq_first + 1) % RUM_CMDQ_SIZE;
	}
	RUM_CMDQ_UNLOCK(sc);
}