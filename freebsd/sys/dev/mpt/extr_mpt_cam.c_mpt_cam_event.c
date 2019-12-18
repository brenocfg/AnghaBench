#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct cam_path* path; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int uint32_t ;
struct mpt_softc {struct cam_sim* sim; struct cam_sim* phydisk_sim; int /*<<< orphan*/  ready; struct cam_path* path; } ;
struct TYPE_13__ {int /*<<< orphan*/  status; int /*<<< orphan*/  flags; int /*<<< orphan*/  func_code; } ;
struct ccb_relsim {TYPE_6__ ccb_h; int /*<<< orphan*/  openings; int /*<<< orphan*/  release_flags; } ;
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;
typedef  int /*<<< orphan*/  request_t ;
typedef  int /*<<< orphan*/  lun_id_t ;
typedef  int /*<<< orphan*/  data0 ;
struct TYPE_12__ {int Event; void** Data; } ;
struct TYPE_11__ {void* DiscoveryStatus; int /*<<< orphan*/  Port; } ;
struct TYPE_10__ {int /*<<< orphan*/  CurrentDepth; int /*<<< orphan*/  TargetID; int /*<<< orphan*/  Bus; } ;
struct TYPE_9__ {int /*<<< orphan*/  ReasonCode; int /*<<< orphan*/  TargetID; int /*<<< orphan*/  Bus; } ;
typedef  TYPE_2__* PTR_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE ;
typedef  TYPE_3__* PTR_EVENT_DATA_QUEUE_FULL ;
typedef  TYPE_4__* PTR_EVENT_DATA_DISCOVERY_ERROR ;
typedef  TYPE_5__ MSG_EVENT_NOTIFY_REPLY ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  CAM_DEV_QFREEZE ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
#define  MPI_EVENT_EVENT_CHANGE 150 
#define  MPI_EVENT_EXT_BUS_RESET 149 
#define  MPI_EVENT_INTEGRATED_RAID 148 
#define  MPI_EVENT_IOC_BUS_RESET 147 
#define  MPI_EVENT_IR2 146 
#define  MPI_EVENT_IR_RESYNC_UPDATE 145 
#define  MPI_EVENT_LINK_STATUS_CHANGE 144 
#define  MPI_EVENT_LOGOUT 143 
#define  MPI_EVENT_LOG_ENTRY_ADDED 142 
#define  MPI_EVENT_LOOP_STATE_CHANGE 141 
#define  MPI_EVENT_QUEUE_FULL 140 
#define  MPI_EVENT_RESCAN 139 
#define  MPI_EVENT_SAS_DEVICE_STATUS_CHANGE 138 
#define  MPI_EVENT_SAS_DEV_STAT_RC_ADDED 137 
#define  MPI_EVENT_SAS_DEV_STAT_RC_CMPL_INTERNAL_DEV_RESET 136 
#define  MPI_EVENT_SAS_DEV_STAT_RC_CMPL_TASK_ABORT_INTERNAL 135 
#define  MPI_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET 134 
#define  MPI_EVENT_SAS_DEV_STAT_RC_NOT_RESPONDING 133 
#define  MPI_EVENT_SAS_DISCOVERY 132 
#define  MPI_EVENT_SAS_DISCOVERY_ERROR 131 
#define  MPI_EVENT_SAS_PHY_LINK_STATUS 130 
#define  MPI_EVENT_SAS_SES 129 
#define  MPI_EVENT_UNIT_ATTENTION 128 
 int /*<<< orphan*/  MPT_MAX_LUNS ; 
 int /*<<< orphan*/  MPT_PRT_WARN ; 
 int /*<<< orphan*/  RELSIM_ADJUST_OPENINGS ; 
 int /*<<< orphan*/  XPT_REL_SIMQ ; 
 int /*<<< orphan*/  bootverbose ; 
 int cam_sim_path (struct cam_sim*) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 void* le32toh (void*) ; 
 int /*<<< orphan*/  mpt_is_raid_member (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,struct cam_path*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_6__*,struct cam_path*,int) ; 

