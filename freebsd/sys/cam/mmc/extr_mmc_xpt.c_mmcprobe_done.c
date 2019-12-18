#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  priority; } ;
struct TYPE_13__ {int /*<<< orphan*/  func_code; struct cam_path* path; TYPE_1__ pinfo; } ;
struct TYPE_10__ {int error; int* resp; int arg; } ;
struct ccb_mmcio {TYPE_2__ cmd; } ;
union ccb {TYPE_5__ ccb_h; struct ccb_mmcio mmcio; } ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct mmc_params {int card_features; int io_ocr; int card_ocr; int card_rca; int /*<<< orphan*/ * card_csd; int /*<<< orphan*/ * card_cid; int /*<<< orphan*/  sdio_func_count; } ;
struct cam_periph {TYPE_4__* path; scalar_t__ softc; } ;
struct cam_path {TYPE_7__* device; } ;
struct TYPE_14__ {int action; int flags; } ;
typedef  TYPE_6__ mmcprobe_softc ;
struct TYPE_15__ {int flags; struct mmc_params mmc_ident_data; int /*<<< orphan*/  protocol; } ;
struct TYPE_12__ {TYPE_3__* device; } ;
struct TYPE_11__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_FOUND_DEVICE ; 
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_PROBE ; 
 int CAM_DEV_UNCONFIGURED ; 
 int CARD_FEATURE_18V ; 
 int CARD_FEATURE_MEMORY ; 
 int CARD_FEATURE_MMC ; 
 int CARD_FEATURE_SD20 ; 
 int CARD_FEATURE_SDHC ; 
 int CARD_FEATURE_SDIO ; 
 int /*<<< orphan*/  FALSE ; 
 int MMC_ERR_NONE ; 
 int MMC_OCR_CARD_BUSY ; 
 int MMC_OCR_CCS ; 
 int MMC_OCR_S18A ; 
 int MMC_OCR_VOLTAGE ; 
 int MMC_PROPOSED_RCA ; 
 int PROBE_DONE ; 
 int PROBE_FLAG_ACMD_SENT ; 
#define  PROBE_GET_CID 139 
#define  PROBE_GET_CSD 138 
#define  PROBE_IDENTIFY 137 
 int PROBE_INVALID ; 
