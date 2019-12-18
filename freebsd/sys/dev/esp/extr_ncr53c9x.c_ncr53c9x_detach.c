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
struct ncr53c9x_softc {int sc_ntarg; struct ncr53c9x_linfo* sc_omess; scalar_t__ sc_omess_self; struct ncr53c9x_linfo* sc_imess; scalar_t__ sc_imess_self; struct ncr53c9x_linfo* sc_tinfo; struct ncr53c9x_linfo* ecb_array; int /*<<< orphan*/  sc_sim; int /*<<< orphan*/  sc_path; int /*<<< orphan*/  sc_watchdog; } ;
struct ncr53c9x_linfo {int /*<<< orphan*/  luns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 struct ncr53c9x_linfo* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct ncr53c9x_linfo* LIST_NEXT (struct ncr53c9x_linfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  NCR_LOCK (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  NCR_UNLOCK (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ncr53c9x_linfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  ncr53c9x_async ; 
 int /*<<< orphan*/  ncr53c9x_clear (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_register_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ncr53c9x_detach(struct ncr53c9x_softc *sc)
{
	struct ncr53c9x_linfo *li, *nextli;
	int t;

	callout_drain(&sc->sc_watchdog);

	NCR_LOCK(sc);

	if (sc->sc_tinfo) {
		/* Cancel all commands. */
		ncr53c9x_clear(sc, CAM_REQ_ABORTED);

		/* Free logical units. */
		for (t = 0; t < sc->sc_ntarg; t++) {
			for (li = LIST_FIRST(&sc->sc_tinfo[t].luns); li;
			    li = nextli) {
				nextli = LIST_NEXT(li, link);
				free(li, M_DEVBUF);
			}
		}
	}

	xpt_register_async(0, ncr53c9x_async, sc->sc_sim, sc->sc_path);
	xpt_free_path(sc->sc_path);
	xpt_bus_deregister(cam_sim_path(sc->sc_sim));
	cam_sim_free(sc->sc_sim, TRUE);

	NCR_UNLOCK(sc);

	free(sc->ecb_array, M_DEVBUF);
	free(sc->sc_tinfo, M_DEVBUF);
	if (sc->sc_imess_self)
		free(sc->sc_imess, M_DEVBUF);
	if (sc->sc_omess_self)
		free(sc->sc_omess, M_DEVBUF);

	return (0);
}