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
struct mly_softc {int mly_cam_channels; TYPE_1__* mly_controllerinfo; int /*<<< orphan*/  mly_dev; int /*<<< orphan*/ ** mly_cam_sim; int /*<<< orphan*/  mly_lock; } ;
struct cam_devq {int dummy; } ;
struct TYPE_2__ {int physical_channels_present; int virtual_channels_present; int /*<<< orphan*/  maximum_parallel_commands; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MLY_LOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_UNLOCK (struct mly_softc*) ; 
 void* cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mly_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct cam_devq*) ; 
 struct cam_devq* cam_simq_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (int,char*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mly_cam_action ; 
 int /*<<< orphan*/  mly_cam_poll ; 
 int /*<<< orphan*/  mly_printf (struct mly_softc*,char*) ; 
 scalar_t__ testenv (char*) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mly_cam_attach(struct mly_softc *sc)
{
    struct cam_devq	*devq;
    int			chn, i;

    debug_called(1);

    /*
     * Allocate a devq for all our channels combined.
     */
    if ((devq = cam_simq_alloc(sc->mly_controllerinfo->maximum_parallel_commands)) == NULL) {
	mly_printf(sc, "can't allocate CAM SIM queue\n");
	return(ENOMEM);
    }

    /*
     * If physical channel registration has been requested, register these first.
     * Note that we enable tagged command queueing for physical channels.
     */
    if (testenv("hw.mly.register_physical_channels")) {
	chn = 0;
	for (i = 0; i < sc->mly_controllerinfo->physical_channels_present; i++, chn++) {

	    if ((sc->mly_cam_sim[chn] = cam_sim_alloc(mly_cam_action, mly_cam_poll, "mly", sc,
						      device_get_unit(sc->mly_dev),
						      &sc->mly_lock,
						      sc->mly_controllerinfo->maximum_parallel_commands,
						      1, devq)) == NULL) {
		return(ENOMEM);
	    }
	    MLY_LOCK(sc);
	    if (xpt_bus_register(sc->mly_cam_sim[chn], sc->mly_dev, chn)) {
		MLY_UNLOCK(sc);
		mly_printf(sc, "CAM XPT phsyical channel registration failed\n");
		return(ENXIO);
	    }
	    MLY_UNLOCK(sc);
	    debug(1, "registered physical channel %d", chn);
	}
    }

    /*
     * Register our virtual channels, with bus numbers matching channel numbers.
     */
    chn = sc->mly_controllerinfo->physical_channels_present;
    for (i = 0; i < sc->mly_controllerinfo->virtual_channels_present; i++, chn++) {
	if ((sc->mly_cam_sim[chn] = cam_sim_alloc(mly_cam_action, mly_cam_poll, "mly", sc,
						  device_get_unit(sc->mly_dev),
						  &sc->mly_lock,
						  sc->mly_controllerinfo->maximum_parallel_commands,
						  0, devq)) == NULL) {
	    return(ENOMEM);
	}
	MLY_LOCK(sc);
	if (xpt_bus_register(sc->mly_cam_sim[chn], sc->mly_dev, chn)) {
	    MLY_UNLOCK(sc);
	    mly_printf(sc, "CAM XPT virtual channel registration failed\n");
	    return(ENXIO);
	}
	MLY_UNLOCK(sc);
	debug(1, "registered virtual channel %d", chn);
    }

    /*
     * This is the total number of channels that (might have been) registered with
     * CAM.  Some may not have been; check the mly_cam_sim array to be certain.
     */
    sc->mly_cam_channels = sc->mly_controllerinfo->physical_channels_present +
	sc->mly_controllerinfo->virtual_channels_present;

    return(0);
}