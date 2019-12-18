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
struct TYPE_4__ {int ccb_state; int status; int /*<<< orphan*/  path; } ;
struct TYPE_3__ {scalar_t__ cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; scalar_t__ data_ptr; } ;
union ccb {TYPE_2__ ccb_h; struct ccb_scsiio csio; } ;
struct scsi_mode_sense_6 {int byte2; } ;
struct scsi_mode_header_6 {int dummy; } ;
struct page_element_address_assignment {int /*<<< orphan*/  ndte; int /*<<< orphan*/  fdtea; int /*<<< orphan*/  niee; int /*<<< orphan*/  fieea; int /*<<< orphan*/  nse; int /*<<< orphan*/  fsea; int /*<<< orphan*/  nmte; int /*<<< orphan*/  mtea; } ;
struct ch_softc {int* sc_counts; int /*<<< orphan*/  state; int /*<<< orphan*/  quirks; void** sc_firsts; void* sc_picker; } ;
struct cam_periph {int flags; int /*<<< orphan*/  path; scalar_t__ softc; } ;
typedef  int /*<<< orphan*/  announce_buf ;

/* Variables and functions */
 int CAM_DEV_QFRZN ; 
 int CAM_PERIPH_INVALID ; 
 int CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CAM_STATUS_MASK ; 
 size_t CHET_DT ; 
 size_t CHET_IE ; 
 size_t CHET_MT ; 
 size_t CHET_ST ; 
#define  CH_CCB_PROBE 128 
 int /*<<< orphan*/  CH_Q_BIT_STRING ; 
 int /*<<< orphan*/  CH_Q_NO_DBD ; 
 int /*<<< orphan*/  CH_STATE_NORMAL ; 
 int ERESTART ; 
 int /*<<< orphan*/  M_SCSICH ; 
 char* PLURAL (int) ; 
 int SF_NO_PRINT ; 
 int SF_RETRY_UA ; 
 int SMS_DBD ; 
 int /*<<< orphan*/  cam_periph_invalidate (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unhold (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_release_devq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cherror (union ccb*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ find_mode_page_6 (struct scsi_mode_header_6*) ; 
 int /*<<< orphan*/  free (struct scsi_mode_header_6*,int /*<<< orphan*/ ) ; 
 void* scsi_2btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sense_print (struct ccb_scsiio*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*,int,char*,int,char*,int,char*) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_announce_periph (struct cam_periph*,char*) ; 
 int /*<<< orphan*/  xpt_announce_quirks (struct cam_periph*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static void
chdone(struct cam_periph *periph, union ccb *done_ccb)
{
	struct ch_softc *softc;
	struct ccb_scsiio *csio;

	softc = (struct ch_softc *)periph->softc;
	csio = &done_ccb->csio;

	switch(done_ccb->ccb_h.ccb_state) {
	case CH_CCB_PROBE:
	{
		struct scsi_mode_header_6 *mode_header;
		struct page_element_address_assignment *ea;
		char announce_buf[80];


		mode_header = (struct scsi_mode_header_6 *)csio->data_ptr;

		ea = (struct page_element_address_assignment *)
			find_mode_page_6(mode_header);

		if ((done_ccb->ccb_h.status & CAM_STATUS_MASK) == CAM_REQ_CMP){
			
			softc->sc_firsts[CHET_MT] = scsi_2btoul(ea->mtea);
			softc->sc_counts[CHET_MT] = scsi_2btoul(ea->nmte);
			softc->sc_firsts[CHET_ST] = scsi_2btoul(ea->fsea);
			softc->sc_counts[CHET_ST] = scsi_2btoul(ea->nse);
			softc->sc_firsts[CHET_IE] = scsi_2btoul(ea->fieea);
			softc->sc_counts[CHET_IE] = scsi_2btoul(ea->niee);
			softc->sc_firsts[CHET_DT] = scsi_2btoul(ea->fdtea);
			softc->sc_counts[CHET_DT] = scsi_2btoul(ea->ndte);
			softc->sc_picker = softc->sc_firsts[CHET_MT];

#define PLURAL(c)	(c) == 1 ? "" : "s"
			snprintf(announce_buf, sizeof(announce_buf),
				"%d slot%s, %d drive%s, "
				"%d picker%s, %d portal%s",
		    		softc->sc_counts[CHET_ST],
				PLURAL(softc->sc_counts[CHET_ST]),
		    		softc->sc_counts[CHET_DT],
				PLURAL(softc->sc_counts[CHET_DT]),
		    		softc->sc_counts[CHET_MT],
				PLURAL(softc->sc_counts[CHET_MT]),
		    		softc->sc_counts[CHET_IE],
				PLURAL(softc->sc_counts[CHET_IE]));
#undef PLURAL
			if (announce_buf[0] != '\0') {
				xpt_announce_periph(periph, announce_buf);
				xpt_announce_quirks(periph, softc->quirks,
				    CH_Q_BIT_STRING);
			}
		} else {
			int error;

			error = cherror(done_ccb, CAM_RETRY_SELTO,
					SF_RETRY_UA | SF_NO_PRINT);
			/*
			 * Retry any UNIT ATTENTION type errors.  They
			 * are expected at boot.
			 */
			if (error == ERESTART) {
				/*
				 * A retry was scheduled, so
				 * just return.
				 */
				return;
			} else if (error != 0) {
				struct scsi_mode_sense_6 *sms;
				int frozen, retry_scheduled;

				sms = (struct scsi_mode_sense_6 *)
					done_ccb->csio.cdb_io.cdb_bytes;
				frozen = (done_ccb->ccb_h.status &
				    CAM_DEV_QFRZN) != 0;

				/*
				 * Check to see if block descriptors were
				 * disabled.  Some devices don't like that.
				 * We're taking advantage of the fact that
				 * the first few bytes of the 6 and 10 byte
				 * mode sense commands are the same.  If
				 * block descriptors were disabled, enable
				 * them and re-send the command.
				 */
				if ((sms->byte2 & SMS_DBD) != 0 &&
				    (periph->flags & CAM_PERIPH_INVALID) == 0) {
					sms->byte2 &= ~SMS_DBD;
					xpt_action(done_ccb);
					softc->quirks |= CH_Q_NO_DBD;
					retry_scheduled = 1;
				} else
					retry_scheduled = 0;

				/* Don't wedge this device's queue */
				if (frozen)
					cam_release_devq(done_ccb->ccb_h.path,
						 /*relsim_flags*/0,
						 /*reduction*/0,
						 /*timeout*/0,
						 /*getcount_only*/0);

				if (retry_scheduled)
					return;

				if ((done_ccb->ccb_h.status & CAM_STATUS_MASK)
				    == CAM_SCSI_STATUS_ERROR) 
					scsi_sense_print(&done_ccb->csio);
				else {
					xpt_print(periph->path,
					    "got CAM status %#x\n",
					    done_ccb->ccb_h.status);
				}
				xpt_print(periph->path, "fatal error, failed "
				    "to attach to device\n");

				cam_periph_invalidate(periph);

			}
		}
		softc->state = CH_STATE_NORMAL;
		free(mode_header, M_SCSICH);
		/*
		 * Since our peripheral may be invalidated by an error
		 * above or an external event, we must release our CCB
		 * before releasing the probe lock on the peripheral.
		 * The peripheral will only go away once the last lock
		 * is removed, and we need it around for the CCB release
		 * operation.
		 */
		xpt_release_ccb(done_ccb);
		cam_periph_unhold(periph);
		return;
	}
	default:
		break;
	}
	xpt_release_ccb(done_ccb);
}