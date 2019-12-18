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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct smt_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  smac; int /*<<< orphan*/  state; int /*<<< orphan*/  pfvf; int /*<<< orphan*/  iqid; int /*<<< orphan*/ * wrq; int /*<<< orphan*/  refcnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  abs_id; } ;
struct TYPE_4__ {TYPE_1__ fwq; int /*<<< orphan*/ * ctrlq; } ;
struct adapter {TYPE_2__ sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  SMT_STATE_SWITCHING ; 
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int t4_write_sme (struct smt_entry*) ; 

int
t4_smt_set_switching(struct adapter *sc, struct smt_entry *e, uint16_t pfvf,
								uint8_t *smac)
{
	int rc = 0;

	if (atomic_load_acq_int(&e->refcnt) == 1) {
		/* Setup the entry for the first time */
		mtx_lock(&e->lock);
		e->wrq = &sc->sge.ctrlq[0];
		e->iqid = sc->sge.fwq.abs_id;
		e->pfvf =  pfvf;
		e->state = SMT_STATE_SWITCHING;
		memcpy(e->smac, smac, ETHER_ADDR_LEN);
		rc = t4_write_sme(e);
		mtx_unlock(&e->lock);
	}

	return (rc);
}