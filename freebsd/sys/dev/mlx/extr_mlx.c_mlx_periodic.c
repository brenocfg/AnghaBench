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
struct TYPE_2__ {scalar_t__ mp_which; scalar_t__ mp_when; int mp_howlong; } ;
struct mlx_softc {int mlx_lastpoll; scalar_t__ mlx_iftype; int /*<<< orphan*/  mlx_timeout; TYPE_1__ mlx_pause; } ;
struct mlx_rebuild_stat {int dummy; } ;
struct mlx_enquiry_old {int dummy; } ;
struct mlx_enquiry {int dummy; } ;
struct mlx_enq_sys_drive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_CMD_ENQSYSDRIVE ; 
 int /*<<< orphan*/  MLX_CMD_ENQUIRY ; 
 int /*<<< orphan*/  MLX_CMD_ENQUIRY_OLD ; 
 int /*<<< orphan*/  MLX_CMD_REBUILDSTAT ; 
 scalar_t__ MLX_IFTYPE_2 ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int MLX_MAXDRIVES ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct mlx_softc*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int hz ; 
 int imax (int,int) ; 
 int /*<<< orphan*/  mlx_done (struct mlx_softc*,int) ; 
 int /*<<< orphan*/  mlx_enquire (struct mlx_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx_pause_action (struct mlx_softc*) ; 
 int /*<<< orphan*/  mlx_periodic_enquiry ; 
 int /*<<< orphan*/  mlx_periodic_rebuild ; 
 int /*<<< orphan*/  sysbeep (int,int) ; 
 int time_second ; 

__attribute__((used)) static void
mlx_periodic(void *data)
{
    struct mlx_softc *sc = (struct mlx_softc *)data;

    debug_called(1);
    MLX_IO_ASSERT_LOCKED(sc);

    /*
     * Run a bus pause? 
     */
    if ((sc->mlx_pause.mp_which != 0) &&
	(sc->mlx_pause.mp_when > 0) &&
	(time_second >= sc->mlx_pause.mp_when)){

	mlx_pause_action(sc);		/* pause is running */
	sc->mlx_pause.mp_when = 0;
	sysbeep(500, hz);

	/* 
	 * Bus pause still running?
	 */
    } else if ((sc->mlx_pause.mp_which != 0) &&
	       (sc->mlx_pause.mp_when == 0)) {

	/* time to stop bus pause? */
	if (time_second >= sc->mlx_pause.mp_howlong) {
	    mlx_pause_action(sc);
	    sc->mlx_pause.mp_which = 0;	/* pause is complete */
	    sysbeep(500, hz);
	} else {
	    sysbeep((time_second % 5) * 100 + 500, hz/8);
	}

	/* 
	 * Run normal periodic activities? 
	 */
    } else if (time_second > (sc->mlx_lastpoll + 10)) {
	sc->mlx_lastpoll = time_second;

	/* 
	 * Check controller status.
	 *
	 * XXX Note that this may not actually launch a command in situations of high load.
	 */
	mlx_enquire(sc, (sc->mlx_iftype == MLX_IFTYPE_2) ? MLX_CMD_ENQUIRY_OLD : MLX_CMD_ENQUIRY, 
		    imax(sizeof(struct mlx_enquiry), sizeof(struct mlx_enquiry_old)), mlx_periodic_enquiry);

	/*
	 * Check system drive status.
	 *
	 * XXX This might be better left to event-driven detection, eg. I/O to an offline
	 *     drive will detect it's offline, rebuilds etc. should detect the drive is back
	 *     online.
	 */
	mlx_enquire(sc, MLX_CMD_ENQSYSDRIVE, sizeof(struct mlx_enq_sys_drive) * MLX_MAXDRIVES, 
			mlx_periodic_enquiry);
		
    }

    /* get drive rebuild/check status */
    /* XXX should check sc->mlx_background if this is only valid while in progress */
    mlx_enquire(sc, MLX_CMD_REBUILDSTAT, sizeof(struct mlx_rebuild_stat), mlx_periodic_rebuild);

    /* deal with possibly-missed interrupts and timed-out commands */
    mlx_done(sc, 1);

    /* reschedule another poll next second or so */
    callout_reset(&sc->mlx_timeout, hz, mlx_periodic, sc);
}