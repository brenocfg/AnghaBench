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
typedef  int uint16_t ;
struct blockif_req {int br_iovcnt; int br_resid; TYPE_1__* br_iov; } ;
struct ahci_prdt_entry {int dbc; scalar_t__ dba; } ;
struct ahci_port {int /*<<< orphan*/  bctx; int /*<<< orphan*/  pr_sc; } ;
struct ahci_ioreq {int done; int len; int more; struct blockif_req io_req; } ;
struct TYPE_2__ {int iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int BLOCKIF_IOV_MAX ; 
 int DBCMASK ; 
 int /*<<< orphan*/  ahci_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int blockif_sectsz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paddr_guest2host (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
ahci_build_iov(struct ahci_port *p, struct ahci_ioreq *aior,
    struct ahci_prdt_entry *prdt, uint16_t prdtl)
{
	struct blockif_req *breq = &aior->io_req;
	int i, j, skip, todo, left, extra;
	uint32_t dbcsz;

	/* Copy part of PRDT between 'done' and 'len' bytes into the iov. */
	skip = aior->done;
	left = aior->len - aior->done;
	todo = 0;
	for (i = 0, j = 0; i < prdtl && j < BLOCKIF_IOV_MAX && left > 0;
	    i++, prdt++) {
		dbcsz = (prdt->dbc & DBCMASK) + 1;
		/* Skip already done part of the PRDT */
		if (dbcsz <= skip) {
			skip -= dbcsz;
			continue;
		}
		dbcsz -= skip;
		if (dbcsz > left)
			dbcsz = left;
		breq->br_iov[j].iov_base = paddr_guest2host(ahci_ctx(p->pr_sc),
		    prdt->dba + skip, dbcsz);
		breq->br_iov[j].iov_len = dbcsz;
		todo += dbcsz;
		left -= dbcsz;
		skip = 0;
		j++;
	}

	/* If we got limited by IOV length, round I/O down to sector size. */
	if (j == BLOCKIF_IOV_MAX) {
		extra = todo % blockif_sectsz(p->bctx);
		todo -= extra;
		assert(todo > 0);
		while (extra > 0) {
			if (breq->br_iov[j - 1].iov_len > extra) {
				breq->br_iov[j - 1].iov_len -= extra;
				break;
			}
			extra -= breq->br_iov[j - 1].iov_len;
			j--;
		}
	}

	breq->br_iovcnt = j;
	breq->br_resid = todo;
	aior->done += todo;
	aior->more = (aior->done < aior->len && i < prdtl);
}