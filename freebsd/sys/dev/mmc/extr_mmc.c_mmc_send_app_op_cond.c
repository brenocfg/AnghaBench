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
typedef  int uint32_t ;
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct mmc_command {int arg; int flags; int* resp; int /*<<< orphan*/ * data; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ACMD_SD_SEND_OP_COND ; 
 int /*<<< orphan*/  CMD_RETRIES ; 
 int MMC_CMD_BCR ; 
 int MMC_ERR_NONE ; 
 int MMC_ERR_TIMEOUT ; 
 int MMC_OCR_CARD_BUSY ; 
 int MMC_OCR_VOLTAGE ; 
 int MMC_RSP_R3 ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_ms_delay (int) ; 
 int mmc_wait_for_app_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmc_send_app_op_cond(struct mmc_softc *sc, uint32_t ocr, uint32_t *rocr)
{
	struct mmc_command cmd;
	int err = MMC_ERR_NONE, i;

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = ACMD_SD_SEND_OP_COND;
	cmd.arg = ocr;
	cmd.flags = MMC_RSP_R3 | MMC_CMD_BCR;
	cmd.data = NULL;

	for (i = 0; i < 1000; i++) {
		err = mmc_wait_for_app_cmd(sc->dev, sc->dev, 0, &cmd,
		    CMD_RETRIES);
		if (err != MMC_ERR_NONE)
			break;
		if ((cmd.resp[0] & MMC_OCR_CARD_BUSY) ||
		    (ocr & MMC_OCR_VOLTAGE) == 0)
			break;
		err = MMC_ERR_TIMEOUT;
		mmc_ms_delay(10);
	}
	if (rocr && err == MMC_ERR_NONE)
		*rocr = cmd.resp[0];
	return (err);
}