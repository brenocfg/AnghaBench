#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct fw_xferq {int flag; int bnchunk; int bnpacket; int psize; TYPE_1__* bulkxfer; int /*<<< orphan*/  stfree; int /*<<< orphan*/ * stproc; int /*<<< orphan*/  stdma; int /*<<< orphan*/  stvalid; scalar_t__ queued; int /*<<< orphan*/ * buf; } ;
struct fw_bulkxfer {int dummy; } ;
struct fw_bufspec {int nchunk; int psize; int npacket; } ;
struct firewire_comm {int dummy; } ;
struct TYPE_4__ {int poffset; int /*<<< orphan*/ * mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_WAITOK ; 
 int EBUSY ; 
 int ENOMEM ; 
 int FWXFERQ_EXTBUF ; 
 int FWXFERQ_MODEMASK ; 
 int FWXFERQ_RUNNING ; 
 int FWXFERQ_STREAM ; 
 int /*<<< orphan*/  M_FW ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fwdma_malloc_multiseg (struct firewire_comm*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roundup2 (int,int) ; 

__attribute__((used)) static int
fwdev_allocbuf(struct firewire_comm *fc, struct fw_xferq *q,
	struct fw_bufspec *b)
{
	int i;

	if (q->flag & (FWXFERQ_RUNNING | FWXFERQ_EXTBUF))
		return (EBUSY);

	q->bulkxfer = malloc(sizeof(struct fw_bulkxfer) * b->nchunk,
	    M_FW, M_WAITOK);

	b->psize = roundup2(b->psize, sizeof(uint32_t));
	q->buf = fwdma_malloc_multiseg(fc, sizeof(uint32_t),
	    b->psize, b->nchunk * b->npacket, BUS_DMA_WAITOK);

	if (q->buf == NULL) {
		free(q->bulkxfer, M_FW);
		q->bulkxfer = NULL;
		return (ENOMEM);
	}
	q->bnchunk = b->nchunk;
	q->bnpacket = b->npacket;
	q->psize = (b->psize + 3) & ~3;
	q->queued = 0;

	STAILQ_INIT(&q->stvalid);
	STAILQ_INIT(&q->stfree);
	STAILQ_INIT(&q->stdma);
	q->stproc = NULL;

	for (i = 0; i < q->bnchunk; i++) {
		q->bulkxfer[i].poffset = i * q->bnpacket;
		q->bulkxfer[i].mbuf = NULL;
		STAILQ_INSERT_TAIL(&q->stfree, &q->bulkxfer[i], link);
	}

	q->flag &= ~FWXFERQ_MODEMASK;
	q->flag |= FWXFERQ_STREAM;
	q->flag |= FWXFERQ_EXTBUF;

	return (0);
}