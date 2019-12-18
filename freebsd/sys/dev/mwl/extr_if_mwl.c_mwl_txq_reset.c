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
struct TYPE_2__ {struct mwl_txbuf* dd_bufptr; } ;
struct mwl_txq {int nfree; int /*<<< orphan*/  free; TYPE_1__ dma; } ;
struct mwl_txbuf {int dummy; } ;
struct mwl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mwl_txbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bf_list ; 
 int mwl_txbuf ; 

__attribute__((used)) static void
mwl_txq_reset(struct mwl_softc *sc, struct mwl_txq *txq)
{
	struct mwl_txbuf *bf;
	int i;

	bf = txq->dma.dd_bufptr;
	STAILQ_INIT(&txq->free);
	for (i = 0; i < mwl_txbuf; i++, bf++)
		STAILQ_INSERT_TAIL(&txq->free, bf, bf_list);
	txq->nfree = i;
}