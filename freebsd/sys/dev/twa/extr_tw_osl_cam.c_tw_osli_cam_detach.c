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
struct twa_softc {int /*<<< orphan*/  sim_lock; scalar_t__ sim; scalar_t__ path; } ;
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cam_sim_free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (scalar_t__) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (scalar_t__) ; 

TW_VOID
tw_osli_cam_detach(struct twa_softc *sc)
{
	tw_osli_dbg_dprintf(3, sc, "entered");

	mtx_lock(sc->sim_lock);
           
	if (sc->path)
		xpt_free_path(sc->path);
	if (sc->sim) {
		xpt_bus_deregister(cam_sim_path(sc->sim));
		/* Passing TRUE to cam_sim_free will free the devq as well. */
		cam_sim_free(sc->sim, TRUE);
	}
	/* It's ok have 1 hold count while destroying the mutex */
	mtx_destroy(sc->sim_lock);
}