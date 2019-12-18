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
typedef  int /*<<< orphan*/  uint32_t ;
struct fwohcidb_tr {int dbcnt; int /*<<< orphan*/ * buf; int /*<<< orphan*/  dma_map; struct fwohcidb* db; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  res; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;
struct fwohcidb {TYPE_2__ db; } ;
struct fw_xferq {int flag; int psize; int /*<<< orphan*/ * buf; } ;
struct fwohci_dbch {int /*<<< orphan*/  dmat; struct fw_xferq xferq; } ;
struct fwdma_alloc {int bus_addr; } ;
typedef  int bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FWOHCI_DMA_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FWOHCI_DMA_WRITE (int /*<<< orphan*/ ,int) ; 
 int FWXFERQ_EXTBUF ; 
 int FWXFERQ_STREAM ; 
 int /*<<< orphan*/  OHCI_BRANCH_ALWAYS ; 
 int /*<<< orphan*/  OHCI_INPUT_LAST ; 
 int OHCI_INPUT_MORE ; 
 int /*<<< orphan*/  OHCI_UPDATE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fwdma_bus_addr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fwdma_malloc_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fwdma_v_addr (int /*<<< orphan*/ *,int) ; 

int
fwohci_add_rx_buf(struct fwohci_dbch *dbch, struct fwohcidb_tr *db_tr,
		int poffset, struct fwdma_alloc *dummy_dma)
{
	struct fwohcidb *db = db_tr->db;
	struct fw_xferq *ir;
	int i, ldesc;
	bus_addr_t dbuf[2];
	int dsiz[2];

	ir = &dbch->xferq;
	if (ir->buf == NULL && (dbch->xferq.flag & FWXFERQ_EXTBUF) == 0) {
		if (db_tr->buf == NULL) {
			db_tr->buf = fwdma_malloc_size(dbch->dmat,
			    &db_tr->dma_map, ir->psize, &dbuf[0],
			    BUS_DMA_NOWAIT);
			if (db_tr->buf == NULL)
				return (ENOMEM);
		}
		db_tr->dbcnt = 1;
		dsiz[0] = ir->psize;
		bus_dmamap_sync(dbch->dmat, db_tr->dma_map,
			BUS_DMASYNC_PREREAD);
	} else {
		db_tr->dbcnt = 0;
		if (dummy_dma != NULL) {
			dsiz[db_tr->dbcnt] = sizeof(uint32_t);
			dbuf[db_tr->dbcnt++] = dummy_dma->bus_addr;
		}
		dsiz[db_tr->dbcnt] = ir->psize;
		if (ir->buf != NULL) {
			db_tr->buf = fwdma_v_addr(ir->buf, poffset);
			dbuf[db_tr->dbcnt] = fwdma_bus_addr(ir->buf, poffset);
		}
		db_tr->dbcnt++;
	}
	for (i = 0; i < db_tr->dbcnt; i++) {
		FWOHCI_DMA_WRITE(db[i].db.desc.addr, dbuf[i]);
		FWOHCI_DMA_WRITE(db[i].db.desc.cmd, OHCI_INPUT_MORE | dsiz[i]);
		if (ir->flag & FWXFERQ_STREAM) {
			FWOHCI_DMA_SET(db[i].db.desc.cmd, OHCI_UPDATE);
		}
		FWOHCI_DMA_WRITE(db[i].db.desc.res, dsiz[i]);
	}
	ldesc = db_tr->dbcnt - 1;
	if (ir->flag & FWXFERQ_STREAM) {
		FWOHCI_DMA_SET(db[ldesc].db.desc.cmd, OHCI_INPUT_LAST);
	}
	FWOHCI_DMA_SET(db[ldesc].db.desc.cmd, OHCI_BRANCH_ALWAYS);
	return 0;
}