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
struct port_info {struct port_info* vi; int /*<<< orphan*/  pi_lock; scalar_t__ dev; int /*<<< orphan*/  viid; } ;
struct memwin {int /*<<< orphan*/  mw_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  atid_lock; int /*<<< orphan*/  ftid_cv; int /*<<< orphan*/  ftid_lock; struct port_info* tid_tab; struct port_info* hpftid_tab; struct port_info* ftid_tab; } ;
struct TYPE_5__ {struct port_info* tls_rx_ports; } ;
struct TYPE_4__ {struct port_info* eqmap; struct port_info* iqmap; struct port_info* ctrlq; struct port_info* txq; struct port_info* rxq; struct port_info* nm_txq; struct port_info* nm_rxq; struct port_info* ofld_rxq; struct port_info* ofld_txq; } ;
struct adapter {int flags; int intr_count; scalar_t__ intr_type; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  sfl_lock; struct memwin* memwin; int /*<<< orphan*/ * policy; int /*<<< orphan*/  policy_lock; int /*<<< orphan*/  ifp_lock; TYPE_3__ tids; int /*<<< orphan*/  sfl_callout; TYPE_2__ tt; TYPE_1__ sge; struct port_info* irq; scalar_t__ key_map; scalar_t__ smt; scalar_t__ l2t; scalar_t__ msix_res; int /*<<< orphan*/  msix_rid; scalar_t__ udbs_res; int /*<<< orphan*/  udbs_rid; scalar_t__ regs_res; int /*<<< orphan*/  regs_rid; int /*<<< orphan*/  mbox; int /*<<< orphan*/  pf; struct port_info** port; int /*<<< orphan*/ * cdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CHK_MBOX_ACCESS ; 
 int FULL_INIT_DONE ; 
 int FW_OK ; 
 scalar_t__ INTR_MSI ; 
 scalar_t__ INTR_MSIX ; 
 int IS_VF ; 
 int MAX_NPORTS ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int NUM_MEMWIN ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  adapter ; 
 int /*<<< orphan*/  adapter_full_uninit (struct adapter*) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bzero (struct adapter*,int) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct adapter* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (struct port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_hftid_hash (TYPE_3__*) ; 
 int /*<<< orphan*/  free_offload_policy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ rw_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_destroy_clip_table (struct adapter*) ; 
 int /*<<< orphan*/  t4_destroy_dma_tag (struct adapter*) ; 
 int /*<<< orphan*/  t4_free_atid_table (struct adapter*) ; 
 int /*<<< orphan*/  t4_free_etid_table (struct adapter*) ; 
 int /*<<< orphan*/  t4_free_irq (struct adapter*,struct port_info*) ; 
 int /*<<< orphan*/  t4_free_l2t (scalar_t__) ; 
 int /*<<< orphan*/  t4_free_smt (scalar_t__) ; 
 int /*<<< orphan*/  t4_free_tx_sched (struct adapter*) ; 
 int /*<<< orphan*/  t4_free_vi (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_fw_bye (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_intr_disable (struct adapter*) ; 
 int /*<<< orphan*/  t4_list ; 
 int /*<<< orphan*/  t4_list_lock ; 
 int /*<<< orphan*/  vmem_destroy (scalar_t__) ; 

int
t4_detach_common(device_t dev)
{
	struct adapter *sc;
	struct port_info *pi;
	int i, rc;

	sc = device_get_softc(dev);

	if (sc->cdev) {
		destroy_dev(sc->cdev);
		sc->cdev = NULL;
	}

	sx_xlock(&t4_list_lock);
	SLIST_REMOVE(&t4_list, sc, adapter, link);
	sx_xunlock(&t4_list_lock);

	sc->flags &= ~CHK_MBOX_ACCESS;
	if (sc->flags & FULL_INIT_DONE) {
		if (!(sc->flags & IS_VF))
			t4_intr_disable(sc);
	}

	if (device_is_attached(dev)) {
		rc = bus_generic_detach(dev);
		if (rc) {
			device_printf(dev,
			    "failed to detach child devices: %d\n", rc);
			return (rc);
		}
	}

	for (i = 0; i < sc->intr_count; i++)
		t4_free_irq(sc, &sc->irq[i]);

	if ((sc->flags & (IS_VF | FW_OK)) == FW_OK)
		t4_free_tx_sched(sc);

	for (i = 0; i < MAX_NPORTS; i++) {
		pi = sc->port[i];
		if (pi) {
			t4_free_vi(sc, sc->mbox, sc->pf, 0, pi->vi[0].viid);
			if (pi->dev)
				device_delete_child(dev, pi->dev);

			mtx_destroy(&pi->pi_lock);
			free(pi->vi, M_CXGBE);
			free(pi, M_CXGBE);
		}
	}

	device_delete_children(dev);

	if (sc->flags & FULL_INIT_DONE)
		adapter_full_uninit(sc);

	if ((sc->flags & (IS_VF | FW_OK)) == FW_OK)
		t4_fw_bye(sc, sc->mbox);

	if (sc->intr_type == INTR_MSI || sc->intr_type == INTR_MSIX)
		pci_release_msi(dev);

	if (sc->regs_res)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->regs_rid,
		    sc->regs_res);

	if (sc->udbs_res)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->udbs_rid,
		    sc->udbs_res);

	if (sc->msix_res)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->msix_rid,
		    sc->msix_res);

	if (sc->l2t)
		t4_free_l2t(sc->l2t);
	if (sc->smt)
		t4_free_smt(sc->smt);
	t4_free_atid_table(sc);
#ifdef RATELIMIT
	t4_free_etid_table(sc);
#endif
	if (sc->key_map)
		vmem_destroy(sc->key_map);
#ifdef INET6
	t4_destroy_clip_table(sc);
#endif

#if defined(TCP_OFFLOAD) || defined(RATELIMIT)
	free(sc->sge.ofld_txq, M_CXGBE);
#endif
#ifdef TCP_OFFLOAD
	free(sc->sge.ofld_rxq, M_CXGBE);
#endif
#ifdef DEV_NETMAP
	free(sc->sge.nm_rxq, M_CXGBE);
	free(sc->sge.nm_txq, M_CXGBE);
#endif
	free(sc->irq, M_CXGBE);
	free(sc->sge.rxq, M_CXGBE);
	free(sc->sge.txq, M_CXGBE);
	free(sc->sge.ctrlq, M_CXGBE);
	free(sc->sge.iqmap, M_CXGBE);
	free(sc->sge.eqmap, M_CXGBE);
	free(sc->tids.ftid_tab, M_CXGBE);
	free(sc->tids.hpftid_tab, M_CXGBE);
	free_hftid_hash(&sc->tids);
	free(sc->tids.tid_tab, M_CXGBE);
	free(sc->tt.tls_rx_ports, M_CXGBE);
	t4_destroy_dma_tag(sc);

	callout_drain(&sc->sfl_callout);
	if (mtx_initialized(&sc->tids.ftid_lock)) {
		mtx_destroy(&sc->tids.ftid_lock);
		cv_destroy(&sc->tids.ftid_cv);
	}
	if (mtx_initialized(&sc->tids.atid_lock))
		mtx_destroy(&sc->tids.atid_lock);
	if (mtx_initialized(&sc->ifp_lock))
		mtx_destroy(&sc->ifp_lock);

	if (rw_initialized(&sc->policy_lock)) {
		rw_destroy(&sc->policy_lock);
#ifdef TCP_OFFLOAD
		if (sc->policy != NULL)
			free_offload_policy(sc->policy);
#endif
	}

	for (i = 0; i < NUM_MEMWIN; i++) {
		struct memwin *mw = &sc->memwin[i];

		if (rw_initialized(&mw->mw_lock))
			rw_destroy(&mw->mw_lock);
	}

	mtx_destroy(&sc->sfl_lock);
	mtx_destroy(&sc->reg_lock);
	mtx_destroy(&sc->sc_lock);

	bzero(sc, sizeof(*sc));

	return (0);
}