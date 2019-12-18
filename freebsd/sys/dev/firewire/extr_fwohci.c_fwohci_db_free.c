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
struct fwohcidb_tr {int /*<<< orphan*/ * dma_map; int /*<<< orphan*/ * buf; } ;
struct TYPE_2__ {int flag; int /*<<< orphan*/  psize; } ;
struct fwohci_dbch {int flags; int ndb; int /*<<< orphan*/  db_trq; int /*<<< orphan*/  am; int /*<<< orphan*/  dmat; TYPE_1__ xferq; } ;

/* Variables and functions */
 int FWOHCI_DBCH_INIT ; 
 int FWXFERQ_EXTBUF ; 
 int /*<<< orphan*/  M_FW ; 
 struct fwohcidb_tr* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct fwohcidb_tr* STAILQ_NEXT (struct fwohcidb_tr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct fwohcidb_tr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwdma_free_multiseg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwdma_free_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
fwohci_db_free(struct fwohci_dbch *dbch)
{
	struct fwohcidb_tr *db_tr;
	int idb;

	if ((dbch->flags & FWOHCI_DBCH_INIT) == 0)
		return;

	for (db_tr = STAILQ_FIRST(&dbch->db_trq), idb = 0; idb < dbch->ndb;
	    db_tr = STAILQ_NEXT(db_tr, link), idb++) {
		if ((dbch->xferq.flag & FWXFERQ_EXTBUF) == 0 &&
		    db_tr->buf != NULL) {
			fwdma_free_size(dbch->dmat, db_tr->dma_map,
					db_tr->buf, dbch->xferq.psize);
			db_tr->buf = NULL;
		} else if (db_tr->dma_map != NULL)
			bus_dmamap_destroy(dbch->dmat, db_tr->dma_map);
	}
	dbch->ndb = 0;
	db_tr = STAILQ_FIRST(&dbch->db_trq);
	fwdma_free_multiseg(dbch->am);
	free(db_tr, M_FW);
	STAILQ_INIT(&dbch->db_trq);
	dbch->flags &= ~FWOHCI_DBCH_INIT;
}