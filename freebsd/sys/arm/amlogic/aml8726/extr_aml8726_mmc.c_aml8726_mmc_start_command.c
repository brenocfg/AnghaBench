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
struct mmc_ios {scalar_t__ bus_width; } ;
struct mmc_data {int len; int flags; int /*<<< orphan*/  data; } ;
struct mmc_command {int opcode; int flags; int error; int arg; TYPE_2__* mrq; struct mmc_data* data; } ;
struct TYPE_3__ {struct mmc_ios ios; } ;
struct aml8726_mmc_softc {int port; int stop_timeout; int /*<<< orphan*/  ch; struct mmc_command* cmd; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmatag; TYPE_1__ host; } ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_4__ {struct mmc_command* stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_MMC_CMD_ARGUMENT_REG ; 
 int AML_MMC_CMD_CHECK_DAT0_BUSY ; 
 int AML_MMC_CMD_CMD_HAS_DATA ; 
 int AML_MMC_CMD_REP_PKG_CNT_SHIFT ; 
 int AML_MMC_CMD_RESP_BITS_SHIFT ; 
 int AML_MMC_CMD_RESP_CRC7_FROM_8 ; 
 int AML_MMC_CMD_RESP_HAS_DATA ; 
 int AML_MMC_CMD_RESP_NO_CRC7 ; 
 int /*<<< orphan*/  AML_MMC_CMD_SEND_REG ; 
 int AML_MMC_CMD_START_BIT ; 
 int AML_MMC_CMD_TIMEOUT ; 
 int AML_MMC_CMD_TRANS_BIT_HOST ; 
 int /*<<< orphan*/  AML_MMC_DMA_ADDR_REG ; 
 int AML_MMC_EXTENSION_PKT_SIZE_SHIFT ; 
 int /*<<< orphan*/  AML_MMC_EXTENSION_REG ; 
 int AML_MMC_MAX_TIMEOUT ; 
 int /*<<< orphan*/  AML_MMC_MULT_CONFIG_REG ; 
 int AML_MMC_MULT_CONFIG_STREAM_EN ; 
 int AML_MMC_READ_TIMEOUT ; 
 int AML_MMC_WRITE_TIMEOUT ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_mmc_softc*,int /*<<< orphan*/ ,int) ; 
 int MMC_DATA_MULTI ; 
 int MMC_DATA_READ ; 
 int MMC_DATA_STREAM ; 
 int MMC_DATA_WRITE ; 
 int MMC_ERR_INVALID ; 
 int MMC_ERR_NONE ; 
 int MMC_ERR_NO_MEMORY ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_BUSY ; 
 int MMC_RSP_CRC ; 
 int MMC_RSP_PRESENT ; 
 int MMC_SECTOR_SIZE ; 
 int /*<<< orphan*/  MSECS_TO_TICKS (int) ; 
 int /*<<< orphan*/  aml8726_mmc_mapmem ; 
 int /*<<< orphan*/  aml8726_mmc_soft_reset (struct aml8726_mmc_softc*,int) ; 
 int /*<<< orphan*/  aml8726_mmc_timeout ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_width_4 ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aml8726_mmc_softc*) ; 

