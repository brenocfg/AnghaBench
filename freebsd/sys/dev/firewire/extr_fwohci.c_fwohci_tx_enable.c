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
typedef  scalar_t__ uint32_t ;
struct fwohcidb_tr {int dbcnt; int bus_addr; struct fwohcidb* db; } ;
struct TYPE_7__ {int /*<<< orphan*/  depend; int /*<<< orphan*/  cmd; } ;
struct TYPE_8__ {TYPE_3__ desc; } ;
struct fwohcidb {TYPE_4__ db; } ;
struct TYPE_5__ {int nisodma; } ;
struct fwohci_softc {struct fwohci_dbch* it; TYPE_1__ fc; } ;
struct TYPE_6__ {int flag; int bnpacket; } ;
struct fwohci_dbch {int ndesc; int ndb; struct fwohcidb_tr* bottom; TYPE_2__ xferq; struct fwohcidb_tr* top; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FWOHCI_DMA_CLEAR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FWOHCI_DMA_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FWOHCI_DMA_WRITE (int /*<<< orphan*/ ,int) ; 
 int FWXFERQ_EXTBUF ; 
 int FWXFERQ_RUNNING ; 
 int /*<<< orphan*/  OHCI_INTERRUPT_ALWAYS ; 
 scalar_t__ OHCI_ITOFF (int) ; 
 struct fwohcidb_tr* STAILQ_NEXT (struct fwohcidb_tr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwohci_add_tx_buf (struct fwohci_dbch*,struct fwohcidb_tr*,int) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static int
fwohci_tx_enable(struct fwohci_softc *sc, struct fwohci_dbch *dbch)
{
	int err = 0;
	int idb, z, i, dmach = 0, ldesc;
	uint32_t off = 0;
	struct fwohcidb_tr *db_tr;
	struct fwohcidb *db;

	if (!(dbch->xferq.flag & FWXFERQ_EXTBUF)) {
		err = EINVAL;
		return err;
	}
	z = dbch->ndesc;
	for (dmach = 0; dmach < sc->fc.nisodma; dmach++) {
		if (&sc->it[dmach] == dbch) {
			off = OHCI_ITOFF(dmach);
			break;
		}
	}
	if (off == 0) {
		err = EINVAL;
		return err;
	}
	if (dbch->xferq.flag & FWXFERQ_RUNNING)
		return err;
	dbch->xferq.flag |= FWXFERQ_RUNNING;
	for (i = 0, dbch->bottom = dbch->top; i < (dbch->ndb - 1); i++) {
		dbch->bottom = STAILQ_NEXT(dbch->bottom, link);
	}
	db_tr = dbch->top;
	for (idb = 0; idb < dbch->ndb; idb++) {
		fwohci_add_tx_buf(dbch, db_tr, idb);
		if (STAILQ_NEXT(db_tr, link) == NULL) {
			break;
		}
		db = db_tr->db;
		ldesc = db_tr->dbcnt - 1;
		FWOHCI_DMA_WRITE(db[0].db.desc.depend,
				STAILQ_NEXT(db_tr, link)->bus_addr | z);
		db[ldesc].db.desc.depend = db[0].db.desc.depend;
		if (dbch->xferq.flag & FWXFERQ_EXTBUF) {
			if (((idb + 1) % dbch->xferq.bnpacket) == 0) {
				FWOHCI_DMA_SET(
					db[ldesc].db.desc.cmd,
					OHCI_INTERRUPT_ALWAYS);
				/* OHCI 1.1 and above */
				FWOHCI_DMA_SET(
					db[0].db.desc.cmd,
					OHCI_INTERRUPT_ALWAYS);
			}
		}
		db_tr = STAILQ_NEXT(db_tr, link);
	}
	FWOHCI_DMA_CLEAR(
		dbch->bottom->db[dbch->bottom->dbcnt - 1].db.desc.depend, 0xf);
	return err;
}