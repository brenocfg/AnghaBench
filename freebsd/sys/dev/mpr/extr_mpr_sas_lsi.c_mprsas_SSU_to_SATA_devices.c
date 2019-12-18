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
struct TYPE_2__ {struct mprsas_softc* ppriv_ptr1; int /*<<< orphan*/  path; int /*<<< orphan*/  target_id; } ;
union ccb {int /*<<< orphan*/  csio; TYPE_1__ ccb_h; } ;
typedef  size_t target_id_t ;
struct mprsas_target {int handle; scalar_t__ stop_at_shutdown; } ;
struct mprsas_softc {int /*<<< orphan*/  sim; struct mprsas_target* targets; } ;
struct mpr_softc {scalar_t__ SSU_refcount; size_t max_devices; int /*<<< orphan*/  SSU_started; struct mprsas_softc* sassc; } ;
typedef  int /*<<< orphan*/  path_str ;
typedef  int /*<<< orphan*/  path_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPR_ERROR ; 
 int /*<<< orphan*/  MPR_FAULT ; 
 int /*<<< orphan*/  MPR_INFO ; 
 int /*<<< orphan*/  MPR_SENSE_LEN ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int RB_NOSYNC ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mpr_lock (struct mpr_softc*) ; 
 int /*<<< orphan*/  mpr_unlock (struct mpr_softc*) ; 
 int /*<<< orphan*/  mprsas_stop_unit_done ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  scsi_start_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_string (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xpt_path_target_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_periph ; 
 int /*<<< orphan*/  xpt_sim_poll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mprsas_SSU_to_SATA_devices(struct mpr_softc *sc, int howto)
{
	struct mprsas_softc *sassc = sc->sassc;
	union ccb *ccb;
	path_id_t pathid = cam_sim_path(sassc->sim);
	target_id_t targetid;
	struct mprsas_target *target;
	char path_str[64];
	int timeout;

	mpr_lock(sc);

	/*
	 * For each target, issue a StartStopUnit command to stop the device.
	 */
	sc->SSU_started = TRUE;
	sc->SSU_refcount = 0;
	for (targetid = 0; targetid < sc->max_devices; targetid++) {
		target = &sassc->targets[targetid];
		if (target->handle == 0x0) {
			continue;
		}

		/*
		 * The stop_at_shutdown flag will be set if this device is
		 * a SATA direct-access end device.
		 */
		if (target->stop_at_shutdown) {
			ccb = xpt_alloc_ccb_nowait();
			if (ccb == NULL) {
				mpr_dprint(sc, MPR_FAULT, "Unable to alloc CCB "
				    "to stop unit.\n");
				return;
			}

			if (xpt_create_path(&ccb->ccb_h.path, xpt_periph,
			    pathid, targetid, CAM_LUN_WILDCARD) !=
			    CAM_REQ_CMP) {
				mpr_dprint(sc, MPR_ERROR, "Unable to create "
				    "path to stop unit.\n");
				xpt_free_ccb(ccb);
				return;
			}
			xpt_path_string(ccb->ccb_h.path, path_str,
			    sizeof(path_str));

			mpr_dprint(sc, MPR_INFO, "Sending StopUnit: path %s "
			    "handle %d\n", path_str, target->handle);

			/*
			 * Issue a START STOP UNIT command for the target.
			 * Increment the SSU counter to be used to count the
			 * number of required replies.
			 */
			mpr_dprint(sc, MPR_INFO, "Incrementing SSU count\n");
			sc->SSU_refcount++;
			ccb->ccb_h.target_id =
			    xpt_path_target_id(ccb->ccb_h.path);
			ccb->ccb_h.ppriv_ptr1 = sassc;
			scsi_start_stop(&ccb->csio,
			    /*retries*/0,
			    mprsas_stop_unit_done,
			    MSG_SIMPLE_Q_TAG,
			    /*start*/FALSE,
			    /*load/eject*/0,
			    /*immediate*/FALSE,
			    MPR_SENSE_LEN,
			    /*timeout*/10000);
			xpt_action(ccb);
		}
	}

	mpr_unlock(sc);

	/*
	 * Timeout after 60 seconds by default or 10 seconds if howto has
	 * RB_NOSYNC set which indicates we're likely handling a panic.
	 */
	timeout = 600;
	if (howto & RB_NOSYNC)
		timeout = 100;

	/*
	 * Wait until all of the SSU commands have completed or time
	 * has expired. Pause for 100ms each time through.  If any
	 * command times out, the target will be reset in the SCSI
	 * command timeout routine.
	 */
	while (sc->SSU_refcount > 0) {
		pause("mprwait", hz/10);
		if (SCHEDULER_STOPPED())
			xpt_sim_poll(sassc->sim);
		
		if (--timeout == 0) {
			mpr_dprint(sc, MPR_ERROR, "Time has expired waiting "
			    "for SSU commands to complete.\n");
			break;
		}
	}
}