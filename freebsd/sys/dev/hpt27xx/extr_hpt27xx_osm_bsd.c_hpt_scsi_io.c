#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_17__ ;
typedef  struct TYPE_36__   TYPE_16__ ;
typedef  struct TYPE_35__   TYPE_15__ ;
typedef  struct TYPE_34__   TYPE_14__ ;
typedef  struct TYPE_33__   TYPE_13__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {int flags; scalar_t__ target_id; scalar_t__ target_lun; void* status; int /*<<< orphan*/  timeout_ch; } ;
struct TYPE_38__ {int* cdb_ptr; int* cdb_bytes; } ;
struct TYPE_30__ {int* data_ptr; int dxfer_len; int sglist_cnt; TYPE_1__ cdb_io; } ;
union ccb {TYPE_11__ ccb_h; TYPE_10__ csio; } ;
struct TYPE_32__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_12__ bus_dma_segment_t ;
struct TYPE_46__ {int data_in; int data_out; int physical_sg; } ;
struct TYPE_44__ {int /*<<< orphan*/  bus; } ;
struct TYPE_45__ {int eot; int /*<<< orphan*/  size; TYPE_7__ addr; } ;
struct TYPE_42__ {int Lba; int nSectors; } ;
struct TYPE_43__ {TYPE_5__ Ide; } ;
struct TYPE_40__ {int logical_sector_size; } ;
struct TYPE_39__ {int sector_size_shift; } ;
struct TYPE_41__ {TYPE_3__ raw; TYPE_2__ array; } ;
struct TYPE_37__ {TYPE_9__ flags; TYPE_8__* psg; int /*<<< orphan*/  buildsgl; int /*<<< orphan*/  done; TYPE_13__* target; TYPE_15__* priv; TYPE_6__ uCmd; } ;
struct TYPE_36__ {int AdditionalLength; int CommandQueue; int* VendorId; int* ProductId; int* ProductRevisionLevel; } ;
struct TYPE_35__ {int /*<<< orphan*/  dma_map; TYPE_8__* psg; union ccb* ccb; } ;
struct TYPE_34__ {int /*<<< orphan*/  io_dmat; int /*<<< orphan*/  vbus; } ;
struct TYPE_33__ {int target_id; int capacity; TYPE_4__ u; int /*<<< orphan*/  type; int /*<<< orphan*/  cmds_per_request; } ;
typedef  TYPE_13__* PVDEV ;
typedef  TYPE_14__* PVBUS_EXT ;
typedef  int /*<<< orphan*/  PVBUS ;
typedef  TYPE_15__* POS_CMDEXT ;
typedef  TYPE_16__* PINQUIRYDATA ;
typedef  TYPE_17__* PCOMMAND ;
typedef  int HPT_U8 ;
typedef  int HPT_U64 ;
typedef  int HPT_U32 ;
typedef  int HPT_U16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_WAITOK ; 
 void* CAM_BUSY ; 
 int CAM_CDB_PHYS ; 
 int CAM_CDB_POINTER ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_CMP_ERR ; 
 void* CAM_REQ_INVALID ; 
 int CAM_SCATTER_VALID ; 
 void* CAM_SEL_TIMEOUT ; 
 int CAM_SG_LIST_PHYS ; 
 void* CAM_TID_INVALID ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  HPT_ASSERT (TYPE_15__*) ; 
 int /*<<< orphan*/  HPT_OSM_TIMEOUT ; 
#define  INQUIRY 140 
 int /*<<< orphan*/  KdPrint (char*) ; 
#define  READ_10 139 
#define  READ_16 138 
#define  READ_6 137 
#define  READ_CAPACITY 136 
#define  REPORT_LUNS 135 
#define  SERVICE_ACTION_IN 134 
#define  START_STOP_UNIT 133 
#define  SYNCHRONIZE_CACHE 132 
#define  TEST_UNIT_READY 131 
 int /*<<< orphan*/  VD_RAW ; 
