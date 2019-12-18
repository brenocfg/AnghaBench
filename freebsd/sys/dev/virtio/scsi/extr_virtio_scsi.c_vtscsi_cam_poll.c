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
struct vtscsi_softc {int dummy; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 struct vtscsi_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  vtscsi_complete_vqs_locked (struct vtscsi_softc*) ; 

__attribute__((used)) static void
vtscsi_cam_poll(struct cam_sim *sim)
{
	struct vtscsi_softc *sc;

	sc = cam_sim_softc(sim);

	vtscsi_complete_vqs_locked(sc);
}