__attribute__((used)) static int
mpt_cam_event(struct mpt_softc *mpt, request_t *req,
	      MSG_EVENT_NOTIFY_REPLY *msg)
{
	uint32_t data0, data1;

	data0 = le32toh(msg->Data[0]);
	data1 = le32toh(msg->Data[1]);
	switch(msg->Event & 0xFF) {
	case MPI_EVENT_UNIT_ATTENTION:
		mpt_prt(mpt, "UNIT ATTENTION: Bus: 0x%02x TargetID: 0x%02x\n",
		    (data0 >> 8) & 0xff, data0 & 0xff);
		break;

	case MPI_EVENT_IOC_BUS_RESET:
		/* We generated a bus reset */
		mpt_prt(mpt, "IOC Generated Bus Reset Port: %d\n",
		    (data0 >> 8) & 0xff);
		xpt_async(AC_BUS_RESET, mpt->path, NULL);
		break;

	case MPI_EVENT_EXT_BUS_RESET:
		/* Someone else generated a bus reset */
		mpt_prt(mpt, "External Bus Reset Detected\n");
		/*
		 * These replies don't return EventData like the MPI
		 * spec says they do
		 */	
		xpt_async(AC_BUS_RESET, mpt->path, NULL);
		break;

	case MPI_EVENT_RESCAN:
	{
		union ccb *ccb;
		uint32_t pathid;
		/*
		 * In general this means a device has been added to the loop.
		 */
		mpt_prt(mpt, "Rescan Port: %d\n", (data0 >> 8) & 0xff);
		if (mpt->ready == 0) {
			break;
		}
		if (mpt->phydisk_sim) {
			pathid = cam_sim_path(mpt->phydisk_sim);
		} else {
			pathid = cam_sim_path(mpt->sim);
		}
		/*
		 * Allocate a CCB, create a wildcard path for this bus,
		 * and schedule a rescan.
		 */
		ccb = xpt_alloc_ccb_nowait();
		if (ccb == NULL) {
			mpt_prt(mpt, "unable to alloc CCB for rescan\n");
			break;
		}

		if (xpt_create_path(&ccb->ccb_h.path, NULL, pathid,
		    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
			mpt_prt(mpt, "unable to create path for rescan\n");
			xpt_free_ccb(ccb);
			break;
		}
		xpt_rescan(ccb);
		break;
	}

	case MPI_EVENT_LINK_STATUS_CHANGE:
		mpt_prt(mpt, "Port %d: LinkState: %s\n",
		    (data1 >> 8) & 0xff,
		    ((data0 & 0xff) == 0)?  "Failed" : "Active");
		break;

	case MPI_EVENT_LOOP_STATE_CHANGE:
		switch ((data0 >> 16) & 0xff) {
		case 0x01:
			mpt_prt(mpt,
			    "Port 0x%x: FC LinkEvent: LIP(%02x,%02x) "
			    "(Loop Initialization)\n",
			    (data1 >> 8) & 0xff,
			    (data0 >> 8) & 0xff,
			    (data0     ) & 0xff);
			switch ((data0 >> 8) & 0xff) {
			case 0xF7:
				if ((data0 & 0xff) == 0xF7) {
					mpt_prt(mpt, "Device needs AL_PA\n");
				} else {
					mpt_prt(mpt, "Device %02x doesn't like "
					    "FC performance\n",
					    data0 & 0xFF);
				}
				break;
			case 0xF8:
				if ((data0 & 0xff) == 0xF7) {
					mpt_prt(mpt, "Device had loop failure "
					    "at its receiver prior to acquiring"
					    " AL_PA\n");
				} else {
					mpt_prt(mpt, "Device %02x detected loop"
					    " failure at its receiver\n", 
					    data0 & 0xFF);
				}
				break;
			default:
				mpt_prt(mpt, "Device %02x requests that device "
				    "%02x reset itself\n", 
				    data0 & 0xFF,
				    (data0 >> 8) & 0xFF);
				break;
			}
			break;
		case 0x02:
			mpt_prt(mpt, "Port 0x%x: FC LinkEvent: "
			    "LPE(%02x,%02x) (Loop Port Enable)\n",
			    (data1 >> 8) & 0xff, /* Port */
			    (data0 >>  8) & 0xff, /* Character 3 */
			    (data0      ) & 0xff  /* Character 4 */);
			break;
		case 0x03:
			mpt_prt(mpt, "Port 0x%x: FC LinkEvent: "
			    "LPB(%02x,%02x) (Loop Port Bypass)\n",
			    (data1 >> 8) & 0xff, /* Port */
			    (data0 >> 8) & 0xff, /* Character 3 */
			    (data0     ) & 0xff  /* Character 4 */);
			break;
		default:
			mpt_prt(mpt, "Port 0x%x: FC LinkEvent: Unknown "
			    "FC event (%02x %02x %02x)\n",
			    (data1 >> 8) & 0xff, /* Port */
			    (data0 >> 16) & 0xff, /* Event */
			    (data0 >>  8) & 0xff, /* Character 3 */
			    (data0      ) & 0xff  /* Character 4 */);
		}
		break;

	case MPI_EVENT_LOGOUT:
		mpt_prt(mpt, "FC Logout Port: %d N_PortID: %02x\n",
		    (data1 >> 8) & 0xff, data0);
		break;
	case MPI_EVENT_QUEUE_FULL:
	{
		struct cam_sim *sim;
		struct cam_path *tmppath;
		struct ccb_relsim crs;
		PTR_EVENT_DATA_QUEUE_FULL pqf;
		lun_id_t lun_id;

		pqf = (PTR_EVENT_DATA_QUEUE_FULL)msg->Data;
		pqf->CurrentDepth = le16toh(pqf->CurrentDepth);
		if (bootverbose) {
		    mpt_prt(mpt, "QUEUE FULL EVENT: Bus 0x%02x Target 0x%02x "
			"Depth %d\n",
			pqf->Bus, pqf->TargetID, pqf->CurrentDepth);
		}
		if (mpt->phydisk_sim && mpt_is_raid_member(mpt,
		    pqf->TargetID) != 0) {
			sim = mpt->phydisk_sim;
		} else {
			sim = mpt->sim;
		}
		for (lun_id = 0; lun_id < MPT_MAX_LUNS; lun_id++) {
			if (xpt_create_path(&tmppath, NULL, cam_sim_path(sim),
			    pqf->TargetID, lun_id) != CAM_REQ_CMP) {
				mpt_prt(mpt, "unable to create a path to send "
				    "XPT_REL_SIMQ");
				break;
			}
			xpt_setup_ccb(&crs.ccb_h, tmppath, 5);
			crs.ccb_h.func_code = XPT_REL_SIMQ;
			crs.ccb_h.flags = CAM_DEV_QFREEZE;
			crs.release_flags = RELSIM_ADJUST_OPENINGS;
			crs.openings = pqf->CurrentDepth - 1;
			xpt_action((union ccb *)&crs);
			if (crs.ccb_h.status != CAM_REQ_CMP) {
				mpt_prt(mpt, "XPT_REL_SIMQ failed\n");
			}
			xpt_free_path(tmppath);
		}
		break;
	}
	case MPI_EVENT_IR_RESYNC_UPDATE:
		mpt_prt(mpt, "IR resync update %d completed\n",
		    (data0 >> 16) & 0xff);
		break;
	case MPI_EVENT_SAS_DEVICE_STATUS_CHANGE:
	{
		union ccb *ccb;
		struct cam_sim *sim;
		struct cam_path *tmppath;
		PTR_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE psdsc;

		psdsc = (PTR_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE)msg->Data;
		if (mpt->phydisk_sim && mpt_is_raid_member(mpt,
		    psdsc->TargetID) != 0)
			sim = mpt->phydisk_sim;
		else
			sim = mpt->sim;
		switch(psdsc->ReasonCode) {
		case MPI_EVENT_SAS_DEV_STAT_RC_ADDED:
			ccb = xpt_alloc_ccb_nowait();
			if (ccb == NULL) {
				mpt_prt(mpt,
				    "unable to alloc CCB for rescan\n");
				break;
			}
			if (xpt_create_path(&ccb->ccb_h.path, NULL,
			    cam_sim_path(sim), psdsc->TargetID,
			    CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
				mpt_prt(mpt,
				    "unable to create path for rescan\n");
				xpt_free_ccb(ccb);
				break;
			}
			xpt_rescan(ccb);
			break;
		case MPI_EVENT_SAS_DEV_STAT_RC_NOT_RESPONDING:
			if (xpt_create_path(&tmppath, NULL, cam_sim_path(sim),
			    psdsc->TargetID, CAM_LUN_WILDCARD) !=
			    CAM_REQ_CMP) {
				mpt_prt(mpt,
				    "unable to create path for async event");
				break;
			}
			xpt_async(AC_LOST_DEVICE, tmppath, NULL);
			xpt_free_path(tmppath);
			break;
		case MPI_EVENT_SAS_DEV_STAT_RC_CMPL_INTERNAL_DEV_RESET:
		case MPI_EVENT_SAS_DEV_STAT_RC_CMPL_TASK_ABORT_INTERNAL:
		case MPI_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET:
			break;
		default:
			mpt_lprt(mpt, MPT_PRT_WARN,
			    "SAS device status change: Bus: 0x%02x TargetID: "
			    "0x%02x ReasonCode: 0x%02x\n", psdsc->Bus,
			    psdsc->TargetID, psdsc->ReasonCode);
			break;
		}
		break;
	}
	case MPI_EVENT_SAS_DISCOVERY_ERROR:
	{
		PTR_EVENT_DATA_DISCOVERY_ERROR pde;

		pde = (PTR_EVENT_DATA_DISCOVERY_ERROR)msg->Data;
		pde->DiscoveryStatus = le32toh(pde->DiscoveryStatus);
		mpt_lprt(mpt, MPT_PRT_WARN,
		    "SAS discovery error: Port: 0x%02x Status: 0x%08x\n",
		    pde->Port, pde->DiscoveryStatus);
		break;
	}
	case MPI_EVENT_EVENT_CHANGE:
	case MPI_EVENT_INTEGRATED_RAID:
	case MPI_EVENT_IR2:
	case MPI_EVENT_LOG_ENTRY_ADDED:
	case MPI_EVENT_SAS_DISCOVERY:
	case MPI_EVENT_SAS_PHY_LINK_STATUS:
	case MPI_EVENT_SAS_SES:
		break;
	default:
		mpt_lprt(mpt, MPT_PRT_WARN, "mpt_cam_event: 0x%x\n",
		    msg->Event & 0xFF);
		return (0);
	}
	return (1);
}