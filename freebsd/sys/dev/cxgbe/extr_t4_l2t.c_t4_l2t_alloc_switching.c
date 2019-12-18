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
struct l2t_entry {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lport; int /*<<< orphan*/  vlan; int /*<<< orphan*/  lock; int /*<<< orphan*/  dmac; int /*<<< orphan*/  state; int /*<<< orphan*/  iqid; int /*<<< orphan*/ * wrq; } ;
struct l2t_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  nfree; } ;
struct TYPE_3__ {int /*<<< orphan*/  abs_id; } ;
struct TYPE_4__ {TYPE_1__ fwq; int /*<<< orphan*/ * ctrlq; } ;
struct adapter {TYPE_2__ sge; struct l2t_data* l2t; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  L2T_STATE_SWITCHING ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 struct l2t_entry* find_or_alloc_l2e (struct l2t_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int t4_write_l2e (struct l2t_entry*,int /*<<< orphan*/ ) ; 

struct l2t_entry *
t4_l2t_alloc_switching(struct adapter *sc, uint16_t vlan, uint8_t port,
    uint8_t *eth_addr)
{
	struct l2t_data *d = sc->l2t;
	struct l2t_entry *e;
	int rc;

	rw_wlock(&d->lock);
	e = find_or_alloc_l2e(d, vlan, port, eth_addr);
	if (e) {
		if (atomic_load_acq_int(&e->refcnt) == 0) {
			mtx_lock(&e->lock);    /* avoid race with t4_l2t_free */
			e->wrq = &sc->sge.ctrlq[0];
			e->iqid = sc->sge.fwq.abs_id;
			e->state = L2T_STATE_SWITCHING;
			e->vlan = vlan;
			e->lport = port;
			memcpy(e->dmac, eth_addr, ETHER_ADDR_LEN);
			atomic_store_rel_int(&e->refcnt, 1);
			atomic_subtract_int(&d->nfree, 1);
			rc = t4_write_l2e(e, 0);
			mtx_unlock(&e->lock);
			if (rc != 0)
				e = NULL;
		} else {
			MPASS(e->vlan == vlan);
			MPASS(e->lport == port);
			atomic_add_int(&e->refcnt, 1);
		}
	}
	rw_wunlock(&d->lock);
	return (e);
}