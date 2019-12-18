#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mmc_data {int flags; int len; } ;
struct mmc_command {int opcode; int flags; int arg; int /*<<< orphan*/  mrq; struct mmc_data* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  clock; } ;
struct TYPE_4__ {TYPE_1__ ios; } ;
struct dwmmc_softc {int hwtype; int flags; scalar_t__ use_pio; scalar_t__ use_auto_stop; int /*<<< orphan*/  req; TYPE_2__ host; struct mmc_command* curcmd; } ;

/* Variables and functions */
 int CARD_INIT_DONE ; 
 int HWTYPE_MASK ; 
 int HWTYPE_ROCKCHIP ; 
 int MMC_DATA_STREAM ; 
 int MMC_DATA_WRITE ; 
 scalar_t__ MMC_GO_IDLE_STATE ; 
 scalar_t__ MMC_GO_INACTIVE_STATE ; 
 scalar_t__ MMC_READ_MULTIPLE_BLOCK ; 
 scalar_t__ MMC_RSP (int) ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_CRC ; 
 scalar_t__ MMC_RSP_NONE ; 
 int MMC_SECTOR_SIZE ; 
 scalar_t__ MMC_SEND_STATUS ; 
 scalar_t__ MMC_STOP_TRANSMISSION ; 
 scalar_t__ MMC_WRITE_MULTIPLE_BLOCK ; 
 int /*<<< orphan*/  SDMMC_BLKSIZ ; 
 int /*<<< orphan*/  SDMMC_BYTCNT ; 
 int /*<<< orphan*/  SDMMC_CMD ; 
 int /*<<< orphan*/  SDMMC_CMDARG ; 
 int SDMMC_CMD_DATA_EXP ; 
 int SDMMC_CMD_DATA_WRITE ; 
 int SDMMC_CMD_MODE_STREAM ; 
 int SDMMC_CMD_RESP_CRC ; 
 int SDMMC_CMD_RESP_EXP ; 
 int SDMMC_CMD_RESP_LONG ; 
 int SDMMC_CMD_SEND_ASTOP ; 
 int SDMMC_CMD_SEND_INIT ; 
 int SDMMC_CMD_START ; 
 int SDMMC_CMD_STOP_ABORT ; 
 int SDMMC_CMD_USE_HOLD_REG ; 
 int SDMMC_CMD_WAIT_PRVDATA ; 
 int /*<<< orphan*/  SDMMC_TMOUT ; 
 int /*<<< orphan*/  WRITE4 (struct dwmmc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_prepare (struct dwmmc_softc*,struct mmc_command*) ; 
 int /*<<< orphan*/  dprintf (char*,int) ; 
 int /*<<< orphan*/  dwmmc_setup_bus (struct dwmmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pio_prepare (struct dwmmc_softc*,struct mmc_command*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
dwmmc_start_cmd(struct dwmmc_softc *sc, struct mmc_command *cmd)
{
	struct mmc_data *data;
	uint32_t blksz;
	uint32_t cmdr;

	sc->curcmd = cmd;
	data = cmd->data;

	if ((sc->hwtype & HWTYPE_MASK) == HWTYPE_ROCKCHIP)
		dwmmc_setup_bus(sc, sc->host.ios.clock);

	/* XXX Upper layers don't always set this */
	cmd->mrq = sc->req;

	/* Begin setting up command register. */

	cmdr = cmd->opcode;

	dprintf("cmd->opcode 0x%08x\n", cmd->opcode);

	if (cmd->opcode == MMC_STOP_TRANSMISSION ||
	    cmd->opcode == MMC_GO_IDLE_STATE ||
	    cmd->opcode == MMC_GO_INACTIVE_STATE)
		cmdr |= SDMMC_CMD_STOP_ABORT;
	else if (cmd->opcode != MMC_SEND_STATUS && data)
		cmdr |= SDMMC_CMD_WAIT_PRVDATA;

	/* Set up response handling. */
	if (MMC_RSP(cmd->flags) != MMC_RSP_NONE) {
		cmdr |= SDMMC_CMD_RESP_EXP;
		if (cmd->flags & MMC_RSP_136)
			cmdr |= SDMMC_CMD_RESP_LONG;
	}

	if (cmd->flags & MMC_RSP_CRC)
		cmdr |= SDMMC_CMD_RESP_CRC;

	/*
	 * XXX: Not all platforms want this.
	 */
	cmdr |= SDMMC_CMD_USE_HOLD_REG;

	if ((sc->flags & CARD_INIT_DONE) == 0) {
		sc->flags |= (CARD_INIT_DONE);
		cmdr |= SDMMC_CMD_SEND_INIT;
	}

	if (data) {
		if ((cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK ||
		     cmd->opcode == MMC_READ_MULTIPLE_BLOCK) &&
		     sc->use_auto_stop)
			cmdr |= SDMMC_CMD_SEND_ASTOP;

		cmdr |= SDMMC_CMD_DATA_EXP;
		if (data->flags & MMC_DATA_STREAM)
			cmdr |= SDMMC_CMD_MODE_STREAM;
		if (data->flags & MMC_DATA_WRITE)
			cmdr |= SDMMC_CMD_DATA_WRITE;

		WRITE4(sc, SDMMC_TMOUT, 0xffffffff);
		WRITE4(sc, SDMMC_BYTCNT, data->len);
		blksz = (data->len < MMC_SECTOR_SIZE) ? \
			 data->len : MMC_SECTOR_SIZE;
		WRITE4(sc, SDMMC_BLKSIZ, blksz);

		if (sc->use_pio) {
			pio_prepare(sc, cmd);
		} else {
			dma_prepare(sc, cmd);
		}
		wmb();
	}

	dprintf("cmdr 0x%08x\n", cmdr);

	WRITE4(sc, SDMMC_CMDARG, cmd->arg);
	wmb();
	WRITE4(sc, SDMMC_CMD, cmdr | SDMMC_CMD_START);
}