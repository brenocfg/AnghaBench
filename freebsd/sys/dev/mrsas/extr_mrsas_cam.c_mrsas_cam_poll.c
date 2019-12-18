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
struct mrsas_softc {int msix_vectors; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  mrsas_complete_cmd (struct mrsas_softc*,int) ; 

__attribute__((used)) static void
mrsas_cam_poll(struct cam_sim *sim)
{
	int i;
	struct mrsas_softc *sc = (struct mrsas_softc *)cam_sim_softc(sim);

	if (sc->msix_vectors != 0){
		for (i=0; i<sc->msix_vectors; i++){
			mrsas_complete_cmd(sc, i);
		}
	} else {
		mrsas_complete_cmd(sc, 0);
	}
}