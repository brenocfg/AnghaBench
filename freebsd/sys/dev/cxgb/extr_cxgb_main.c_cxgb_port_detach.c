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
struct sge_txq {int /*<<< orphan*/  txq_timer; int /*<<< orphan*/  txq_watchdog; } ;
struct sge_qset {struct sge_txq* txq; } ;
struct port_info {int first_qset; int nqsets; int /*<<< orphan*/ * ifp; int /*<<< orphan*/ * port_cdev; struct adapter* adapter; } ;
struct TYPE_2__ {struct sge_qset* qs; } ;
struct adapter {int /*<<< orphan*/  flags; TYPE_1__ sge; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_LOCK (struct adapter*) ; 
 int /*<<< orphan*/  ADAPTER_UNLOCK (struct adapter*) ; 
 int /*<<< orphan*/  CLR_BUSY (struct adapter*) ; 
 scalar_t__ IS_BUSY (struct adapter*) ; 
 int /*<<< orphan*/  PORT_LOCK_DEINIT (struct port_info*) ; 
 int /*<<< orphan*/  SET_BUSY (struct adapter*) ; 
 int /*<<< orphan*/  SET_DOOMED (struct port_info*) ; 
 size_t TXQ_ETH ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgb_uninit_synchronized (struct port_info*) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 struct port_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cxgb_port_detach(device_t dev)
{
	struct port_info *p;
	struct adapter *sc;
	int i;

	p = device_get_softc(dev);
	sc = p->adapter;

	/* Tell cxgb_ioctl and if_init that the port is going away */
	ADAPTER_LOCK(sc);
	SET_DOOMED(p);
	wakeup(&sc->flags);
	while (IS_BUSY(sc))
		mtx_sleep(&sc->flags, &sc->lock, 0, "cxgbdtch", 0);
	SET_BUSY(sc);
	ADAPTER_UNLOCK(sc);

	if (p->port_cdev != NULL)
		destroy_dev(p->port_cdev);

	cxgb_uninit_synchronized(p);
	ether_ifdetach(p->ifp);

	for (i = p->first_qset; i < p->first_qset + p->nqsets; i++) {
		struct sge_qset *qs = &sc->sge.qs[i];
		struct sge_txq *txq = &qs->txq[TXQ_ETH];

		callout_drain(&txq->txq_watchdog);
		callout_drain(&txq->txq_timer);
	}

	PORT_LOCK_DEINIT(p);
	if_free(p->ifp);
	p->ifp = NULL;

	ADAPTER_LOCK(sc);
	CLR_BUSY(sc);
	wakeup_one(&sc->flags);
	ADAPTER_UNLOCK(sc);
	return (0);
}