__attribute__((used)) static int
aml8726_mmc_start_command(struct aml8726_mmc_softc *sc, struct mmc_command *cmd)
{
	struct mmc_ios *ios = &sc->host.ios;
	bus_addr_t baddr;
	uint32_t block_size;
	uint32_t bus_width;
	uint32_t cmdr;
	uint32_t extr;
	uint32_t mcfgr;
	uint32_t nbits_per_pkg;
	uint32_t timeout;
	int error;
	struct mmc_data *data;

	if (cmd->opcode > 0x3f)
		return (MMC_ERR_INVALID);

	/*
	 * Ensure the hardware state machine is in a known state.
	 */
	aml8726_mmc_soft_reset(sc, true);

	/*
	 * Start and transmission bits are per section 4.7.2 of the:
	 *
	 *   SD Specifications Part 1
	 *   Physical Layer Simplified Specification
	 *   Version 4.10
	 */
	cmdr = AML_MMC_CMD_START_BIT | AML_MMC_CMD_TRANS_BIT_HOST | cmd->opcode;
	baddr = 0;
	extr = 0;
	mcfgr = sc->port;
	timeout = AML_MMC_CMD_TIMEOUT;

	/*
	 * If this is a linked command, then use the previous timeout.
	 */
	if (cmd == cmd->mrq->stop && sc->stop_timeout)
		timeout = sc->stop_timeout;
	sc->stop_timeout = 0;

	if ((cmd->flags & MMC_RSP_136) != 0) {
		cmdr |= AML_MMC_CMD_RESP_CRC7_FROM_8;
		cmdr |= (133 << AML_MMC_CMD_RESP_BITS_SHIFT);
	} else if ((cmd->flags & MMC_RSP_PRESENT) != 0)
		cmdr |= (45 << AML_MMC_CMD_RESP_BITS_SHIFT);

	if ((cmd->flags & MMC_RSP_CRC) == 0)
		cmdr |= AML_MMC_CMD_RESP_NO_CRC7;

	if ((cmd->flags & MMC_RSP_BUSY) != 0)
		cmdr |= AML_MMC_CMD_CHECK_DAT0_BUSY;

	data = cmd->data;

	if (data && data->len &&
	    (data->flags & (MMC_DATA_READ | MMC_DATA_WRITE)) != 0) {
		block_size = data->len;

		if ((data->flags & MMC_DATA_MULTI) != 0) {
			block_size = MMC_SECTOR_SIZE;
			if ((data->len % block_size) != 0)
				return (MMC_ERR_INVALID);
		}

		cmdr |= (((data->len / block_size) - 1) <<
		    AML_MMC_CMD_REP_PKG_CNT_SHIFT);

		mcfgr |= (data->flags & MMC_DATA_STREAM) ?
		    AML_MMC_MULT_CONFIG_STREAM_EN : 0;

		/*
		 * The number of bits per package equals the number
		 * of data bits + the number of CRC bits.  There are
		 * 16 bits of CRC calculate per bus line.
		 *
		 * A completed package appears to be detected by when
		 * a counter decremented by the width underflows, thus
		 * a value of zero always transfers 1 (or 4 bits depending
		 * on the mode) which is why bus_width is subtracted.
		 */
		bus_width = (ios->bus_width == bus_width_4) ? 4 : 1;
		nbits_per_pkg = block_size * 8 + 16 * bus_width - bus_width;
		if (nbits_per_pkg > 0x3fff)
			return (MMC_ERR_INVALID);

		extr |= (nbits_per_pkg << AML_MMC_EXTENSION_PKT_SIZE_SHIFT);

		error = bus_dmamap_load(sc->dmatag, sc->dmamap,
		    data->data, data->len, aml8726_mmc_mapmem, &baddr,
		    BUS_DMA_NOWAIT);
		if (error)
			return (MMC_ERR_NO_MEMORY);

		if ((data->flags & MMC_DATA_READ) != 0) {
			cmdr |= AML_MMC_CMD_RESP_HAS_DATA;
			bus_dmamap_sync(sc->dmatag, sc->dmamap,
			    BUS_DMASYNC_PREREAD);
			timeout = AML_MMC_READ_TIMEOUT *
			    (data->len / block_size);
		} else {
			cmdr |= AML_MMC_CMD_CMD_HAS_DATA;
			bus_dmamap_sync(sc->dmatag, sc->dmamap,
			    BUS_DMASYNC_PREWRITE);
			timeout = AML_MMC_WRITE_TIMEOUT *
			    (data->len / block_size);
		}

		/*
		 * Stop terminates a multiblock read / write and thus
		 * can take as long to execute as an actual read / write.
		 */
		if (cmd->mrq->stop != NULL)
			sc->stop_timeout = timeout;
	}

	sc->cmd = cmd;

	cmd->error = MMC_ERR_NONE;

	if (timeout > AML_MMC_MAX_TIMEOUT)
		timeout = AML_MMC_MAX_TIMEOUT;

	callout_reset(&sc->ch, MSECS_TO_TICKS(timeout),
	    aml8726_mmc_timeout, sc);

	CSR_WRITE_4(sc, AML_MMC_CMD_ARGUMENT_REG, cmd->arg);
	CSR_WRITE_4(sc, AML_MMC_MULT_CONFIG_REG, mcfgr);
	CSR_WRITE_4(sc, AML_MMC_EXTENSION_REG, extr);
	CSR_WRITE_4(sc, AML_MMC_DMA_ADDR_REG, (uint32_t)baddr);

	CSR_WRITE_4(sc, AML_MMC_CMD_SEND_REG, cmdr);
	CSR_BARRIER(sc, AML_MMC_CMD_SEND_REG);

	return (MMC_ERR_NONE);
}