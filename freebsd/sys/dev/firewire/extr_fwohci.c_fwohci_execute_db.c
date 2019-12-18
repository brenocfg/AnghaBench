#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fwohcidb_tr {size_t dbcnt; struct fwohcidb* db; } ;
struct TYPE_5__ {int /*<<< orphan*/  res; int /*<<< orphan*/  cmd; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;
struct fwohcidb {TYPE_2__ db; } ;
struct TYPE_7__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_3__ bus_dma_segment_t ;

/* Variables and functions */
 int EFBIG ; 
 int /*<<< orphan*/  FWOHCI_DMA_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ firewire_debug ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
fwohci_execute_db(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct fwohcidb_tr *db_tr;
	struct fwohcidb *db;
	bus_dma_segment_t *s;
	int i;

	db_tr = (struct fwohcidb_tr *)arg;
	db = &db_tr->db[db_tr->dbcnt];
	if (error) {
		if (firewire_debug || error != EFBIG)
			printf("fwohci_execute_db: error=%d\n", error);
		return;
	}
	for (i = 0; i < nseg; i++) {
		s = &segs[i];
		FWOHCI_DMA_WRITE(db->db.desc.addr, s->ds_addr);
		FWOHCI_DMA_WRITE(db->db.desc.cmd, s->ds_len);
 		FWOHCI_DMA_WRITE(db->db.desc.res, 0);
		db++;
		db_tr->dbcnt++;
	}
}