#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* status; int /*<<< orphan*/  timeout_ch; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct TYPE_11__ {scalar_t__ data_out; scalar_t__ data_in; } ;
struct TYPE_14__ {int Result; TYPE_2__ flags; int /*<<< orphan*/  priv; } ;
struct TYPE_13__ {int /*<<< orphan*/  dma_map; TYPE_3__* vbus_ext; int /*<<< orphan*/  timeout; union ccb* ccb; } ;
struct TYPE_12__ {int /*<<< orphan*/  io_dmat; } ;
typedef  TYPE_4__* POS_CMDEXT ;
typedef  TYPE_5__* PCOMMAND ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 void* CAM_BUSY ; 
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
 int /*<<< orphan*/  cmdext_put (TYPE_4__*) ; 
 int /*<<< orphan*/  hpt_timeout ; 
 int /*<<< orphan*/  ldm_free_cmds (TYPE_5__*) ; 
 int /*<<< orphan*/  untimeout (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void os_cmddone(PCOMMAND pCmd)
{
	POS_CMDEXT ext = (POS_CMDEXT)pCmd->priv;
	union ccb *ccb = ext->ccb;

	KdPrint(("<8>os_cmddone(%p, %d)", pCmd, pCmd->Result));
#if (__FreeBSD_version >= 1000510)	
	callout_stop(&ext->timeout);
#else 
	untimeout(hpt_timeout, pCmd, ccb->ccb_h.timeout_ch);
#endif
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