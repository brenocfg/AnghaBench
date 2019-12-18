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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_prevent {int how; } ;
struct TYPE_3__ {int /*<<< orphan*/  nexus; } ;
struct ctl_scsiio {TYPE_1__ io_hdr; scalar_t__ cdb; } ;
struct ctl_lun {int flags; TYPE_2__* backend; int /*<<< orphan*/  lun_lock; int /*<<< orphan*/  prevent_count; int /*<<< orphan*/ * prevent; } ;
struct TYPE_4__ {int (* config_write ) (union ctl_io*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_LUN_REMOVABLE ; 
 int CTL_RETVAL_COMPLETE ; 
 int PR_PREVENT ; 
 int /*<<< orphan*/  ctl_clear_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_get_initindex (int /*<<< orphan*/ *) ; 
 scalar_t__ ctl_is_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_invalid_opcode (struct ctl_scsiio*) ; 
 int /*<<< orphan*/  ctl_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (union ctl_io*) ; 

int
ctl_prevent_allow(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_prevent *cdb;
	int retval;
	uint32_t initidx;

	CTL_DEBUG_PRINT(("ctl_prevent_allow\n"));

	cdb = (struct scsi_prevent *)ctsio->cdb;

	if ((lun->flags & CTL_LUN_REMOVABLE) == 0 || lun->prevent == NULL) {
		ctl_set_invalid_opcode(ctsio);
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}

	initidx = ctl_get_initindex(&ctsio->io_hdr.nexus);
	mtx_lock(&lun->lun_lock);
	if ((cdb->how & PR_PREVENT) &&
	    ctl_is_set(lun->prevent, initidx) == 0) {
		ctl_set_mask(lun->prevent, initidx);
		lun->prevent_count++;
	} else if ((cdb->how & PR_PREVENT) == 0 &&
	    ctl_is_set(lun->prevent, initidx)) {
		ctl_clear_mask(lun->prevent, initidx);
		lun->prevent_count--;
	}
	mtx_unlock(&lun->lun_lock);
	retval = lun->backend->config_write((union ctl_io *)ctsio);
	return (retval);
}