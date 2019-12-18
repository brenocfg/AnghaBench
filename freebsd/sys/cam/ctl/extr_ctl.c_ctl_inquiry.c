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
typedef  union ctl_io {int dummy; } ctl_io ;
struct scsi_inquiry {int byte2; scalar_t__ page_code; } ;
struct ctl_scsiio {scalar_t__ cdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int CTL_RETVAL_COMPLETE ; 
 int SI_EVPD ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int ctl_inquiry_evpd (struct ctl_scsiio*) ; 
 int ctl_inquiry_std (struct ctl_scsiio*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ctl_inquiry(struct ctl_scsiio *ctsio)
{
	struct scsi_inquiry *cdb;
	int retval;

	CTL_DEBUG_PRINT(("ctl_inquiry\n"));

	cdb = (struct scsi_inquiry *)ctsio->cdb;
	if (cdb->byte2 & SI_EVPD)
		retval = ctl_inquiry_evpd(ctsio);
	else if (cdb->page_code == 0)
		retval = ctl_inquiry_std(ctsio);
	else {
		ctl_set_invalid_field(ctsio,
				      /*sks_valid*/ 1,
				      /*command*/ 1,
				      /*field*/ 2,
				      /*bit_valid*/ 0,
				      /*bit*/ 0);
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}

	return (retval);
}