#define  PROBE_MMC_INIT 136 
#define  PROBE_MMC_SET_RELATIVE_ADDR 135 
#define  PROBE_RESET 134 
#define  PROBE_SDIO_INIT 133 
#define  PROBE_SDIO_RESET 132 
#define  PROBE_SELECT_CARD 131 
#define  PROBE_SEND_APP_OP_COND 130 
#define  PROBE_SEND_IF_COND 129 
#define  PROBE_SEND_RELATIVE_ADDR 128 
 int /*<<< orphan*/  PROBE_SET_ACTION (TYPE_6__*,int const) ; 
 int /*<<< orphan*/  PROTO_MMCSD ; 
 int R4_IO_MEM_PRESENT ; 
 int /*<<< orphan*/  R4_IO_NUM_FUNCTIONS (int) ; 
 int R4_IO_OCR_MASK ; 
 int /*<<< orphan*/  XPT_GDEV_TYPE ; 
 int /*<<< orphan*/  cam_periph_invalidate (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int cam_release_devq (struct cam_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  xpt_acquire_device (TYPE_7__*) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,struct cam_path*,union ccb*) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmcprobe_done(struct cam_periph *periph, union ccb *done_ccb)
{
	mmcprobe_softc *softc;
	struct cam_path *path;

	int err;
	struct ccb_mmcio *mmcio;
	u_int32_t  priority;

	CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE, ("mmcprobe_done\n"));
	softc = (mmcprobe_softc *)periph->softc;
	path = done_ccb->ccb_h.path;
	priority = done_ccb->ccb_h.pinfo.priority;

	switch (softc->action) {
	case PROBE_RESET:
		/* FALLTHROUGH */
	case PROBE_IDENTIFY:
	{
		printf("Starting completion of PROBE_RESET\n");
		CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE, ("done with PROBE_RESET\n"));
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;

		if (err != MMC_ERR_NONE) {
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
				  ("GO_IDLE_STATE failed with error %d\n",
				   err));

			/* There was a device there, but now it's gone... */
			if ((path->device->flags & CAM_DEV_UNCONFIGURED) == 0) {
				xpt_async(AC_LOST_DEVICE, path, NULL);
			}
			PROBE_SET_ACTION(softc, PROBE_INVALID);
			break;
		}
		path->device->protocol = PROTO_MMCSD;
		PROBE_SET_ACTION(softc, PROBE_SEND_IF_COND);
		break;
	}
	case PROBE_SEND_IF_COND:
	{
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;
		struct mmc_params *mmcp = &path->device->mmc_ident_data;

		if (err != MMC_ERR_NONE || mmcio->cmd.resp[0] != 0x1AA) {
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
				  ("IF_COND: error %d, pattern %08x\n",
				   err, mmcio->cmd.resp[0]));
		} else {
			mmcp->card_features |= CARD_FEATURE_SD20;
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
				  ("SD 2.0 interface conditions: OK\n"));

		}
                PROBE_SET_ACTION(softc, PROBE_SDIO_RESET);
		break;
	}
        case PROBE_SDIO_RESET:
        {
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;

                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                          ("SDIO_RESET: error %d, CCCR CTL register: %08x\n",
                           err, mmcio->cmd.resp[0]));
                PROBE_SET_ACTION(softc, PROBE_SDIO_INIT);
                break;
        }
        case PROBE_SDIO_INIT:
        {
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;
                struct mmc_params *mmcp = &path->device->mmc_ident_data;

                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                          ("SDIO_INIT: error %d, %08x %08x %08x %08x\n",
                           err, mmcio->cmd.resp[0],
                           mmcio->cmd.resp[1],
                           mmcio->cmd.resp[2],
                           mmcio->cmd.resp[3]));

                /*
                 * Error here means that this card is not SDIO,
                 * so proceed with memory init as if nothing has happened
                 */
		if (err != MMC_ERR_NONE) {
                        PROBE_SET_ACTION(softc, PROBE_SEND_APP_OP_COND);
                        break;
		}
                mmcp->card_features |= CARD_FEATURE_SDIO;
                uint32_t ioifcond = mmcio->cmd.resp[0];
                uint32_t io_ocr = ioifcond & R4_IO_OCR_MASK;

                mmcp->sdio_func_count = R4_IO_NUM_FUNCTIONS(ioifcond);
                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                          ("SDIO card: %d functions\n", mmcp->sdio_func_count));
                if (io_ocr == 0) {
                    CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                              ("SDIO OCR invalid?!\n"));
                    break; /* Retry */
                }

                if (io_ocr != 0 && mmcp->io_ocr == 0) {
                        mmcp->io_ocr = io_ocr;
                        break; /* Retry, this time with non-0 OCR */
                }
                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                          ("SDIO OCR: %08x\n", mmcp->io_ocr));

                if (ioifcond & R4_IO_MEM_PRESENT) {
                        /* Combo card -- proceed to memory initialization */
                        PROBE_SET_ACTION(softc, PROBE_SEND_APP_OP_COND);
                } else {
                        /* No memory portion -- get RCA and select card */
                        PROBE_SET_ACTION(softc, PROBE_SEND_RELATIVE_ADDR);
                }
                break;
        }
        case PROBE_MMC_INIT:
        {
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;
                struct mmc_params *mmcp = &path->device->mmc_ident_data;

		if (err != MMC_ERR_NONE) {
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
				  ("MMC_INIT: error %d, resp %08x\n",
				   err, mmcio->cmd.resp[0]));
			PROBE_SET_ACTION(softc, PROBE_INVALID);
                        break;
                }
                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                          ("MMC card, OCR %08x\n", mmcio->cmd.resp[0]));

                if (mmcp->card_ocr == 0) {
                        /* We haven't sent the OCR to the card yet -- do it */
                        mmcp->card_ocr = mmcio->cmd.resp[0];
                        CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                                  ("-> sending OCR to card\n"));
                        break;
                }

                if (!(mmcio->cmd.resp[0] & MMC_OCR_CARD_BUSY)) {
                        CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                                  ("Card is still powering up\n"));
                        break;
                }

                mmcp->card_features |= CARD_FEATURE_MMC | CARD_FEATURE_MEMORY;
                PROBE_SET_ACTION(softc, PROBE_GET_CID);
                break;
        }
	case PROBE_SEND_APP_OP_COND:
	{
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;

		if (err != MMC_ERR_NONE) {
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
				  ("APP_OP_COND: error %d, resp %08x\n",
				   err, mmcio->cmd.resp[0]));
			PROBE_SET_ACTION(softc, PROBE_MMC_INIT);
                        break;
                }

                if (!(softc->flags & PROBE_FLAG_ACMD_SENT)) {
                        /* Don't change the state */
                        softc->flags |= PROBE_FLAG_ACMD_SENT;
                        break;
                }

                softc->flags &= ~PROBE_FLAG_ACMD_SENT;
                if ((mmcio->cmd.resp[0] & MMC_OCR_CARD_BUSY) ||
                    (mmcio->cmd.arg & MMC_OCR_VOLTAGE) == 0) {
                        struct mmc_params *mmcp = &path->device->mmc_ident_data;
                        CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                                  ("Card OCR: %08x\n",  mmcio->cmd.resp[0]));
                        if (mmcp->card_ocr == 0) {
                                mmcp->card_ocr = mmcio->cmd.resp[0];
                                /* Now when we know OCR that we want -- send it to card */
                                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                                          ("-> sending OCR to card\n"));
                        } else {
                                /* We already know the OCR and despite of that we
                                 * are processing the answer to ACMD41 -> move on
                                 */
                                PROBE_SET_ACTION(softc, PROBE_GET_CID);
                        }
                        /* Getting an answer to ACMD41 means the card has memory */
                        mmcp->card_features |= CARD_FEATURE_MEMORY;

                        /* Standard capacity vs High Capacity memory card */
                        if (mmcio->cmd.resp[0] & MMC_OCR_CCS) {
                                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                                          ("Card is SDHC\n"));
                                mmcp->card_features |= CARD_FEATURE_SDHC;
                        }

			/* Whether the card supports 1.8V signaling */
			if (mmcio->cmd.resp[0] & MMC_OCR_S18A) {
				CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
					  ("Card supports 1.8V signaling\n"));
				mmcp->card_features |= CARD_FEATURE_18V;
			}
		} else {
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
				  ("Card not ready: %08x\n",  mmcio->cmd.resp[0]));
			/* Send CMD55+ACMD41 once again  */
			PROBE_SET_ACTION(softc, PROBE_SEND_APP_OP_COND);
		}

                break;
	}
        case PROBE_GET_CID: /* XXX move to mmc_da */
        {
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;

		if (err != MMC_ERR_NONE) {
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
				  ("PROBE_GET_CID: error %d\n", err));
			PROBE_SET_ACTION(softc, PROBE_INVALID);
                        break;
                }

                struct mmc_params *mmcp = &path->device->mmc_ident_data;
                memcpy(mmcp->card_cid, mmcio->cmd.resp, 4 * sizeof(uint32_t));
                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                          ("CID %08x%08x%08x%08x\n",
                           mmcp->card_cid[0],
                           mmcp->card_cid[1],
                           mmcp->card_cid[2],
                           mmcp->card_cid[3]));
		if (mmcp->card_features & CARD_FEATURE_MMC)
			PROBE_SET_ACTION(softc, PROBE_MMC_SET_RELATIVE_ADDR);
		else
			PROBE_SET_ACTION(softc, PROBE_SEND_RELATIVE_ADDR);
                break;
        }
        case PROBE_SEND_RELATIVE_ADDR: {
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;
                struct mmc_params *mmcp = &path->device->mmc_ident_data;
                uint16_t rca = mmcio->cmd.resp[0] >> 16;
                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                          ("Card published RCA: %u\n", rca));
                path->device->mmc_ident_data.card_rca = rca;
		if (err != MMC_ERR_NONE) {
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
				  ("PROBE_SEND_RELATIVE_ADDR: error %d\n", err));
			PROBE_SET_ACTION(softc, PROBE_INVALID);
                        break;
                }

                /* If memory is present, get CSD, otherwise select card */
                if (mmcp->card_features & CARD_FEATURE_MEMORY)
                        PROBE_SET_ACTION(softc, PROBE_GET_CSD);
                else
                        PROBE_SET_ACTION(softc, PROBE_SELECT_CARD);
		break;
        }
	case PROBE_MMC_SET_RELATIVE_ADDR:
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;
		if (err != MMC_ERR_NONE) {
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
			    ("PROBE_MMC_SET_RELATIVE_ADDR: error %d\n", err));
			PROBE_SET_ACTION(softc, PROBE_INVALID);
			break;
		}
		path->device->mmc_ident_data.card_rca = MMC_PROPOSED_RCA;
		PROBE_SET_ACTION(softc, PROBE_GET_CSD);
		break;
        case PROBE_GET_CSD: {
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;

		if (err != MMC_ERR_NONE) {
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
				  ("PROBE_GET_CSD: error %d\n", err));
			PROBE_SET_ACTION(softc, PROBE_INVALID);
                        break;
                }

                struct mmc_params *mmcp = &path->device->mmc_ident_data;
                memcpy(mmcp->card_csd, mmcio->cmd.resp, 4 * sizeof(uint32_t));
                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
                          ("CSD %08x%08x%08x%08x\n",
                           mmcp->card_csd[0],
                           mmcp->card_csd[1],
                           mmcp->card_csd[2],
                           mmcp->card_csd[3]));
                PROBE_SET_ACTION(softc, PROBE_SELECT_CARD);
                break;
        }
        case PROBE_SELECT_CARD: {
		mmcio = &done_ccb->mmcio;
		err = mmcio->cmd.error;
		if (err != MMC_ERR_NONE) {
			CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
				  ("PROBE_SEND_RELATIVE_ADDR: error %d\n", err));
			PROBE_SET_ACTION(softc, PROBE_INVALID);
                        break;
                }

		PROBE_SET_ACTION(softc, PROBE_DONE);
                break;
        }
	default:
		CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
			  ("mmc_probedone: invalid action state 0x%x\n", softc->action));
		panic("default: case in mmc_probe_done()");
	}

        if (softc->action == PROBE_INVALID &&
            (path->device->flags & CAM_DEV_UNCONFIGURED) == 0) {
                CAM_DEBUG(done_ccb->ccb_h.path, CAM_DEBUG_PROBE,
			  ("mmc_probedone: Should send AC_LOST_DEVICE but won't for now\n"));
                //xpt_async(AC_LOST_DEVICE, path, NULL);
        }

	xpt_release_ccb(done_ccb);
        if (softc->action != PROBE_INVALID)
                xpt_schedule(periph, priority);
	/* Drop freeze taken due to CAM_DEV_QFREEZE flag set. */
	int frozen = cam_release_devq(path, 0, 0, 0, FALSE);
        printf("mmc_probedone: remaining freezecnt %d\n", frozen);

	if (softc->action == PROBE_DONE) {
                /* Notify the system that the device is found! */
		if (periph->path->device->flags & CAM_DEV_UNCONFIGURED) {
			path->device->flags &= ~CAM_DEV_UNCONFIGURED;
			xpt_acquire_device(path->device);
			done_ccb->ccb_h.func_code = XPT_GDEV_TYPE;
			xpt_action(done_ccb);
			xpt_async(AC_FOUND_DEVICE, path, done_ccb);
		}
	}
        if (softc->action == PROBE_DONE || softc->action == PROBE_INVALID) {
                cam_periph_invalidate(periph);
                cam_periph_release_locked(periph);
        }
}