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
struct amr_softc {int amr_maxchan; int /*<<< orphan*/ * amr_cam_devq; int /*<<< orphan*/  amr_list_lock; int /*<<< orphan*/ ** amr_cam_sim; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ *) ; 
 struct amr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amr_cam_detach(device_t dev)
{
	struct amr_softc *sc;
	int		chn;

	sc = device_get_softc(dev);
	mtx_lock(&sc->amr_list_lock);
	for (chn = 0; chn < sc->amr_maxchan; chn++) {
		/*
		 * If a sim was allocated for this channel, free it
		 */
		if (sc->amr_cam_sim[chn] != NULL) {
			xpt_bus_deregister(cam_sim_path(sc->amr_cam_sim[chn]));
			cam_sim_free(sc->amr_cam_sim[chn], FALSE);
		}
	}
	mtx_unlock(&sc->amr_list_lock);

	/* Now free the devq */
	if (sc->amr_cam_devq != NULL)
		cam_simq_free(sc->amr_cam_devq);

	return (0);
}