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
typedef  int uint32_t ;
struct fwohcidb_tr {int bus_addr; struct fwohcidb* db; } ;
struct TYPE_4__ {int cmd; int depend; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;
struct fwohcidb {TYPE_2__ db; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct fwohci_softc {TYPE_3__ fc; struct fwohci_dbch* it; } ;
struct fw_xferq {int flag; int bnpacket; int bnchunk; int /*<<< orphan*/  stfree; int /*<<< orphan*/  stdma; int /*<<< orphan*/  stvalid; int /*<<< orphan*/  buf; } ;
struct fwohci_dbch {int flags; int ndb; int ndesc; int /*<<< orphan*/  am; struct fw_xferq xferq; } ;
struct fw_bulkxfer {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  poffset; } ;
struct firewire_comm {int (* cyctimer ) (struct firewire_comm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int ENOMEM ; 
 int FWOHCI_DBCH_INIT ; 
 int /*<<< orphan*/  FWOHCI_DMA_SET (int,int) ; 
 int /*<<< orphan*/  FWOHCI_INTMASK ; 
 int /*<<< orphan*/  FW_GLOCK (struct firewire_comm*) ; 
 int /*<<< orphan*/  FW_GUNLOCK (struct firewire_comm*) ; 
 scalar_t__ ITX_CH ; 
 int OHCI_BRANCH_ALWAYS ; 
 int OHCI_CNTL_CYCMATCH_S ; 
 int OHCI_CNTL_DMA_ACTIVE ; 
 int OHCI_CNTL_DMA_RUN ; 
 int OHCI_CNTL_DMA_WAKE ; 
 int OHCI_INT_DMA_IT ; 
 int /*<<< orphan*/  OHCI_ITCMD (int) ; 
 int /*<<< orphan*/  OHCI_ITCTL (int) ; 
 int /*<<< orphan*/  OHCI_ITCTLCLR (int) ; 
 int /*<<< orphan*/  OHCI_IT_MASK ; 
 int /*<<< orphan*/  OHCI_IT_MASKCLR ; 
 int /*<<< orphan*/  OHCI_IT_STATCLR ; 
 int OREAD (struct fwohci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int) ; 
 struct fw_bulkxfer* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fw_bulkxfer*,int /*<<< orphan*/ ) ; 
 struct fw_bulkxfer* STAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dump_db (struct fwohci_softc*,scalar_t__) ; 
 int /*<<< orphan*/  dump_dma (struct fwohci_softc*,scalar_t__) ; 
 int firewire_debug ; 
 int /*<<< orphan*/  fw_bulkxfer ; 
 int /*<<< orphan*/  fwdma_sync_multiseg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwdma_sync_multiseg_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwohci_db_init (struct fwohci_softc*,struct fwohci_dbch*) ; 
 int fwohci_next_cycle (struct firewire_comm*,int) ; 
 int fwohci_tx_enable (struct fwohci_softc*,struct fwohci_dbch*) ; 
 int /*<<< orphan*/  fwohci_txbufdb (struct fwohci_softc*,int,struct fw_bulkxfer*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int splfw () ; 
 int /*<<< orphan*/  splx (int) ; 
 int stub1 (struct firewire_comm*) ; 

__attribute__((used)) static int
fwohci_itxbuf_enable(struct firewire_comm *fc, int dmach)
{
	struct fwohci_softc *sc = (struct fwohci_softc *)fc;
	int err = 0;
	unsigned short tag, ich;
	struct fwohci_dbch *dbch;
	int cycle_match, cycle_now, s, ldesc;
	uint32_t stat;
	struct fw_bulkxfer *first, *chunk, *prev;
	struct fw_xferq *it;

	dbch = &sc->it[dmach];
	it = &dbch->xferq;

	tag = (it->flag >> 6) & 3;
	ich = it->flag & 0x3f;
	if ((dbch->flags & FWOHCI_DBCH_INIT) == 0) {
		dbch->ndb = it->bnpacket * it->bnchunk;
		dbch->ndesc = 3;
		fwohci_db_init(sc, dbch);
		if ((dbch->flags & FWOHCI_DBCH_INIT) == 0)
			return ENOMEM;

		err = fwohci_tx_enable(sc, dbch);
	}
	if (err)
		return err;

	ldesc = dbch->ndesc - 1;
	s = splfw();
	FW_GLOCK(fc);
	prev = STAILQ_LAST(&it->stdma, fw_bulkxfer, link);
	while  ((chunk = STAILQ_FIRST(&it->stvalid)) != NULL) {
		struct fwohcidb *db;

		fwdma_sync_multiseg(it->buf, chunk->poffset, it->bnpacket,
					BUS_DMASYNC_PREWRITE);
		fwohci_txbufdb(sc, dmach, chunk);
		if (prev != NULL) {
			db = ((struct fwohcidb_tr *)(prev->end))->db;
#if 0 /* XXX necessary? */
			FWOHCI_DMA_SET(db[ldesc].db.desc.cmd,
						OHCI_BRANCH_ALWAYS);
#endif
#if 0 /* if bulkxfer->npacket changes */
			db[ldesc].db.desc.depend = db[0].db.desc.depend =
				((struct fwohcidb_tr *)
				(chunk->start))->bus_addr | dbch->ndesc;
#else
			FWOHCI_DMA_SET(db[0].db.desc.depend, dbch->ndesc);
			FWOHCI_DMA_SET(db[ldesc].db.desc.depend, dbch->ndesc);
#endif
		}
		STAILQ_REMOVE_HEAD(&it->stvalid, link);
		STAILQ_INSERT_TAIL(&it->stdma, chunk, link);
		prev = chunk;
	}
	FW_GUNLOCK(fc);
	fwdma_sync_multiseg_all(dbch->am, BUS_DMASYNC_PREWRITE);
	fwdma_sync_multiseg_all(dbch->am, BUS_DMASYNC_PREREAD);
	splx(s);
	stat = OREAD(sc, OHCI_ITCTL(dmach));
	if (firewire_debug && (stat & OHCI_CNTL_CYCMATCH_S))
		printf("stat 0x%x\n", stat);

	if (stat & (OHCI_CNTL_DMA_ACTIVE | OHCI_CNTL_CYCMATCH_S))
		return 0;

#if 0
	OWRITE(sc, OHCI_ITCTLCLR(dmach), OHCI_CNTL_DMA_RUN);
#endif
	OWRITE(sc, OHCI_IT_MASKCLR, 1 << dmach);
	OWRITE(sc, OHCI_IT_STATCLR, 1 << dmach);
	OWRITE(sc, OHCI_IT_MASK, 1 << dmach);
	OWRITE(sc, FWOHCI_INTMASK, OHCI_INT_DMA_IT);

	first = STAILQ_FIRST(&it->stdma);
	OWRITE(sc, OHCI_ITCMD(dmach),
		((struct fwohcidb_tr *)(first->start))->bus_addr | dbch->ndesc);
	if (firewire_debug > 1) {
		printf("fwohci_itxbuf_enable: kick 0x%08x\n", stat);
#if 1
		dump_dma(sc, ITX_CH + dmach);
#endif
	}
	if ((stat & OHCI_CNTL_DMA_RUN) == 0) {
#if 1
		/* Don't start until all chunks are buffered */
		if (STAILQ_FIRST(&it->stfree) != NULL)
			goto out;
#endif
#if 1
		/* Clear cycle match counter bits */
		OWRITE(sc, OHCI_ITCTLCLR(dmach), 0xffff0000);

		/* 2bit second + 13bit cycle */
		cycle_now = (fc->cyctimer(fc) >> 12) & 0x7fff;
		cycle_match = fwohci_next_cycle(fc, cycle_now);

		OWRITE(sc, OHCI_ITCTL(dmach),
				OHCI_CNTL_CYCMATCH_S | (cycle_match << 16)
				| OHCI_CNTL_DMA_RUN);
#else
		OWRITE(sc, OHCI_ITCTL(dmach), OHCI_CNTL_DMA_RUN);
#endif
		if (firewire_debug > 1) {
			printf("cycle_match: 0x%04x->0x%04x\n",
						cycle_now, cycle_match);
			dump_dma(sc, ITX_CH + dmach);
			dump_db(sc, ITX_CH + dmach);
		}
	} else if ((stat & OHCI_CNTL_CYCMATCH_S) == 0) {
		device_printf(sc->fc.dev,
			"IT DMA underrun (0x%08x)\n", stat);
		OWRITE(sc, OHCI_ITCTL(dmach), OHCI_CNTL_DMA_WAKE);
	}
out:
	return err;
}