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
struct scsi_sense_data {int dummy; } ;
struct TYPE_4__ {scalar_t__ scsi_status; scalar_t__ sense_resid; scalar_t__ sense_len; struct scsi_sense_data sense_data; } ;
struct TYPE_3__ {scalar_t__ func_code; int status; int flags; } ;
union ccb {TYPE_2__ csio; TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int CAM_AUTOSNS_VALID ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CAM_SENSE_PHYS ; 
 int CAM_SENSE_PTR ; 
 int CAM_STATUS_MASK ; 
 scalar_t__ SCSI_STATUS_CHECK_COND ; 
 scalar_t__ XPT_SCSI_IO ; 
 int /*<<< orphan*/  bcopy (struct scsi_sense_data**,struct scsi_sense_data**,int) ; 
 int /*<<< orphan*/  scsi_extract_sense_len (struct scsi_sense_data*,scalar_t__,int*,int*,int*,int*,int) ; 

int
scsi_extract_sense_ccb(union ccb *ccb,
    int *error_code, int *sense_key, int *asc, int *ascq)
{
	struct scsi_sense_data *sense_data;

	/* Make sure there are some sense data we can access. */
	if (ccb->ccb_h.func_code != XPT_SCSI_IO ||
	    (ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_SCSI_STATUS_ERROR ||
	    (ccb->csio.scsi_status != SCSI_STATUS_CHECK_COND) ||
	    (ccb->ccb_h.status & CAM_AUTOSNS_VALID) == 0 ||
	    (ccb->ccb_h.flags & CAM_SENSE_PHYS))
		return (0);

	if (ccb->ccb_h.flags & CAM_SENSE_PTR)
		bcopy((struct scsi_sense_data **)&ccb->csio.sense_data,
		    &sense_data, sizeof(struct scsi_sense_data *));
	else
		sense_data = &ccb->csio.sense_data;
	scsi_extract_sense_len(sense_data,
	    ccb->csio.sense_len - ccb->csio.sense_resid,
	    error_code, sense_key, asc, ascq, 1);
	if (*error_code == -1)
		return (0);
	return (1);
}