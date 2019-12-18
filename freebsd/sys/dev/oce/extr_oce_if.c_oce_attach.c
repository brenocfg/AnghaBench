#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_26__ {int rq_frag_size; int /*<<< orphan*/  bmbx_lock; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  bsmbx; int /*<<< orphan*/  ifp; void* vlan_detach; void* vlan_attach; int /*<<< orphan*/  timer; struct TYPE_26__* next; int /*<<< orphan*/  promisc; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  tx_ring_size; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOUT_MPSAFE ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_FIRST ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_CREATE (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOCK_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCE_DEFAULT_FLOW_CONTROL ; 
 int /*<<< orphan*/  OCE_DEFAULT_PROMISCUOUS ; 
 int /*<<< orphan*/  OCE_RX_RING_SIZE ; 
 int /*<<< orphan*/  OCE_TX_RING_SIZE ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oce_add_sysctls (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_add_vlan ; 
 int oce_attach_ifp (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_del_vlan ; 
 int /*<<< orphan*/  oce_dma_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oce_free_lro (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_get_config (TYPE_1__*) ; 
 int oce_hw_init (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_hw_intr_disable (TYPE_1__*) ; 
 int oce_hw_pci_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_hw_pci_free (TYPE_1__*) ; 
 int oce_hw_start (TYPE_1__*) ; 
 int oce_init_lro (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_intr_free (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_local_timer ; 
 int oce_queue_init_all (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_queue_release_all (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_read_env_variables (TYPE_1__*) ; 
 int oce_rq_buf_size ; 
 int oce_setup_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_stats_free (TYPE_1__*) ; 
 int oce_stats_init (TYPE_1__*) ; 
 int /*<<< orphan*/  setup_max_queues_want (TYPE_1__*) ; 
 TYPE_1__* softc_head ; 
 TYPE_1__* softc_tail ; 
 int /*<<< orphan*/  vlan_config ; 
 int /*<<< orphan*/  vlan_unconfig ; 

__attribute__((used)) static int
oce_attach(device_t dev)
{
	POCE_SOFTC sc;
	int rc = 0;

	sc = device_get_softc(dev);

	rc = oce_hw_pci_alloc(sc);
	if (rc)
		return rc;

	sc->tx_ring_size = OCE_TX_RING_SIZE;
	sc->rx_ring_size = OCE_RX_RING_SIZE;
	/* receive fragment size should be multiple of 2K */
	sc->rq_frag_size = ((oce_rq_buf_size / 2048) * 2048);
	sc->flow_control = OCE_DEFAULT_FLOW_CONTROL;
	sc->promisc	 = OCE_DEFAULT_PROMISCUOUS;

	LOCK_CREATE(&sc->bmbx_lock, "Mailbox_lock");
	LOCK_CREATE(&sc->dev_lock,  "Device_lock");

	/* initialise the hardware */
	rc = oce_hw_init(sc);
	if (rc)
		goto pci_res_free;

	oce_read_env_variables(sc);

	oce_get_config(sc);

	setup_max_queues_want(sc);	

	rc = oce_setup_intr(sc);
	if (rc)
		goto mbox_free;

	rc = oce_queue_init_all(sc);
	if (rc)
		goto intr_free;

	rc = oce_attach_ifp(sc);
	if (rc)
		goto queues_free;

#if defined(INET6) || defined(INET)
	rc = oce_init_lro(sc);
	if (rc)
		goto ifp_free;
#endif

	rc = oce_hw_start(sc);
	if (rc)
		goto lro_free;

	sc->vlan_attach = EVENTHANDLER_REGISTER(vlan_config,
				oce_add_vlan, sc, EVENTHANDLER_PRI_FIRST);
	sc->vlan_detach = EVENTHANDLER_REGISTER(vlan_unconfig,
				oce_del_vlan, sc, EVENTHANDLER_PRI_FIRST);

	rc = oce_stats_init(sc);
	if (rc)
		goto vlan_free;

	oce_add_sysctls(sc);

	callout_init(&sc->timer, CALLOUT_MPSAFE);
	rc = callout_reset(&sc->timer, 2 * hz, oce_local_timer, sc);
	if (rc)
		goto stats_free;

	sc->next =NULL;
	if (softc_tail != NULL) {
	  softc_tail->next = sc;
	} else {
	  softc_head = sc;
	}
	softc_tail = sc;

	return 0;

stats_free:
	callout_drain(&sc->timer);
	oce_stats_free(sc);
vlan_free:
	if (sc->vlan_attach)
		EVENTHANDLER_DEREGISTER(vlan_config, sc->vlan_attach);
	if (sc->vlan_detach)
		EVENTHANDLER_DEREGISTER(vlan_unconfig, sc->vlan_detach);
	oce_hw_intr_disable(sc);
lro_free:
#if defined(INET6) || defined(INET)
	oce_free_lro(sc);
ifp_free:
#endif
	ether_ifdetach(sc->ifp);
	if_free(sc->ifp);
queues_free:
	oce_queue_release_all(sc);
intr_free:
	oce_intr_free(sc);
mbox_free:
	oce_dma_free(sc, &sc->bsmbx);
pci_res_free:
	oce_hw_pci_free(sc);
	LOCK_DESTROY(&sc->dev_lock);
	LOCK_DESTROY(&sc->bmbx_lock);
	return rc;

}