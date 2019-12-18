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
struct fwohcidb_tr {struct fwohcidb* db; } ;
struct TYPE_5__ {int /*<<< orphan*/  res; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;
struct fwohcidb {TYPE_3__ db; } ;
struct firewire_comm {int /*<<< orphan*/  dev; struct fw_xferq** it; } ;
struct fwohci_softc {TYPE_1__* it; struct firewire_comm fc; } ;
struct fw_xferq {int /*<<< orphan*/  stfree; int /*<<< orphan*/  stdma; } ;
struct fw_bulkxfer {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_4__ {int ndesc; int /*<<< orphan*/  am; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
#define  FWOHCIEV_ACKCOMPL 128 
 int FWOHCIEV_MASK ; 
 int FWOHCI_DMA_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_GLOCK (struct firewire_comm*) ; 
 int /*<<< orphan*/  FW_GUNLOCK (struct firewire_comm*) ; 
 scalar_t__ ITX_CH ; 
 int OHCI_COUNT_MASK ; 
 int OHCI_STATUS_SHIFT ; 
 struct fw_bulkxfer* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fw_bulkxfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dump_db (struct fwohci_softc*,scalar_t__) ; 
 scalar_t__ firewire_debug ; 
 int /*<<< orphan*/  fwdma_sync_multiseg_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fwohcicode ; 
 int /*<<< orphan*/  link ; 
 int splfw () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  wakeup (struct fw_xferq*) ; 

__attribute__((used)) static void
fwohci_tbuf_update(struct fwohci_softc *sc, int dmach)
{
	struct firewire_comm *fc = &sc->fc;
	struct fwohcidb *db;
	struct fw_bulkxfer *chunk;
	struct fw_xferq *it;
	uint32_t stat, count;
	int s, w=0, ldesc;

	it = fc->it[dmach];
	ldesc = sc->it[dmach].ndesc - 1;
	s = splfw(); /* unnecessary ? */
	FW_GLOCK(fc);
	fwdma_sync_multiseg_all(sc->it[dmach].am, BUS_DMASYNC_POSTREAD);
	if (firewire_debug)
		dump_db(sc, ITX_CH + dmach);
	while ((chunk = STAILQ_FIRST(&it->stdma)) != NULL) {
		db = ((struct fwohcidb_tr *)(chunk->end))->db;
		stat = FWOHCI_DMA_READ(db[ldesc].db.desc.res)
				>> OHCI_STATUS_SHIFT;
		db = ((struct fwohcidb_tr *)(chunk->start))->db;
		/* timestamp */
		count = FWOHCI_DMA_READ(db[ldesc].db.desc.res)
				& OHCI_COUNT_MASK;
		if (stat == 0)
			break;
		STAILQ_REMOVE_HEAD(&it->stdma, link);
		switch (stat & FWOHCIEV_MASK) {
		case FWOHCIEV_ACKCOMPL:
#if 0
			device_printf(fc->dev, "0x%08x\n", count);
#endif
			break;
		default:
			device_printf(fc->dev,
				"Isochronous transmit err %02x(%s)\n",
					stat, fwohcicode[stat & 0x1f]);
		}
		STAILQ_INSERT_TAIL(&it->stfree, chunk, link);
		w++;
	}
	FW_GUNLOCK(fc);
	splx(s);
	if (w)
		wakeup(it);
}