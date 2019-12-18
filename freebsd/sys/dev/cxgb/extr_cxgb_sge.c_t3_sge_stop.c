#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sge_qset {TYPE_4__* txq; } ;
struct TYPE_10__ {struct sge_qset* qs; } ;
struct TYPE_8__ {int nports; } ;
struct TYPE_12__ {int /*<<< orphan*/ * tq; TYPE_3__ sge; TYPE_2__* port; TYPE_1__ params; } ;
typedef  TYPE_5__ adapter_t ;
struct TYPE_11__ {int /*<<< orphan*/  qresume_task; } ;
struct TYPE_9__ {scalar_t__ nqsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_CONTROL ; 
 int /*<<< orphan*/  F_GLOBALENABLE ; 
 size_t TXQ_CTRL ; 
 size_t TXQ_OFLD ; 
 int /*<<< orphan*/  t3_set_reg_field (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
t3_sge_stop(adapter_t *sc)
{
	int i, nqsets;
	
	t3_set_reg_field(sc, A_SG_CONTROL, F_GLOBALENABLE, 0);

	if (sc->tq == NULL)
		return;
	
	for (nqsets = i = 0; i < (sc)->params.nports; i++) 
		nqsets += sc->port[i].nqsets;
#ifdef notyet
	/*
	 * 
	 * XXX
	 */
	for (i = 0; i < nqsets; ++i) {
		struct sge_qset *qs = &sc->sge.qs[i];
		
		taskqueue_drain(sc->tq, &qs->txq[TXQ_OFLD].qresume_task);
		taskqueue_drain(sc->tq, &qs->txq[TXQ_CTRL].qresume_task);
	}
#endif
}