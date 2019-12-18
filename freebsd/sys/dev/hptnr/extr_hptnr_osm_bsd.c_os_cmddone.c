#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int flags; void* status; } ;
struct TYPE_13__ {int* cdb_ptr; int* cdb_bytes; } ;
struct TYPE_15__ {int /*<<< orphan*/  sense_data; TYPE_1__ cdb_io; } ;
union ccb {TYPE_4__ ccb_h; TYPE_3__ csio; } ;
struct TYPE_17__ {scalar_t__ data_out; scalar_t__ data_in; } ;
struct TYPE_19__ {int bSectorCountReg; int bLbaLowReg; int bLbaMidReg; int bLbaHighReg; int /*<<< orphan*/  bFeaturesReg; int /*<<< orphan*/  bDriveHeadReg; int /*<<< orphan*/  bCommandReg; } ;
struct TYPE_14__ {TYPE_7__ Passthrough; } ;
struct TYPE_21__ {int Result; TYPE_5__ flags; TYPE_2__ uCmd; int /*<<< orphan*/  priv; } ;
struct TYPE_20__ {int /*<<< orphan*/  dma_map; TYPE_6__* vbus_ext; int /*<<< orphan*/  timeout; union ccb* ccb; } ;
struct TYPE_18__ {int /*<<< orphan*/  io_dmat; } ;
typedef  TYPE_7__ PassthroughCmd ;
typedef  TYPE_8__* POS_CMDEXT ;
typedef  TYPE_9__* PCOMMAND ;
typedef  int HPT_U8 ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 void* CAM_BUSY ; 
 int CAM_CDB_POINTER ; 
 void* CAM_DEV_NOT_THERE ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_INVALID ; 
 void* CAM_SCSI_STATUS_ERROR ; 
 void* CAM_SEL_TIMEOUT ; 
 int /*<<< orphan*/  KdPrint (char*) ; 
#define  RETURN_BAD_DEVICE 133 
#define  RETURN_DEVICE_BUSY 132 
#define  RETURN_INVALID_REQUEST 131 
#define  RETURN_RETRY 130 
#define  RETURN_SELECTION_TIMEOUT 129 
#define  RETURN_SUCCESS 128 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdext_put (TYPE_8__*) ; 
 int /*<<< orphan*/  ldm_free_cmds (TYPE_9__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void os_cmddone(PCOMMAND pCmd)
{
	POS_CMDEXT ext = (POS_CMDEXT)pCmd->priv;
	union ccb *ccb = ext->ccb;
	HPT_U8 *cdb;
		
	if (ccb->ccb_h.flags & CAM_CDB_POINTER)
		cdb = ccb->csio.cdb_io.cdb_ptr;
	else
		cdb = ccb->csio.cdb_io.cdb_bytes;

	KdPrint(("os_cmddone(%p, %d)", pCmd, pCmd->Result));

	callout_stop(&ext->timeout);
	switch(cdb[0]) {
		case 0x85: /*ATA_16*/
		case 0xA1: /*ATA_12*/
		{
			PassthroughCmd *passthru = &pCmd->uCmd.Passthrough;
			HPT_U8 *sense_buffer = (HPT_U8 *)&ccb->csio.sense_data;
			memset(&ccb->csio.sense_data, 0,sizeof(ccb->csio.sense_data));

			sense_buffer[0] = 0x72; /* Response Code */
			sense_buffer[7] = 14; /* Additional Sense Length */
	
			sense_buffer[8] = 0x9; /* ATA Return Descriptor */
			sense_buffer[9] = 0xc; /* Additional Descriptor Length */
			sense_buffer[11] = (HPT_U8)passthru->bFeaturesReg; /* Error */
			sense_buffer[13] = (HPT_U8)passthru->bSectorCountReg;  /* Sector Count (7:0) */
			sense_buffer[15] = (HPT_U8)passthru->bLbaLowReg; /* LBA Low (7:0) */
			sense_buffer[17] = (HPT_U8)passthru->bLbaMidReg; /* LBA Mid (7:0) */
			sense_buffer[19] = (HPT_U8)passthru->bLbaHighReg; /* LBA High (7:0) */
	
			if ((cdb[0] == 0x85) && (cdb[1] & 0x1))
			{
				sense_buffer[10] = 1;
				sense_buffer[12] = (HPT_U8)(passthru->bSectorCountReg >> 8); /* Sector Count (15:8) */
				sense_buffer[14] = (HPT_U8)(passthru->bLbaLowReg >> 8);	/* LBA Low (15:8) */
				sense_buffer[16] = (HPT_U8)(passthru->bLbaMidReg >> 8); /* LBA Mid (15:8) */
				sense_buffer[18] = (HPT_U8)(passthru->bLbaHighReg >> 8); /* LBA High (15:8) */
			}
	
			sense_buffer[20] = (HPT_U8)passthru->bDriveHeadReg; /* Device */
			sense_buffer[21] = (HPT_U8)passthru->bCommandReg; /* Status */
			KdPrint(("sts 0x%x err 0x%x low 0x%x mid 0x%x hig 0x%x dh 0x%x sc 0x%x",
					 passthru->bCommandReg,
					 passthru->bFeaturesReg,
					 passthru->bLbaLowReg,
					 passthru->bLbaMidReg,
					 passthru->bLbaHighReg,
					 passthru->bDriveHeadReg,
					 passthru->bSectorCountReg));
			KdPrint(("result:0x%x,bFeaturesReg:0x%04x,bSectorCountReg:0x%04x,LBA:0x%04x%04x%04x ",
				pCmd->Result,passthru->bFeaturesReg,passthru->bSectorCountReg,
				passthru->bLbaHighReg,passthru->bLbaMidReg,passthru->bLbaLowReg));
		}
		default:
			break;
	}

	switch(pCmd->Result) {
	case RETURN_SUCCESS:
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	case RETURN_BAD_DEVICE:
		ccb->ccb_h.status = CAM_DEV_NOT_THERE;
		break;
	case RETURN_DEVICE_BUSY:
		ccb->ccb_h.status = CAM_BUSY;
		break;
	case RETURN_INVALID_REQUEST:
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	case RETURN_SELECTION_TIMEOUT:
		ccb->ccb_h.status = CAM_SEL_TIMEOUT;
		break;
	case RETURN_RETRY:
		ccb->ccb_h.status = CAM_BUSY;
		break;
	default:
		ccb->ccb_h.status = CAM_SCSI_STATUS_ERROR;
		break;
	}

	if (pCmd->flags.data_in) {
		bus_dmamap_sync(ext->vbus_ext->io_dmat, ext->dma_map, BUS_DMASYNC_POSTREAD);
	}
	else if (pCmd->flags.data_out) {
		bus_dmamap_sync(ext->vbus_ext->io_dmat, ext->dma_map, BUS_DMASYNC_POSTWRITE);
	}
	
	bus_dmamap_unload(ext->vbus_ext->io_dmat, ext->dma_map);

	cmdext_put(ext);
	ldm_free_cmds(pCmd);
	xpt_done(ccb);
}