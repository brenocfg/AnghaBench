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
struct TYPE_4__ {TYPE_2__* path; int /*<<< orphan*/  status; } ;
struct ccb_dev_advinfo {int buftype; int flags; void* provsiz; void* bufsiz; int /*<<< orphan*/ * buf; } ;
union ccb {TYPE_1__ ccb_h; struct ccb_dev_advinfo cdai; } ;
struct nvme_namespace_data {int dummy; } ;
struct nvme_controller_data {int dummy; } ;
struct cam_ed {void* device_id_len; void* serial_num_len; void* physpath_len; int /*<<< orphan*/ * nvme_data; int /*<<< orphan*/ * nvme_cdata; int /*<<< orphan*/ * physpath; int /*<<< orphan*/ * serial_num; int /*<<< orphan*/ * device_id; } ;
typedef  void* off_t ;
struct TYPE_5__ {struct cam_ed* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ADVINFO_CHANGED ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int CDAI_FLAG_STORE ; 
#define  CDAI_TYPE_NVME_CNTRL 132 
#define  CDAI_TYPE_NVME_NS 131 
#define  CDAI_TYPE_PHYS_PATH 130 
#define  CDAI_TYPE_SCSI_DEVID 129 
#define  CDAI_TYPE_SERIAL_NUM 128 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  xpt_path_assert (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_dev_advinfo(union ccb *start_ccb)
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
			if (device->physpath != NULL)
				free(device->physpath, M_CAMXPT);
			device->physpath_len = cdai->bufsiz;
			/* Clear existing buffer if zero length */
			if (cdai->bufsiz == 0)
				break;
			device->physpath = malloc(cdai->bufsiz, M_CAMXPT, M_NOWAIT);
			if (device->physpath == NULL) {
				start_ccb->ccb_h.status = CAM_REQ_ABORTED;
				return;
			}
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
	case CDAI_TYPE_NVME_CNTRL:
		if (cdai->flags & CDAI_FLAG_STORE)
			return;
		amt = sizeof(struct nvme_controller_data);
		cdai->provsiz = amt;
		if (amt > cdai->bufsiz)
			amt = cdai->bufsiz;
		memcpy(cdai->buf, device->nvme_cdata, amt);
		break;
	case CDAI_TYPE_NVME_NS:
		if (cdai->flags & CDAI_FLAG_STORE)
			return;
		amt = sizeof(struct nvme_namespace_data);
		cdai->provsiz = amt;
		if (amt > cdai->bufsiz)
			amt = cdai->bufsiz;
		memcpy(cdai->buf, device->nvme_data, amt);
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