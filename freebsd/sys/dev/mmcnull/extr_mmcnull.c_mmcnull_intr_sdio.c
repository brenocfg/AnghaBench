#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int opcode; int* resp; TYPE_1__* data; } ;
struct ccb_mmcio {TYPE_2__ cmd; } ;
union ccb {TYPE_3__ ccb_h; struct ccb_mmcio mmcio; } ;
struct mmcnull_softc {union ccb* cur_ccb; int /*<<< orphan*/  dev; int /*<<< orphan*/  tick; int /*<<< orphan*/  sc_mtx; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
#define  ACMD_SD_SEND_OP_COND 138 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
#define  IO_SEND_OP_COND 137 
 int /*<<< orphan*/  MA_OWNED ; 
#define  MMC_ALL_SEND_CID 136 
#define  MMC_APP_CMD 135 
#define  MMC_GO_IDLE_STATE 134 
 int MMC_OCR_CARD_BUSY ; 
#define  MMC_READ_MULTIPLE_BLOCK 133 
#define  MMC_READ_SINGLE_BLOCK 132 
#define  MMC_SELECT_CARD 131 
 int R1_APP_CMD ; 
 int R4_IO_MEM_PRESENT ; 
#define  SD_IO_RW_DIRECT 130 
#define  SD_SEND_IF_COND 129 
#define  SD_SEND_RELATIVE_ADDR 128 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct mmcnull_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hz ; 
 int /*<<< orphan*/  mmcnull_intr_sdio_newintr ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
mmcnull_intr_sdio(void *xsc) {
	struct mmcnull_softc *sc;
	union ccb *ccb;
	struct ccb_mmcio *mmcio;

	sc = (struct mmcnull_softc *) xsc;
	mtx_assert(&sc->sc_mtx, MA_OWNED);

	ccb = sc->cur_ccb;
	mmcio = &ccb->mmcio;
	device_printf(sc->dev, "mmcnull_intr: MMC command = %d\n",
		      mmcio->cmd.opcode);

	switch (mmcio->cmd.opcode) {
	case MMC_GO_IDLE_STATE:
		device_printf(sc->dev, "Reset device\n");
		break;
	case SD_SEND_IF_COND:
		mmcio->cmd.resp[0] = 0x1AA; // To match mmc_xpt expectations :-)
		break;
	case MMC_APP_CMD:
		mmcio->cmd.resp[0] = R1_APP_CMD;
		break;
	case IO_SEND_OP_COND:
		mmcio->cmd.resp[0] = 0x12345678;
		mmcio->cmd.resp[0] |= ~ R4_IO_MEM_PRESENT;
		break;
	case SD_SEND_RELATIVE_ADDR:
	case MMC_SELECT_CARD:
		mmcio->cmd.resp[0] = 0x1 << 16;
		break;
	case ACMD_SD_SEND_OP_COND:
		/* TODO: steal valid OCR from somewhere :-) */
		mmcio->cmd.resp[0] = 0x123;
		mmcio->cmd.resp[0] |= MMC_OCR_CARD_BUSY;
		break;
	case MMC_ALL_SEND_CID:
		mmcio->cmd.resp[0] = 0x1234;
		mmcio->cmd.resp[1] = 0x5678;
		mmcio->cmd.resp[2] = 0x9ABC;
		mmcio->cmd.resp[3] = 0xDEF0;
		break;
	case MMC_READ_SINGLE_BLOCK:
	case MMC_READ_MULTIPLE_BLOCK:
		strcpy(mmcio->cmd.data->data, "WTF?!");
		break;
	case SD_IO_RW_DIRECT:
		device_printf(sc->dev, "Scheduling interrupt generation...\n");
		callout_reset(&sc->tick, hz / 10, mmcnull_intr_sdio_newintr, sc);
		break;
	default:
		device_printf(sc->dev, "mmcnull_intr_sdio: unknown command\n");
	}
	ccb->ccb_h.status = CAM_REQ_CMP;

	sc->cur_ccb = NULL;
	xpt_done(ccb);
}