#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
struct hifn_softc {int sc_dmaier; int sc_cmdk; int sc_srck; int sc_resk; int sc_cmdu; int sc_srcu; int sc_resu; int sc_flags; int sc_needwakeup; int /*<<< orphan*/  sc_cid; int /*<<< orphan*/  sc_dstu; int /*<<< orphan*/  sc_dev; struct hifn_command** sc_hifn_commands; int /*<<< orphan*/  sc_dstk; int /*<<< orphan*/  sc_resi; int /*<<< orphan*/  sc_dsti; int /*<<< orphan*/  sc_srci; int /*<<< orphan*/  sc_cmdi; struct hifn_dma* sc_dma; } ;
struct hifn_dma {TYPE_3__* cmdr; TYPE_2__* srcr; int /*<<< orphan*/ ** result_bufs; TYPE_1__* resr; } ;
struct hifn_command {int base_masks; } ;
struct TYPE_8__ {int /*<<< orphan*/  hst_opackets; int /*<<< orphan*/  hst_abort; } ;
struct TYPE_7__ {int l; } ;
struct TYPE_6__ {int l; } ;
struct TYPE_5__ {int l; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CRYPTO_ASYMQ ; 
 int CRYPTO_SYMQ ; 
 int /*<<< orphan*/  HIFN_1_DMA_CSR ; 
 int /*<<< orphan*/  HIFN_1_DMA_IER ; 
 int /*<<< orphan*/  HIFN_1_PUB_STATUS ; 
 int HIFN_BASE_CMD_MAC ; 
 int /*<<< orphan*/  HIFN_CMDR_SYNC (struct hifn_softc*,int,int) ; 
 int /*<<< orphan*/  HIFN_CMD_SYNC (struct hifn_softc*,int,int) ; 
 int HIFN_DMACSR_C_ABORT ; 
 int HIFN_DMACSR_C_WAIT ; 
 int HIFN_DMACSR_D_ABORT ; 
 int HIFN_DMACSR_D_OVER ; 
 int HIFN_DMACSR_ILLR ; 
 int HIFN_DMACSR_ILLW ; 
 int HIFN_DMACSR_PUBDONE ; 
 int HIFN_DMACSR_R_ABORT ; 
 int HIFN_DMACSR_R_OVER ; 
 int HIFN_DMACSR_S_ABORT ; 
 int HIFN_DMAIER_C_WAIT ; 
 int HIFN_D_CMD_RSIZE ; 
 int HIFN_D_RES_RSIZE ; 
 int HIFN_D_SRC_RSIZE ; 
 int /*<<< orphan*/  HIFN_D_VALID ; 
 int HIFN_HAS_PUBLIC ; 
 int HIFN_IS_7811 ; 
 int /*<<< orphan*/  HIFN_LOCK (struct hifn_softc*) ; 
 int HIFN_PUBSTS_DONE ; 
 int /*<<< orphan*/  HIFN_RESR_SYNC (struct hifn_softc*,int,int) ; 
 int /*<<< orphan*/  HIFN_RES_SYNC (struct hifn_softc*,int,int) ; 
 int /*<<< orphan*/  HIFN_SRCR_SYNC (struct hifn_softc*,int,int) ; 
 int /*<<< orphan*/  HIFN_UNLOCK (struct hifn_softc*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int READ_REG_1 (struct hifn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG_1 (struct hifn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_unblock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hifn_abort (struct hifn_softc*) ; 
 int /*<<< orphan*/  hifn_callback (struct hifn_softc*,struct hifn_command*,int /*<<< orphan*/ *) ; 
 scalar_t__ hifn_debug ; 
 TYPE_4__ hifnstats ; 
 int htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
hifn_intr(void *arg)
{
	struct hifn_softc *sc = arg;
	struct hifn_dma *dma;
	u_int32_t dmacsr, restart;
	int i, u;

	dmacsr = READ_REG_1(sc, HIFN_1_DMA_CSR);

	/* Nothing in the DMA unit interrupted */
	if ((dmacsr & sc->sc_dmaier) == 0)
		return;

	HIFN_LOCK(sc);

	dma = sc->sc_dma;

#ifdef HIFN_DEBUG
	if (hifn_debug) {
		device_printf(sc->sc_dev,
		    "irq: stat %08x ien %08x damier %08x i %d/%d/%d/%d k %d/%d/%d/%d u %d/%d/%d/%d\n",
		    dmacsr, READ_REG_1(sc, HIFN_1_DMA_IER), sc->sc_dmaier,
		    sc->sc_cmdi, sc->sc_srci, sc->sc_dsti, sc->sc_resi,
		    sc->sc_cmdk, sc->sc_srck, sc->sc_dstk, sc->sc_resk,
		    sc->sc_cmdu, sc->sc_srcu, sc->sc_dstu, sc->sc_resu);
	}
#endif

	WRITE_REG_1(sc, HIFN_1_DMA_CSR, dmacsr & sc->sc_dmaier);

	if ((sc->sc_flags & HIFN_HAS_PUBLIC) &&
	    (dmacsr & HIFN_DMACSR_PUBDONE))
		WRITE_REG_1(sc, HIFN_1_PUB_STATUS,
		    READ_REG_1(sc, HIFN_1_PUB_STATUS) | HIFN_PUBSTS_DONE);

	restart = dmacsr & (HIFN_DMACSR_D_OVER | HIFN_DMACSR_R_OVER);
	if (restart)
		device_printf(sc->sc_dev, "overrun %x\n", dmacsr);

	if (sc->sc_flags & HIFN_IS_7811) {
		if (dmacsr & HIFN_DMACSR_ILLR)
			device_printf(sc->sc_dev, "illegal read\n");
		if (dmacsr & HIFN_DMACSR_ILLW)
			device_printf(sc->sc_dev, "illegal write\n");
	}

	restart = dmacsr & (HIFN_DMACSR_C_ABORT | HIFN_DMACSR_S_ABORT |
	    HIFN_DMACSR_D_ABORT | HIFN_DMACSR_R_ABORT);
	if (restart) {
		device_printf(sc->sc_dev, "abort, resetting.\n");
		hifnstats.hst_abort++;
		hifn_abort(sc);
		HIFN_UNLOCK(sc);
		return;
	}

	if ((dmacsr & HIFN_DMACSR_C_WAIT) && (sc->sc_cmdu == 0)) {
		/*
		 * If no slots to process and we receive a "waiting on
		 * command" interrupt, we disable the "waiting on command"
		 * (by clearing it).
		 */
		sc->sc_dmaier &= ~HIFN_DMAIER_C_WAIT;
		WRITE_REG_1(sc, HIFN_1_DMA_IER, sc->sc_dmaier);
	}

	/* clear the rings */
	i = sc->sc_resk; u = sc->sc_resu;
	while (u != 0) {
		HIFN_RESR_SYNC(sc, i,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		if (dma->resr[i].l & htole32(HIFN_D_VALID)) {
			HIFN_RESR_SYNC(sc, i,
			    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
			break;
		}

		if (i != HIFN_D_RES_RSIZE) {
			struct hifn_command *cmd;
			u_int8_t *macbuf = NULL;

			HIFN_RES_SYNC(sc, i, BUS_DMASYNC_POSTREAD);
			cmd = sc->sc_hifn_commands[i];
			KASSERT(cmd != NULL,
				("hifn_intr: null command slot %u", i));
			sc->sc_hifn_commands[i] = NULL;

			if (cmd->base_masks & HIFN_BASE_CMD_MAC) {
				macbuf = dma->result_bufs[i];
				macbuf += 12;
			}

			hifn_callback(sc, cmd, macbuf);
			hifnstats.hst_opackets++;
			u--;
		}

		if (++i == (HIFN_D_RES_RSIZE + 1))
			i = 0;
	}
	sc->sc_resk = i; sc->sc_resu = u;

	i = sc->sc_srck; u = sc->sc_srcu;
	while (u != 0) {
		if (i == HIFN_D_SRC_RSIZE)
			i = 0;
		HIFN_SRCR_SYNC(sc, i,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		if (dma->srcr[i].l & htole32(HIFN_D_VALID)) {
			HIFN_SRCR_SYNC(sc, i,
			    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
			break;
		}
		i++, u--;
	}
	sc->sc_srck = i; sc->sc_srcu = u;

	i = sc->sc_cmdk; u = sc->sc_cmdu;
	while (u != 0) {
		HIFN_CMDR_SYNC(sc, i,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		if (dma->cmdr[i].l & htole32(HIFN_D_VALID)) {
			HIFN_CMDR_SYNC(sc, i,
			    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
			break;
		}
		if (i != HIFN_D_CMD_RSIZE) {
			u--;
			HIFN_CMD_SYNC(sc, i, BUS_DMASYNC_POSTWRITE);
		}
		if (++i == (HIFN_D_CMD_RSIZE + 1))
			i = 0;
	}
	sc->sc_cmdk = i; sc->sc_cmdu = u;

	HIFN_UNLOCK(sc);

	if (sc->sc_needwakeup) {		/* XXX check high watermark */
		int wakeup = sc->sc_needwakeup & (CRYPTO_SYMQ|CRYPTO_ASYMQ);
#ifdef HIFN_DEBUG
		if (hifn_debug)
			device_printf(sc->sc_dev,
				"wakeup crypto (%x) u %d/%d/%d/%d\n",
				sc->sc_needwakeup,
				sc->sc_cmdu, sc->sc_srcu, sc->sc_dstu, sc->sc_resu);
#endif
		sc->sc_needwakeup &= ~wakeup;
		crypto_unblock(sc->sc_cid, wakeup);
	}
}