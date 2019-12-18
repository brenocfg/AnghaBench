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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  size_t u_int ;
struct scsi_report_luns_data {TYPE_2__* luns; int /*<<< orphan*/  length; } ;
struct cam_path {TYPE_1__* target; } ;
typedef  int probe_flags ;
typedef  scalar_t__ lun_id_t ;
struct TYPE_4__ {int /*<<< orphan*/ * lundata; } ;
struct TYPE_3__ {int /*<<< orphan*/  luns_mtx; struct scsi_report_luns_data* luns; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  CAM_CAN_GET_SIMPLE_LUN (struct scsi_report_luns_data*,size_t) ; 
 int /*<<< orphan*/  CAM_GET_LUN (struct scsi_report_luns_data*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  CAM_GET_SIMPLE_LUN (struct scsi_report_luns_data*,size_t,scalar_t__) ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int PROBE_EXTLUN ; 
 int /*<<< orphan*/  free (struct scsi_report_luns_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int scsi_4btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,struct cam_path*,int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_path_id (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_target_id (struct cam_path*) ; 

__attribute__((used)) static void
probe_purge_old(struct cam_path *path, struct scsi_report_luns_data *new,
    probe_flags flags)
{
	struct cam_path *tp;
	struct scsi_report_luns_data *old;
	u_int idx1, idx2, nlun_old, nlun_new;
	lun_id_t this_lun;
	u_int8_t *ol, *nl;

	if (path->target == NULL) {
		return;
	}
	mtx_lock(&path->target->luns_mtx);
	old = path->target->luns;
	path->target->luns = new;
	mtx_unlock(&path->target->luns_mtx);
	if (old == NULL)
		return;
	nlun_old = scsi_4btoul(old->length) / 8;
	nlun_new = scsi_4btoul(new->length) / 8;

	/*
	 * We are not going to assume sorted lists. Deal.
	 */
	for (idx1 = 0; idx1 < nlun_old; idx1++) {
		ol = old->luns[idx1].lundata;
		for (idx2 = 0; idx2 < nlun_new; idx2++) {
			nl = new->luns[idx2].lundata;
			if (memcmp(nl, ol, 8) == 0) {
				break;
			}
		}
		if (idx2 < nlun_new) {
			continue;
		}
		/*
		 * An 'old' item not in the 'new' list.
		 * Nuke it. Except that if it is lun 0,
		 * that would be what the probe state
		 * machine is currently working on,
		 * so we won't do that.
		 */
		CAM_GET_LUN(old, idx1, this_lun);
		if (this_lun == 0) {
			continue;
		}

		/*
		 * We also cannot nuke it if it is
		 * not in a lun format we understand
		 * and replace the LUN with a "simple" LUN
		 * if that is all the HBA supports.
		 */
		if (!(flags & PROBE_EXTLUN)) {
			if (!CAM_CAN_GET_SIMPLE_LUN(old, idx1))
				continue;
			CAM_GET_SIMPLE_LUN(old, idx1, this_lun);
		}

		if (xpt_create_path(&tp, NULL, xpt_path_path_id(path),
		    xpt_path_target_id(path), this_lun) == CAM_REQ_CMP) {
			xpt_async(AC_LOST_DEVICE, tp, NULL);
			xpt_free_path(tp);
		}
	}
	free(old, M_CAMXPT);
}