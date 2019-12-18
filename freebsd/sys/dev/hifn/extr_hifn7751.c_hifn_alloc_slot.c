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
struct hifn_softc {size_t sc_cmdi; size_t sc_cmdk; size_t sc_srci; size_t sc_srck; size_t sc_dsti; size_t sc_dstk; size_t sc_resi; size_t sc_resk; struct hifn_dma* sc_dma; } ;
struct hifn_dma {TYPE_4__* resr; TYPE_3__* dstr; TYPE_2__* srcr; TYPE_1__* cmdr; } ;
struct TYPE_8__ {void* l; } ;
struct TYPE_7__ {void* l; } ;
struct TYPE_6__ {void* l; } ;
struct TYPE_5__ {void* l; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  HIFN_CMDR_SYNC (struct hifn_softc*,size_t,int) ; 
 int /*<<< orphan*/  HIFN_DSTR_SYNC (struct hifn_softc*,size_t,int) ; 
 size_t HIFN_D_CMD_RSIZE ; 
 size_t HIFN_D_DST_RSIZE ; 
 int HIFN_D_JUMP ; 
 int HIFN_D_MASKDONEIRQ ; 
 size_t HIFN_D_RES_RSIZE ; 
 size_t HIFN_D_SRC_RSIZE ; 
 int HIFN_D_VALID ; 
 int /*<<< orphan*/  HIFN_RESR_SYNC (struct hifn_softc*,size_t,int) ; 
 int /*<<< orphan*/  HIFN_SRCR_SYNC (struct hifn_softc*,size_t,int) ; 
 void* htole32 (int) ; 

__attribute__((used)) static void
hifn_alloc_slot(struct hifn_softc *sc, int *cmdp, int *srcp, int *dstp, int *resp)
{
	struct hifn_dma *dma = sc->sc_dma;

	if (sc->sc_cmdi == HIFN_D_CMD_RSIZE) {
		sc->sc_cmdi = 0;
		dma->cmdr[HIFN_D_CMD_RSIZE].l = htole32(HIFN_D_VALID |
		    HIFN_D_JUMP | HIFN_D_MASKDONEIRQ);
		HIFN_CMDR_SYNC(sc, HIFN_D_CMD_RSIZE,
		    BUS_DMASYNC_PREWRITE | BUS_DMASYNC_PREREAD);
	}
	*cmdp = sc->sc_cmdi++;
	sc->sc_cmdk = sc->sc_cmdi;

	if (sc->sc_srci == HIFN_D_SRC_RSIZE) {
		sc->sc_srci = 0;
		dma->srcr[HIFN_D_SRC_RSIZE].l = htole32(HIFN_D_VALID |
		    HIFN_D_JUMP | HIFN_D_MASKDONEIRQ);
		HIFN_SRCR_SYNC(sc, HIFN_D_SRC_RSIZE,
		    BUS_DMASYNC_PREWRITE | BUS_DMASYNC_PREREAD);
	}
	*srcp = sc->sc_srci++;
	sc->sc_srck = sc->sc_srci;

	if (sc->sc_dsti == HIFN_D_DST_RSIZE) {
		sc->sc_dsti = 0;
		dma->dstr[HIFN_D_DST_RSIZE].l = htole32(HIFN_D_VALID |
		    HIFN_D_JUMP | HIFN_D_MASKDONEIRQ);
		HIFN_DSTR_SYNC(sc, HIFN_D_DST_RSIZE,
		    BUS_DMASYNC_PREWRITE | BUS_DMASYNC_PREREAD);
	}
	*dstp = sc->sc_dsti++;
	sc->sc_dstk = sc->sc_dsti;

	if (sc->sc_resi == HIFN_D_RES_RSIZE) {
		sc->sc_resi = 0;
		dma->resr[HIFN_D_RES_RSIZE].l = htole32(HIFN_D_VALID |
		    HIFN_D_JUMP | HIFN_D_MASKDONEIRQ);
		HIFN_RESR_SYNC(sc, HIFN_D_RES_RSIZE,
		    BUS_DMASYNC_PREWRITE | BUS_DMASYNC_PREREAD);
	}
	*resp = sc->sc_resi++;
	sc->sc_resk = sc->sc_resi;
}