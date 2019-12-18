#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ model; } ;
struct psm_softc {int config; int /*<<< orphan*/  unit; int /*<<< orphan*/  flags; TYPE_1__ hw; int /*<<< orphan*/  kbdc; } ;
struct TYPE_6__ {int /*<<< orphan*/  resolution; int /*<<< orphan*/  rate; } ;
typedef  TYPE_2__ mousemode_t ;
struct TYPE_7__ {scalar_t__ model; int /*<<< orphan*/  (* probefunc ) (struct psm_softc*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
#define  PSM_ACK 128 
 int PSM_CONFIG_IGNPORTERROR ; 
 int PSM_CONFIG_NORESET ; 
 int /*<<< orphan*/  PSM_NEED_SYNCBITS ; 
 int /*<<< orphan*/  REINIT ; 
 int TRUE ; 
 int /*<<< orphan*/  disable_aux_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enable_aux_dev (int /*<<< orphan*/ ) ; 
 int get_mouse_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  recover_from_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_aux_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mouse_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mouse_resolution (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mouse_sampling_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mouse_scaling (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct psm_softc*,int /*<<< orphan*/ ) ; 
 int test_aux_port (int /*<<< orphan*/ ) ; 
 TYPE_3__* vendortype ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int
doinitialize(struct psm_softc *sc, mousemode_t *mode)
{
	KBDC kbdc = sc->kbdc;
	int stat[3];
	int i;

	switch((i = test_aux_port(kbdc))) {
	case 1:	/* ignore these errors */
	case 2:
	case 3:
	case PSM_ACK:
		if (verbose)
			log(LOG_DEBUG,
			    "psm%d: strange result for test aux port (%d).\n",
			    sc->unit, i);
		/* FALLTHROUGH */
	case 0:		/* no error */
		break;
	case -1:	/* time out */
	default:	/* error */
		recover_from_error(kbdc);
		if (sc->config & PSM_CONFIG_IGNPORTERROR)
			break;
		log(LOG_ERR, "psm%d: the aux port is not functioning (%d).\n",
		    sc->unit, i);
		return (FALSE);
	}

	if (sc->config & PSM_CONFIG_NORESET) {
		/*
		 * Don't try to reset the pointing device.  It may possibly
		 * be left in the unknown state, though...
		 */
	} else {
		/*
		 * NOTE: some controllers appears to hang the `keyboard' when
		 * the aux port doesn't exist and `PSMC_RESET_DEV' is issued.
		 */
		if (!reset_aux_dev(kbdc)) {
			recover_from_error(kbdc);
			log(LOG_ERR, "psm%d: failed to reset the aux device.\n",
			    sc->unit);
			return (FALSE);
		}
	}

	/*
	 * both the aux port and the aux device is functioning, see
	 * if the device can be enabled.
	 */
	if (!enable_aux_dev(kbdc) || !disable_aux_dev(kbdc)) {
		log(LOG_ERR, "psm%d: failed to enable the aux device.\n",
		    sc->unit);
		return (FALSE);
	}
	empty_both_buffers(kbdc, 10);	/* remove stray data if any */

	/* Re-enable the mouse. */
	for (i = 0; vendortype[i].probefunc != NULL; ++i)
		if (vendortype[i].model == sc->hw.model)
			(*vendortype[i].probefunc)(sc, REINIT);

	/* set mouse parameters */
	if (mode != (mousemode_t *)NULL) {
		if (mode->rate > 0)
			mode->rate = set_mouse_sampling_rate(kbdc, mode->rate);
		if (mode->resolution >= 0)
			mode->resolution =
			    set_mouse_resolution(kbdc, mode->resolution);
		set_mouse_scaling(kbdc, 1);
		set_mouse_mode(kbdc);
	}

	/* Record sync on the next data packet we see. */
	sc->flags |= PSM_NEED_SYNCBITS;

	/* just check the status of the mouse */
	if (get_mouse_status(kbdc, stat, 0, 3) < 3)
		log(LOG_DEBUG, "psm%d: failed to get status (doinitialize).\n",
		    sc->unit);

	return (TRUE);
}