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
typedef  int /*<<< orphan*/  uint32_t ;
struct fwohcidb_tr {struct fwohcidb* db; } ;
struct TYPE_5__ {int /*<<< orphan*/  depend; int /*<<< orphan*/  res; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;
struct fwohcidb {TYPE_3__ db; } ;
struct fwohci_softc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  psize; } ;
struct fwohci_dbch {struct fwohcidb_tr* bottom; int /*<<< orphan*/  am; TYPE_1__ xferq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  FWOHCI_DMA_CLEAR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FWOHCI_DMA_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FWOHCI_DMA_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OHCI_CNTL_DMA_WAKE ; 
 int /*<<< orphan*/  OHCI_DMACTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwdma_sync_multiseg_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fwohci_arcv_free_buf(struct fwohci_softc *sc, struct fwohci_dbch *dbch,
    struct fwohcidb_tr *db_tr, uint32_t off, int wake)
{
	struct fwohcidb *db = &db_tr->db[0];

	FWOHCI_DMA_CLEAR(db->db.desc.depend, 0xf);
	FWOHCI_DMA_WRITE(db->db.desc.res, dbch->xferq.psize);
	FWOHCI_DMA_SET(dbch->bottom->db[0].db.desc.depend, 1);
	fwdma_sync_multiseg_all(dbch->am, BUS_DMASYNC_PREWRITE);
	dbch->bottom = db_tr;

	if (wake)
		OWRITE(sc, OHCI_DMACTL(off), OHCI_CNTL_DMA_WAKE);
}