#define  WRITE_10 130 
#define  WRITE_16 129 
#define  WRITE_6 128 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,TYPE_17__*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ ,TYPE_17__*,int /*<<< orphan*/ ) ; 
 TYPE_15__* cmdext_get (TYPE_14__*) ; 
 int /*<<< orphan*/  cmdext_put (TYPE_15__*) ; 
 int /*<<< orphan*/  hpt_io_dmamap_callback ; 
 int /*<<< orphan*/  hpt_timeout ; 
 TYPE_17__* ldm_alloc_cmds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_13__* ldm_find_target (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ldm_free_cmds (TYPE_17__*) ; 
 int /*<<< orphan*/  ldm_queue_cmd (TYPE_17__*) ; 
 int /*<<< orphan*/  mIsArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int**,char*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_buildsgl ; 
 int /*<<< orphan*/  os_cmddone ; 
 int /*<<< orphan*/  os_printk (char*,int) ; 
 scalar_t__ osm_max_targets ; 
 int /*<<< orphan*/  timeout (int /*<<< orphan*/ ,TYPE_17__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void hpt_scsi_io(PVBUS_EXT vbus_ext, union ccb *ccb)
{
	PVBUS vbus = (PVBUS)vbus_ext->vbus;
	PVDEV vd;
	PCOMMAND pCmd;
	POS_CMDEXT ext;
	HPT_U8 *cdb;

	if (ccb->ccb_h.flags & CAM_CDB_POINTER)
		cdb = ccb->csio.cdb_io.cdb_ptr;
	else
		cdb = ccb->csio.cdb_io.cdb_bytes;
	
	KdPrint(("<8>hpt_scsi_io: ccb %x id %d lun %d cdb %x-%x-%x",
		ccb,
		ccb->ccb_h.target_id, ccb->ccb_h.target_lun,
		*(HPT_U32 *)&cdb[0], *(HPT_U32 *)&cdb[4], *(HPT_U32 *)&cdb[8]
	));

	/* ccb->ccb_h.path_id is not our bus id - don't check it */
	if (ccb->ccb_h.target_lun != 0 ||
		ccb->ccb_h.target_id >= osm_max_targets ||
		(ccb->ccb_h.flags & CAM_CDB_PHYS))
	{
		ccb->ccb_h.status = CAM_TID_INVALID;
		xpt_done(ccb);
		return;
	}

	vd = ldm_find_target(vbus, ccb->ccb_h.target_id);

	if (!vd) {
		ccb->ccb_h.status = CAM_SEL_TIMEOUT;
		xpt_done(ccb);
		return;
	}
   
	switch (cdb[0]) {
	case TEST_UNIT_READY:
	case START_STOP_UNIT:
	case SYNCHRONIZE_CACHE:
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;

	case INQUIRY:
		{
			PINQUIRYDATA inquiryData;
			memset(ccb->csio.data_ptr, 0, ccb->csio.dxfer_len);
			inquiryData = (PINQUIRYDATA)ccb->csio.data_ptr;
		
			inquiryData->AdditionalLength = 31;
			inquiryData->CommandQueue = 1;
			memcpy(&inquiryData->VendorId, "HPT     ", 8);
			memcpy(&inquiryData->ProductId, "DISK 0_0        ", 16);
	
			if (vd->target_id / 10) {
				inquiryData->ProductId[7] = (vd->target_id % 100) / 10 + '0';
				inquiryData->ProductId[8] = (vd->target_id % 100) % 10 + '0';
			}
			else
				inquiryData->ProductId[7] = (vd->target_id % 100) % 10 + '0';
	
			memcpy(&inquiryData->ProductRevisionLevel, "4.00", 4);
	
			ccb->ccb_h.status = CAM_REQ_CMP;
		}
		break;

	case READ_CAPACITY:
	{
		HPT_U8 *rbuf = ccb->csio.data_ptr;
		HPT_U32 cap;
		HPT_U8 sector_size_shift = 0;
		HPT_U64 new_cap;
		HPT_U32 sector_size = 0;

		if (mIsArray(vd->type))
			sector_size_shift = vd->u.array.sector_size_shift;
		else{
			if(vd->type == VD_RAW){
				sector_size = vd->u.raw.logical_sector_size;
			}
		
			switch (sector_size) {
				case 0x1000:
					KdPrint(("set 4k setctor size in READ_CAPACITY"));
					sector_size_shift = 3;
					break;
				default:
					break;
			}			
		}
		new_cap = vd->capacity >> sector_size_shift;
		
		if (new_cap > 0xfffffffful)
			cap = 0xffffffff;
		else
			cap = new_cap - 1;
			
		rbuf[0] = (HPT_U8)(cap>>24);
		rbuf[1] = (HPT_U8)(cap>>16);
		rbuf[2] = (HPT_U8)(cap>>8);
		rbuf[3] = (HPT_U8)cap;
		rbuf[4] = 0;
		rbuf[5] = 0;
		rbuf[6] = 2 << sector_size_shift;
		rbuf[7] = 0;

		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	}
	case REPORT_LUNS:
	{
		HPT_U8 *rbuf = ccb->csio.data_ptr;
		memset(rbuf, 0, 16);
		rbuf[3] = 8;
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;				
	}
	case SERVICE_ACTION_IN: 
	{
		HPT_U8 *rbuf = ccb->csio.data_ptr;
		HPT_U64	cap = 0;
		HPT_U8 sector_size_shift = 0;
		HPT_U32 sector_size = 0;

		if(mIsArray(vd->type))
			sector_size_shift = vd->u.array.sector_size_shift;
		else{
			if(vd->type == VD_RAW){
				sector_size = vd->u.raw.logical_sector_size;
			}
		
			switch (sector_size) {
				case 0x1000:
					KdPrint(("set 4k setctor size in SERVICE_ACTION_IN"));
					sector_size_shift = 3;
					break;
				default:
					break;
			}			
		}
		cap = (vd->capacity >> sector_size_shift) - 1;
					
		rbuf[0] = (HPT_U8)(cap>>56);
		rbuf[1] = (HPT_U8)(cap>>48);
		rbuf[2] = (HPT_U8)(cap>>40);
		rbuf[3] = (HPT_U8)(cap>>32);
		rbuf[4] = (HPT_U8)(cap>>24);
		rbuf[5] = (HPT_U8)(cap>>16);
		rbuf[6] = (HPT_U8)(cap>>8);
		rbuf[7] = (HPT_U8)cap;
		rbuf[8] = 0;
		rbuf[9] = 0;
		rbuf[10] = 2 << sector_size_shift;
		rbuf[11] = 0;
		
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;	
	}
	
	case READ_6:
	case READ_10:
	case READ_16:
	case WRITE_6:
	case WRITE_10:
	case WRITE_16:
	case 0x13:
	case 0x2f:
	case 0x8f: /* VERIFY_16 */
	{
		HPT_U8 sector_size_shift = 0;
		HPT_U32 sector_size = 0;
		pCmd = ldm_alloc_cmds(vbus, vd->cmds_per_request);
		if(!pCmd){
			KdPrint(("Failed to allocate command!"));
			ccb->ccb_h.status = CAM_BUSY;
			break;
		}

		switch (cdb[0])	{
		case READ_6:
		case WRITE_6:
		case 0x13:
			pCmd->uCmd.Ide.Lba =  ((HPT_U32)cdb[1] << 16) | ((HPT_U32)cdb[2] << 8) | (HPT_U32)cdb[3];
			pCmd->uCmd.Ide.nSectors = (HPT_U16) cdb[4];
			break;
		case READ_16:
		case WRITE_16:
		case 0x8f: /* VERIFY_16 */
		{
			HPT_U64 block =
				((HPT_U64)cdb[2]<<56) |
				((HPT_U64)cdb[3]<<48) |
				((HPT_U64)cdb[4]<<40) |
				((HPT_U64)cdb[5]<<32) |
				((HPT_U64)cdb[6]<<24) |
				((HPT_U64)cdb[7]<<16) |
				((HPT_U64)cdb[8]<<8) |
				((HPT_U64)cdb[9]);
			pCmd->uCmd.Ide.Lba = block;
			pCmd->uCmd.Ide.nSectors = (HPT_U16)cdb[13] | ((HPT_U16)cdb[12]<<8);
			break;
		}
		
		default:
			pCmd->uCmd.Ide.Lba = (HPT_U32)cdb[5] | ((HPT_U32)cdb[4] << 8) | ((HPT_U32)cdb[3] << 16) | ((HPT_U32)cdb[2] << 24);
			pCmd->uCmd.Ide.nSectors = (HPT_U16) cdb[8] | ((HPT_U16)cdb[7]<<8);
			break;
		}

		if(mIsArray(vd->type)) {
			sector_size_shift = vd->u.array.sector_size_shift;
		}
		else{
			if(vd->type == VD_RAW){
				sector_size = vd->u.raw.logical_sector_size;
			}
	  		
			switch (sector_size) {
				case 0x1000:
					KdPrint(("<8>resize sector size from 4k to 512"));
					sector_size_shift = 3;
					break;
				default:
					break;
	 		}			
		}
		pCmd->uCmd.Ide.Lba <<= sector_size_shift;
		pCmd->uCmd.Ide.nSectors <<= sector_size_shift;

		
		switch (cdb[0]) {
		case READ_6:
		case READ_10:
		case READ_16:
			pCmd->flags.data_in = 1;
			break;
		case WRITE_6:
		case WRITE_10:
		case WRITE_16:
			pCmd->flags.data_out = 1;
			break;
		}
		pCmd->priv = ext = cmdext_get(vbus_ext);
		HPT_ASSERT(ext);
		ext->ccb = ccb;
		pCmd->target = vd;
		pCmd->done = os_cmddone;
		pCmd->buildsgl = os_buildsgl;

		pCmd->psg = ext->psg;
#if (__FreeBSD_version < 1000510)			
		if (ccb->ccb_h.flags & CAM_SCATTER_VALID) {
			int idx;
			bus_dma_segment_t *sgList = (bus_dma_segment_t *)ccb->csio.data_ptr;
			
			if (ccb->ccb_h.flags & CAM_SG_LIST_PHYS)
				pCmd->flags.physical_sg = 1;
				
			for (idx = 0; idx < ccb->csio.sglist_cnt; idx++) {
				pCmd->psg[idx].addr.bus = sgList[idx].ds_addr;
				pCmd->psg[idx].size = sgList[idx].ds_len;
				pCmd->psg[idx].eot = (idx==ccb->csio.sglist_cnt-1)? 1 : 0;
			}

			ccb->ccb_h.timeout_ch = timeout(hpt_timeout, pCmd, HPT_OSM_TIMEOUT);
			ldm_queue_cmd(pCmd);
		}
		else 
#endif
		{
			int error;
			pCmd->flags.physical_sg = 1;
#if (__FreeBSD_version >= 1000510)
			error = bus_dmamap_load_ccb(vbus_ext->io_dmat,
						ext->dma_map, ccb,
						hpt_io_dmamap_callback, pCmd,
						BUS_DMA_WAITOK
					);
#else 
			error = bus_dmamap_load(vbus_ext->io_dmat, 
						ext->dma_map, 
						ccb->csio.data_ptr, ccb->csio.dxfer_len, 
						hpt_io_dmamap_callback, pCmd,
				    	BUS_DMA_WAITOK
					);
#endif
			KdPrint(("<8>bus_dmamap_load return %d", error));
			if (error && error!=EINPROGRESS) {
				os_printk("bus_dmamap_load error %d", error);
				cmdext_put(ext);
				ldm_free_cmds(pCmd);
				ccb->ccb_h.status = CAM_REQ_CMP_ERR;
				xpt_done(ccb);
			}
		}
		return;
	}

	default:
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	}

	xpt_done(ccb);
	return;
}