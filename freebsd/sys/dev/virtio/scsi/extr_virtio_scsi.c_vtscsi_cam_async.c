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
typedef  int uint32_t ;
struct vtscsi_softc {int dummy; } ;
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
#define  AC_FOUND_DEVICE 129 
#define  AC_LOST_DEVICE 128 
 int /*<<< orphan*/  VTSCSI_TRACE ; 
 struct vtscsi_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
vtscsi_cam_async(void *cb_arg, uint32_t code, struct cam_path *path, void *arg)
{
	struct cam_sim *sim;
	struct vtscsi_softc *sc;

	sim = cb_arg;
	sc = cam_sim_softc(sim);

	vtscsi_dprintf(sc, VTSCSI_TRACE, "code=%u\n", code);

	/*
	 * TODO Once QEMU supports event reporting, we should
	 *      (un)subscribe to events here.
	 */
	switch (code) {
	case AC_FOUND_DEVICE:
		break;
	case AC_LOST_DEVICE:
		break;
	}
}