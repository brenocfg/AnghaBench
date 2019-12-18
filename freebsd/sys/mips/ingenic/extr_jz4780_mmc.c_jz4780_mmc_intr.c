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
struct mmc_data {int len; } ;
struct jz4780_mmc_softc {int sc_dma_inuse; int sc_intr_seen; int sc_resid; int sc_intr_wait; TYPE_2__* sc_req; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_4__ {TYPE_1__* cmd; } ;
struct TYPE_3__ {struct mmc_data* data; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int JZ_INT_DMAEND ; 
 int JZ_INT_END_CMD_RES ; 
 int JZ_INT_RXFIFO_RD_REQ ; 
 int JZ_INT_TIMEOUT_READ ; 
 int JZ_INT_TIMEOUT_RES ; 
 int JZ_INT_TXFIFO_WR_REQ ; 
 int /*<<< orphan*/  JZ_MMC_LOCK (struct jz4780_mmc_softc*) ; 
 int JZ_MMC_READ_4 (struct jz4780_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_MMC_UNLOCK (struct jz4780_mmc_softc*) ; 
 int /*<<< orphan*/  JZ_MMC_WRITE_4 (struct jz4780_mmc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JZ_MSC_DMAC ; 
 int /*<<< orphan*/  JZ_MSC_DMACMD ; 
 int /*<<< orphan*/  JZ_MSC_DMADA ; 
 int /*<<< orphan*/  JZ_MSC_DMALEN ; 
 int /*<<< orphan*/  JZ_MSC_DMANDA ; 
 int /*<<< orphan*/  JZ_MSC_IFLG ; 
 int JZ_MSC_INT_ERR_BITS ; 
 int /*<<< orphan*/  JZ_MSC_STAT ; 
 int /*<<< orphan*/  MMC_ERR_FAILED ; 
 int /*<<< orphan*/  MMC_ERR_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  jz4780_mmc_pio_transfer (struct jz4780_mmc_softc*,struct mmc_data*) ; 
 int /*<<< orphan*/  jz4780_mmc_read_response (struct jz4780_mmc_softc*) ; 
 int /*<<< orphan*/  jz4780_mmc_req_done (struct jz4780_mmc_softc*) ; 
 int /*<<< orphan*/  jz4780_mmc_req_ok (struct jz4780_mmc_softc*) ; 
 int /*<<< orphan*/  jz4780_mmc_start_dma (struct jz4780_mmc_softc*) ; 

__attribute__((used)) static void
jz4780_mmc_intr(void *arg)
{
	struct jz4780_mmc_softc *sc;
	struct mmc_data *data;
	uint32_t rint;

	sc = (struct jz4780_mmc_softc *)arg;
	JZ_MMC_LOCK(sc);
	rint  = JZ_MMC_READ_4(sc, JZ_MSC_IFLG);
#if defined(JZ_MMC_DEBUG)
	device_printf(sc->sc_dev, "rint: %#x, stat: %#x\n",
	    rint, JZ_MMC_READ_4(sc, JZ_MSC_STAT));
	if (sc->sc_dma_inuse == 1 && (sc->sc_intr_seen & JZ_INT_DMAEND) == 0)
		device_printf(sc->sc_dev, "\tdmada %#x dmanext %#x dmac %#x"
		    " dmalen %d dmacmd %#x\n",
		    JZ_MMC_READ_4(sc, JZ_MSC_DMADA),
		    JZ_MMC_READ_4(sc, JZ_MSC_DMANDA),
		    JZ_MMC_READ_4(sc, JZ_MSC_DMAC),
		    JZ_MMC_READ_4(sc, JZ_MSC_DMALEN),
		    JZ_MMC_READ_4(sc, JZ_MSC_DMACMD));
#endif
	if (sc->sc_req == NULL) {
		device_printf(sc->sc_dev,
		    "Spurious interrupt - no active request, rint: 0x%08X\n",
		    rint);
		goto end;
	}
	if (rint & JZ_MSC_INT_ERR_BITS) {
#if defined(JZ_MMC_DEBUG)
		device_printf(sc->sc_dev, "controller error, rint %#x stat %#x\n",
		    rint,  JZ_MMC_READ_4(sc, JZ_MSC_STAT));
#endif
		if (rint & (JZ_INT_TIMEOUT_RES | JZ_INT_TIMEOUT_READ))
			sc->sc_req->cmd->error = MMC_ERR_TIMEOUT;
		else
			sc->sc_req->cmd->error = MMC_ERR_FAILED;
		jz4780_mmc_req_done(sc);
		goto end;
	}
	data = sc->sc_req->cmd->data;
	/* Check for command response */
	if (rint & JZ_INT_END_CMD_RES) {
		jz4780_mmc_read_response(sc);
		if (sc->sc_dma_inuse == 1)
			jz4780_mmc_start_dma(sc);
	}
	if (data != NULL) {
		if (sc->sc_dma_inuse == 1 && (rint & JZ_INT_DMAEND))
			sc->sc_resid = data->len >> 2;
		else if (sc->sc_dma_inuse == 0 &&
		    (rint & (JZ_INT_TXFIFO_WR_REQ | JZ_INT_RXFIFO_RD_REQ)))
			jz4780_mmc_pio_transfer(sc, data);
	}
	sc->sc_intr_seen |= rint;
	if ((sc->sc_intr_seen & sc->sc_intr_wait) == sc->sc_intr_wait)
		jz4780_mmc_req_ok(sc);
end:
	JZ_MMC_WRITE_4(sc, JZ_MSC_IFLG, rint);
	JZ_MMC_UNLOCK(sc);
}