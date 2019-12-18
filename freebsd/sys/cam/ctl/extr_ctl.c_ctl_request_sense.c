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
typedef  union ctl_io {int dummy; } ctl_io ;
typedef  int uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct scsi_sense_data_fixed {int dummy; } ;
struct scsi_sense_data_desc {int dummy; } ;
struct scsi_sense_data {scalar_t__ error_code; } ;
struct scsi_request_sense {int byte2; int /*<<< orphan*/  length; } ;
struct ctl_softc {scalar_t__ ha_link; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  nexus; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_2__ io_hdr; int /*<<< orphan*/  kern_total_len; int /*<<< orphan*/  kern_data_len; scalar_t__ kern_rel_offset; scalar_t__ kern_sg_entries; scalar_t__ kern_data_ptr; scalar_t__ cdb; } ;
struct TYPE_3__ {scalar_t__ mrie; } ;
struct ctl_lun {int flags; int ie_asc; int ie_ascq; int /*<<< orphan*/  lun_lock; TYPE_1__ MODE_IE; struct scsi_sense_data** pending_sense; } ;
typedef  scalar_t__ scsi_sense_data_type ;
typedef  scalar_t__ ctl_ua_type ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 scalar_t__ CTL_HA_LINK_UNKNOWN ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_LUN_PRIMARY_SC ; 
 size_t CTL_MAX_INIT_PER_PORT ; 
 int CTL_RETVAL_COMPLETE ; 
 struct ctl_softc* CTL_SOFTC (struct ctl_scsiio*) ; 
 scalar_t__ CTL_UA_NONE ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ SIEP_MRIE_NO ; 
 int SRS_DESC ; 
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  SSD_KEY_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SSD_KEY_NO_SENSE ; 
 scalar_t__ SSD_TYPE_DESC ; 
 scalar_t__ SSD_TYPE_FIXED ; 
 scalar_t__ ctl_build_ua (struct ctl_lun*,size_t,struct scsi_sense_data*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 size_t ctl_get_initindex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_sense_to_desc (struct scsi_sense_data_fixed*,struct scsi_sense_data_desc*) ; 
 int /*<<< orphan*/  ctl_sense_to_fixed (struct scsi_sense_data_desc*,struct scsi_sense_data_fixed*) ; 
 int /*<<< orphan*/  ctl_set_sense_data (struct scsi_sense_data*,int /*<<< orphan*/ *,struct ctl_lun*,scalar_t__,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct scsi_sense_data*,struct scsi_sense_data*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_sense_type (struct scsi_sense_data*) ; 

int
ctl_request_sense(struct ctl_scsiio *ctsio)
{
	struct ctl_softc *softc = CTL_SOFTC(ctsio);
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_request_sense *cdb;
	struct scsi_sense_data *sense_ptr, *ps;
	uint32_t initidx;
	int have_error;
	u_int sense_len = SSD_FULL_SIZE;
	scsi_sense_data_type sense_format;
	ctl_ua_type ua_type;
	uint8_t asc = 0, ascq = 0;

	cdb = (struct scsi_request_sense *)ctsio->cdb;

	CTL_DEBUG_PRINT(("ctl_request_sense\n"));

	/*
	 * Determine which sense format the user wants.
	 */
	if (cdb->byte2 & SRS_DESC)
		sense_format = SSD_TYPE_DESC;
	else
		sense_format = SSD_TYPE_FIXED;

	ctsio->kern_data_ptr = malloc(sizeof(*sense_ptr), M_CTL, M_WAITOK);
	sense_ptr = (struct scsi_sense_data *)ctsio->kern_data_ptr;
	ctsio->kern_sg_entries = 0;
	ctsio->kern_rel_offset = 0;

	/*
	 * struct scsi_sense_data, which is currently set to 256 bytes, is
	 * larger than the largest allowed value for the length field in the
	 * REQUEST SENSE CDB, which is 252 bytes as of SPC-4.
	 */
	ctsio->kern_data_len = cdb->length;
	ctsio->kern_total_len = cdb->length;

	/*
	 * If we don't have a LUN, we don't have any pending sense.
	 */
	if (lun == NULL ||
	    ((lun->flags & CTL_LUN_PRIMARY_SC) == 0 &&
	     softc->ha_link < CTL_HA_LINK_UNKNOWN)) {
		/* "Logical unit not supported" */
		ctl_set_sense_data(sense_ptr, &sense_len, NULL, sense_format,
		    /*current_error*/ 1,
		    /*sense_key*/ SSD_KEY_ILLEGAL_REQUEST,
		    /*asc*/ 0x25,
		    /*ascq*/ 0x00,
		    SSD_ELEM_NONE);
		goto send;
	}

	have_error = 0;
	initidx = ctl_get_initindex(&ctsio->io_hdr.nexus);
	/*
	 * Check for pending sense, and then for pending unit attentions.
	 * Pending sense gets returned first, then pending unit attentions.
	 */
	mtx_lock(&lun->lun_lock);
	ps = lun->pending_sense[initidx / CTL_MAX_INIT_PER_PORT];
	if (ps != NULL)
		ps += initidx % CTL_MAX_INIT_PER_PORT;
	if (ps != NULL && ps->error_code != 0) {
		scsi_sense_data_type stored_format;

		/*
		 * Check to see which sense format was used for the stored
		 * sense data.
		 */
		stored_format = scsi_sense_type(ps);

		/*
		 * If the user requested a different sense format than the
		 * one we stored, then we need to convert it to the other
		 * format.  If we're going from descriptor to fixed format
		 * sense data, we may lose things in translation, depending
		 * on what options were used.
		 *
		 * If the stored format is SSD_TYPE_NONE (i.e. invalid),
		 * for some reason we'll just copy it out as-is.
		 */
		if ((stored_format == SSD_TYPE_FIXED)
		 && (sense_format == SSD_TYPE_DESC))
			ctl_sense_to_desc((struct scsi_sense_data_fixed *)
			    ps, (struct scsi_sense_data_desc *)sense_ptr);
		else if ((stored_format == SSD_TYPE_DESC)
		      && (sense_format == SSD_TYPE_FIXED))
			ctl_sense_to_fixed((struct scsi_sense_data_desc *)
			    ps, (struct scsi_sense_data_fixed *)sense_ptr);
		else
			memcpy(sense_ptr, ps, sizeof(*sense_ptr));

		ps->error_code = 0;
		have_error = 1;
	} else {
		ua_type = ctl_build_ua(lun, initidx, sense_ptr, &sense_len,
		    sense_format);
		if (ua_type != CTL_UA_NONE)
			have_error = 1;
	}
	if (have_error == 0) {
		/*
		 * Report informational exception if have one and allowed.
		 */
		if (lun->MODE_IE.mrie != SIEP_MRIE_NO) {
			asc = lun->ie_asc;
			ascq = lun->ie_ascq;
		}
		ctl_set_sense_data(sense_ptr, &sense_len, lun, sense_format,
		    /*current_error*/ 1,
		    /*sense_key*/ SSD_KEY_NO_SENSE,
		    /*asc*/ asc,
		    /*ascq*/ ascq,
		    SSD_ELEM_NONE);
	}
	mtx_unlock(&lun->lun_lock);

send:
	/*
	 * We report the SCSI status as OK, since the status of the command
	 * itself is OK.  We're reporting sense as parameter data.
	 */
	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}