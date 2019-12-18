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
struct fwohcidb_tr {int dbcnt; int /*<<< orphan*/  buf; struct fwohcidb* db; } ;
struct TYPE_3__ {int /*<<< orphan*/  res; int /*<<< orphan*/  cmd; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ desc; int /*<<< orphan*/ * immed; } ;
struct fwohcidb {TYPE_2__ db; } ;
struct fw_xferq {scalar_t__ buf; } ;
struct fwohci_dbch {struct fw_xferq xferq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FWOHCI_DMA_WRITE (int /*<<< orphan*/ ,int) ; 
 int OHCI_BRANCH_ALWAYS ; 
 int OHCI_KEY_ST2 ; 
 int OHCI_OUTPUT_LAST ; 
 int OHCI_OUTPUT_MORE ; 
 int OHCI_UPDATE ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int fwdma_bus_addr (scalar_t__,int) ; 
 int /*<<< orphan*/  fwdma_v_addr (scalar_t__,int) ; 

__attribute__((used)) static int
fwohci_add_tx_buf(struct fwohci_dbch *dbch, struct fwohcidb_tr *db_tr,
								int poffset)
{
	struct fwohcidb *db = db_tr->db;
	struct fw_xferq *it;
	int err = 0;

	it = &dbch->xferq;
	if (it->buf == 0) {
		err = EINVAL;
		return err;
	}
	db_tr->buf = fwdma_v_addr(it->buf, poffset);
	db_tr->dbcnt = 3;

	FWOHCI_DMA_WRITE(db[0].db.desc.cmd,
		OHCI_OUTPUT_MORE | OHCI_KEY_ST2 | 8);
	FWOHCI_DMA_WRITE(db[0].db.desc.addr, 0);
	bzero((void *)&db[1].db.immed[0], sizeof(db[1].db.immed));
	FWOHCI_DMA_WRITE(db[2].db.desc.addr,
	fwdma_bus_addr(it->buf, poffset) + sizeof(uint32_t));

	FWOHCI_DMA_WRITE(db[2].db.desc.cmd,
		OHCI_OUTPUT_LAST | OHCI_UPDATE | OHCI_BRANCH_ALWAYS);
#if 1
	FWOHCI_DMA_WRITE(db[0].db.desc.res, 0);
	FWOHCI_DMA_WRITE(db[2].db.desc.res, 0);
#endif
	return 0;
}