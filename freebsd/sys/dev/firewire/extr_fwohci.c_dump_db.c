#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct fwohcidb_tr {int bus_addr; struct fwohcidb* db; } ;
struct fwohcidb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct fwohci_dbch {int ndb; int ndesc; struct fwohcidb_tr* top; } ;
struct fwohci_softc {TYPE_1__ fc; struct fwohci_dbch* ir; struct fwohci_dbch* it; struct fwohci_dbch arrs; struct fwohci_dbch arrq; struct fwohci_dbch atrs; struct fwohci_dbch atrq; } ;

/* Variables and functions */
 int IRX_CH ; 
 int /*<<< orphan*/  ITX_CH ; 
 int OHCI_ARQOFF ; 
 int OHCI_ARSOFF ; 
 int OHCI_ATQOFF ; 
 int OHCI_ATSOFF ; 
 int OHCI_IRCTL (int /*<<< orphan*/ ) ; 
 int OHCI_ITCTL (int /*<<< orphan*/ ) ; 
 int OREAD (struct fwohci_softc*,int) ; 
 struct fwohcidb_tr* STAILQ_NEXT (struct fwohcidb_tr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  print_db (struct fwohcidb_tr*,struct fwohcidb*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

void
dump_db(struct fwohci_softc *sc, uint32_t ch)
{
	struct fwohci_dbch *dbch;
	struct fwohcidb_tr *cp = NULL, *pp, *np = NULL;
	struct fwohcidb *curr = NULL, *prev, *next = NULL;
	int idb, jdb;
	uint32_t cmd, off;

	if (ch == 0) {
		off = OHCI_ATQOFF;
		dbch = &sc->atrq;
	} else if (ch == 1) {
		off = OHCI_ATSOFF;
		dbch = &sc->atrs;
	} else if (ch == 2) {
		off = OHCI_ARQOFF;
		dbch = &sc->arrq;
	} else if (ch == 3) {
		off = OHCI_ARSOFF;
		dbch = &sc->arrs;
	} else if (ch < IRX_CH) {
		off = OHCI_ITCTL(ch - ITX_CH);
		dbch = &sc->it[ch - ITX_CH];
	} else {
		off = OHCI_IRCTL(ch - IRX_CH);
		dbch = &sc->ir[ch - IRX_CH];
	}
	cmd = OREAD(sc, off + 0xc);

	if (dbch->ndb == 0) {
		device_printf(sc->fc.dev, "No DB is attached ch=%d\n", ch);
		return;
	}
	pp = dbch->top;
	prev = pp->db;
	for (idb = 0; idb < dbch->ndb; idb++) {
		cp = STAILQ_NEXT(pp, link);
		if (cp == NULL) {
			curr = NULL;
			goto outdb;
		}
		np = STAILQ_NEXT(cp, link);
		for (jdb = 0; jdb < dbch->ndesc; jdb++) {
			if ((cmd  & 0xfffffff0) == cp->bus_addr) {
				curr = cp->db;
				if (np != NULL) {
					next = np->db;
				} else {
					next = NULL;
				}
				goto outdb;
			}
		}
		pp = STAILQ_NEXT(pp, link);
		if (pp == NULL) {
			curr = NULL;
			goto outdb;
		}
		prev = pp->db;
	}
outdb:
	if (curr != NULL) {
#if 0
		printf("Prev DB %d\n", ch);
		print_db(pp, prev, ch, dbch->ndesc);
#endif
		printf("Current DB %d\n", ch);
		print_db(cp, curr, ch, dbch->ndesc);
#if 0
		printf("Next DB %d\n", ch);
		print_db(np, next, ch, dbch->ndesc);
#endif
	} else {
		printf("dbdump err ch = %d cmd = 0x%08x\n", ch, cmd);
	}
	return;
}