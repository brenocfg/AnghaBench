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
typedef  union ctl_io {int dummy; } ctl_io ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tpc_list {int abort; } ;
struct scsi_copy_operation_abort {int /*<<< orphan*/  list_identifier; } ;
struct TYPE_2__ {int /*<<< orphan*/  nexus; } ;
struct ctl_scsiio {TYPE_1__ io_hdr; scalar_t__ cdb; } ;
struct ctl_lun {int /*<<< orphan*/  lun_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_get_initindex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_4btoul (int /*<<< orphan*/ ) ; 
 struct tpc_list* tpc_find_list (struct ctl_lun*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ctl_copy_operation_abort(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_copy_operation_abort *cdb;
	struct tpc_list *list;
	int retval;
	uint32_t list_id;

	CTL_DEBUG_PRINT(("ctl_copy_operation_abort\n"));

	cdb = (struct scsi_copy_operation_abort *)ctsio->cdb;
	retval = CTL_RETVAL_COMPLETE;

	list_id = scsi_4btoul(cdb->list_identifier);
	mtx_lock(&lun->lun_lock);
	list = tpc_find_list(lun, list_id,
	    ctl_get_initindex(&ctsio->io_hdr.nexus));
	if (list == NULL) {
		mtx_unlock(&lun->lun_lock);
		ctl_set_invalid_field(ctsio, /*sks_valid*/ 1,
		    /*command*/ 1, /*field*/ 2, /*bit_valid*/ 0,
		    /*bit*/ 0);
		ctl_done((union ctl_io *)ctsio);
		return (retval);
	}
	list->abort = 1;
	mtx_unlock(&lun->lun_lock);

	ctl_set_success(ctsio);
	ctl_done((union ctl_io *)ctsio);
	return (retval);
}