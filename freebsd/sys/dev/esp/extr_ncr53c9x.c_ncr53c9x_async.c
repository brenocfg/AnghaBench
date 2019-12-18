#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  width; int /*<<< orphan*/  offset; int /*<<< orphan*/  period; } ;
struct TYPE_3__ {int /*<<< orphan*/  width; int /*<<< orphan*/  offset; int /*<<< orphan*/  period; } ;
struct ncr53c9x_tinfo {int flags; TYPE_2__ goal; TYPE_1__ curr; } ;
struct ncr53c9x_softc {int sc_ntarg; int sc_cfflags; int /*<<< orphan*/  sc_minsync; struct ncr53c9x_tinfo* sc_tinfo; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
#define  AC_LOST_DEVICE 128 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  NCR_LOCK_ASSERT (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int T_RSELECTOFF ; 
 int T_SYNCHOFF ; 
 struct ncr53c9x_softc* cam_sim_softc (void*) ; 
 int /*<<< orphan*/  ncr53c9x_clear_target (struct ncr53c9x_softc*,int,int /*<<< orphan*/ ) ; 
 int xpt_path_target_id (struct cam_path*) ; 

__attribute__((used)) static void
ncr53c9x_async(void *cbarg, uint32_t code, struct cam_path *path, void *arg)
{
	struct ncr53c9x_softc *sc;
	struct ncr53c9x_tinfo *ti;
	int target;

	sc = cam_sim_softc(cbarg);

	NCR_LOCK_ASSERT(sc, MA_OWNED);

	switch (code) {
	case AC_LOST_DEVICE:
		target = xpt_path_target_id(path);
		if (target < 0 || target >= sc->sc_ntarg)
			break;

		/* Cancel outstanding disconnected commands. */
		ncr53c9x_clear_target(sc, target, CAM_REQ_ABORTED);

		/* Set the default parameters for the target. */
		ti = &sc->sc_tinfo[target];
/* XXX - config flags per target: low bits: no reselect; high bits: no synch */
		ti->flags = ((sc->sc_minsync != 0 &&
		    (sc->sc_cfflags & (1 << ((target & 7) + 8))) == 0) ?
		    0 : T_SYNCHOFF) |
		    ((sc->sc_cfflags & (1 << (target & 7))) == 0 ?
		    0 : T_RSELECTOFF);
		ti->curr.period = ti->goal.period = 0;
		ti->curr.offset = ti->goal.offset = 0;
		ti->curr.width = ti->goal.width = MSG_EXT_WDTR_BUS_8_BIT;
		break;
	}
}