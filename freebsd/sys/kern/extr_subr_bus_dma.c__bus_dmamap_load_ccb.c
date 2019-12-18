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
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct ccb_nvmeio {int /*<<< orphan*/  sglist_cnt; int /*<<< orphan*/  dxfer_len; void* data_ptr; } ;
struct ccb_ataio {int /*<<< orphan*/  dxfer_len; void* data_ptr; } ;
struct ccb_scsiio {int /*<<< orphan*/  sglist_cnt; int /*<<< orphan*/  dxfer_len; void* data_ptr; } ;
struct ccb_hdr {int func_code; int flags; } ;
union ccb {struct ccb_nvmeio nvmeio; struct ccb_ataio ataio; struct ccb_scsiio ctio; struct ccb_scsiio csio; struct ccb_hdr ccb_h; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
#define  CAM_DATA_BIO 137 
 int CAM_DATA_MASK ; 
#define  CAM_DATA_PADDR 136 
#define  CAM_DATA_SG 135 
#define  CAM_DATA_SG_PADDR 134 
#define  CAM_DATA_VADDR 133 
#define  XPT_ATA_IO 132 
#define  XPT_CONT_TARGET_IO 131 
#define  XPT_NVME_ADMIN 130 
#define  XPT_NVME_IO 129 
#define  XPT_SCSI_IO 128 
 int _bus_dmamap_load_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio*,int*,int) ; 
 int _bus_dmamap_load_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int _bus_dmamap_load_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int _bus_dmamap_load_plist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int _bus_dmamap_load_vlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
_bus_dmamap_load_ccb(bus_dma_tag_t dmat, bus_dmamap_t map, union ccb *ccb,
		    int *nsegs, int flags)
{
	struct ccb_hdr *ccb_h;
	void *data_ptr;
	int error;
	uint32_t dxfer_len;
	uint16_t sglist_cnt;

	error = 0;
	ccb_h = &ccb->ccb_h;
	switch (ccb_h->func_code) {
	case XPT_SCSI_IO: {
		struct ccb_scsiio *csio;

		csio = &ccb->csio;
		data_ptr = csio->data_ptr;
		dxfer_len = csio->dxfer_len;
		sglist_cnt = csio->sglist_cnt;
		break;
	}
	case XPT_CONT_TARGET_IO: {
		struct ccb_scsiio *ctio;

		ctio = &ccb->ctio;
		data_ptr = ctio->data_ptr;
		dxfer_len = ctio->dxfer_len;
		sglist_cnt = ctio->sglist_cnt;
		break;
	}
	case XPT_ATA_IO: {
		struct ccb_ataio *ataio;

		ataio = &ccb->ataio;
		data_ptr = ataio->data_ptr;
		dxfer_len = ataio->dxfer_len;
		sglist_cnt = 0;
		break;
	}
	case XPT_NVME_IO:
	case XPT_NVME_ADMIN: {
		struct ccb_nvmeio *nvmeio;

		nvmeio = &ccb->nvmeio;
		data_ptr = nvmeio->data_ptr;
		dxfer_len = nvmeio->dxfer_len;
		sglist_cnt = nvmeio->sglist_cnt;
		break;
	}
	default:
		panic("_bus_dmamap_load_ccb: Unsupported func code %d",
		    ccb_h->func_code);
	}

	switch ((ccb_h->flags & CAM_DATA_MASK)) {
	case CAM_DATA_VADDR:
		error = _bus_dmamap_load_buffer(dmat, map, data_ptr, dxfer_len,
		    kernel_pmap, flags, NULL, nsegs);
		break;
	case CAM_DATA_PADDR:
		error = _bus_dmamap_load_phys(dmat, map,
		    (vm_paddr_t)(uintptr_t)data_ptr, dxfer_len, flags, NULL,
		    nsegs);
		break;
	case CAM_DATA_SG:
		error = _bus_dmamap_load_vlist(dmat, map,
		    (bus_dma_segment_t *)data_ptr, sglist_cnt, kernel_pmap,
		    nsegs, flags, 0, dxfer_len);
		break;
	case CAM_DATA_SG_PADDR:
		error = _bus_dmamap_load_plist(dmat, map,
		    (bus_dma_segment_t *)data_ptr, sglist_cnt, nsegs, flags);
		break;
	case CAM_DATA_BIO:
		error = _bus_dmamap_load_bio(dmat, map, (struct bio *)data_ptr,
		    nsegs, flags);
		break;
	default:
		panic("_bus_dmamap_load_ccb: flags 0x%X unimplemented",
		    ccb_h->flags);
	}
	return (error);
}