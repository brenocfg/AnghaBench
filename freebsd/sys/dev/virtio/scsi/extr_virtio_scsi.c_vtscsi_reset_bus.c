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
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_flags; int /*<<< orphan*/  vtscsi_dev; int /*<<< orphan*/  vtscsi_sim; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  VTSCSI_FLAG_RESET ; 
 int /*<<< orphan*/  VTSCSI_LOCK_OWNED (struct vtscsi_softc*) ; 
 int VTSCSI_REQUEST ; 
 int VTSCSI_REQUEST_VQ ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vtscsi_announce (struct vtscsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vtscsi_bus_reset_disable ; 
 int /*<<< orphan*/  vtscsi_complete_vqs_locked (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_drain_vqs (struct vtscsi_softc*) ; 
 int vtscsi_reinit (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_stop (struct vtscsi_softc*) ; 
 scalar_t__ vtscsi_thaw_simq (struct vtscsi_softc*,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtscsi_reset_bus(struct vtscsi_softc *sc)
{
	int error;

	VTSCSI_LOCK_OWNED(sc);

	if (vtscsi_bus_reset_disable != 0) {
		device_printf(sc->vtscsi_dev, "bus reset disabled\n");
		return (0);
	}

	sc->vtscsi_flags |= VTSCSI_FLAG_RESET;

	/*
	 * vtscsi_stop() will cause the in-flight requests to be canceled.
	 * Those requests are then completed here so CAM will retry them
	 * after the reset is complete.
	 */
	vtscsi_stop(sc);
	vtscsi_complete_vqs_locked(sc);

	/* Rid the virtqueues of any remaining requests. */
	vtscsi_drain_vqs(sc);

	/*
	 * Any resource shortage that froze the SIMQ cannot persist across
	 * a bus reset so ensure it gets thawed here.
	 */
	if (vtscsi_thaw_simq(sc, VTSCSI_REQUEST | VTSCSI_REQUEST_VQ) != 0)
		xpt_release_simq(sc->vtscsi_sim, 0);

	error = vtscsi_reinit(sc);
	if (error) {
		device_printf(sc->vtscsi_dev,
		    "reinitialization failed, stopping device...\n");
		vtscsi_stop(sc);
	} else
		vtscsi_announce(sc, AC_BUS_RESET, CAM_TARGET_WILDCARD,
		    CAM_LUN_WILDCARD);

	sc->vtscsi_flags &= ~VTSCSI_FLAG_RESET;

	return (error);
}