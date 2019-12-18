#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* path; void* status; } ;
struct ccb_dev_advinfo {int buftype; int flags; int /*<<< orphan*/ * buf; int /*<<< orphan*/  bufsiz; int /*<<< orphan*/  provsiz; } ;
union ccb {TYPE_1__ ccb_h; struct ccb_dev_advinfo cdai; } ;
struct cam_ed {int /*<<< orphan*/ * ext_inq; int /*<<< orphan*/  ext_inq_len; int /*<<< orphan*/ * rcap_buf; int /*<<< orphan*/  rcap_len; int /*<<< orphan*/ * physpath; int /*<<< orphan*/  physpath_len; int /*<<< orphan*/ * serial_num; int /*<<< orphan*/  serial_num_len; int /*<<< orphan*/ * device_id; int /*<<< orphan*/  device_id_len; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_5__ {struct cam_ed* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ADVINFO_CHANGED ; 
 void* CAM_REQ_ABORTED ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_INVALID ; 
 int CDAI_FLAG_STORE ; 
#define  CDAI_TYPE_EXT_INQ 132 
#define  CDAI_TYPE_PHYS_PATH 131 
#define  CDAI_TYPE_RCAPLONG 130 
#define  CDAI_TYPE_SCSI_DEVID 129 
#define  CDAI_TYPE_SERIAL_NUM 128 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  xpt_path_assert (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scsi_dev_advinfo(union ccb *start_ccb)
{
	struct cam_ed *device;
	struct ccb_dev_advinfo *cdai;
	off_t amt;

	xpt_path_assert(start_ccb->ccb_h.path, MA_OWNED);
	start_ccb->ccb_h.status = CAM_REQ_INVALID;
	device = start_ccb->ccb_h.path->device;
	cdai = &start_ccb->cdai;
	switch(cdai->buftype) {
	case CDAI_TYPE_SCSI_DEVID:
		if (cdai->flags & CDAI_FLAG_STORE)
			return;
		cdai->provsiz = device->device_id_len;
		if (device->device_id_len == 0)
			break;
		amt = device->device_id_len;
		if (cdai->provsiz > cdai->bufsiz)
			amt = cdai->bufsiz;
		memcpy(cdai->buf, device->device_id, amt);
		break;
	case CDAI_TYPE_SERIAL_NUM:
		if (cdai->flags & CDAI_FLAG_STORE)
			return;
		cdai->provsiz = device->serial_num_len;
		if (device->serial_num_len == 0)
			break;
		amt = device->serial_num_len;
		if (cdai->provsiz > cdai->bufsiz)
			amt = cdai->bufsiz;
		memcpy(cdai->buf, device->serial_num, amt);
		break;
	case CDAI_TYPE_PHYS_PATH:
		if (cdai->flags & CDAI_FLAG_STORE) {
			if (device->physpath != NULL) {
				free(device->physpath, M_CAMXPT);
				device->physpath = NULL;
				device->physpath_len = 0;
			}
			/* Clear existing buffer if zero length */
			if (cdai->bufsiz == 0)
				break;
			device->physpath = malloc(cdai->bufsiz, M_CAMXPT, M_NOWAIT);
			if (device->physpath == NULL) {
				start_ccb->ccb_h.status = CAM_REQ_ABORTED;
				return;
			}
			device->physpath_len = cdai->bufsiz;
			memcpy(device->physpath, cdai->buf, cdai->bufsiz);
		} else {
			cdai->provsiz = device->physpath_len;
			if (device->physpath_len == 0)
				break;
			amt = device->physpath_len;
			if (cdai->provsiz > cdai->bufsiz)
				amt = cdai->bufsiz;
			memcpy(cdai->buf, device->physpath, amt);
		}
		break;
	case CDAI_TYPE_RCAPLONG:
		if (cdai->flags & CDAI_FLAG_STORE) {
			if (device->rcap_buf != NULL) {
				free(device->rcap_buf, M_CAMXPT);
				device->rcap_buf = NULL;
			}

			device->rcap_len = cdai->bufsiz;
			/* Clear existing buffer if zero length */
			if (cdai->bufsiz == 0)
				break;

			device->rcap_buf = malloc(cdai->bufsiz, M_CAMXPT,
						  M_NOWAIT);
			if (device->rcap_buf == NULL) {
				start_ccb->ccb_h.status = CAM_REQ_ABORTED;
				return;
			}

			memcpy(device->rcap_buf, cdai->buf, cdai->bufsiz);
		} else {
			cdai->provsiz = device->rcap_len;
			if (device->rcap_len == 0)
				break;
			amt = device->rcap_len;
			if (cdai->provsiz > cdai->bufsiz)
				amt = cdai->bufsiz;
			memcpy(cdai->buf, device->rcap_buf, amt);
		}
		break;
	case CDAI_TYPE_EXT_INQ:
		/*
		 * We fetch extended inquiry data during probe, if
		 * available.  We don't allow changing it.
		 */
		if (cdai->flags & CDAI_FLAG_STORE)
			return;
		cdai->provsiz = device->ext_inq_len;
		if (device->ext_inq_len == 0)
			break;
		amt = device->ext_inq_len;
		if (cdai->provsiz > cdai->bufsiz)
			amt = cdai->bufsiz;
		memcpy(cdai->buf, device->ext_inq, amt);
		break;
	default:
		return;
	}
	start_ccb->ccb_h.status = CAM_REQ_CMP;

	if (cdai->flags & CDAI_FLAG_STORE) {
		xpt_async(AC_ADVINFO_CHANGED, start_ccb->ccb_h.path,
			  (void *)(uintptr_t)cdai->buftype);
	}
}