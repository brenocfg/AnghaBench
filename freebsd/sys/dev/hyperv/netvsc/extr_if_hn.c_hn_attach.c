#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct taskqueue {int dummy; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_11__ {int ifq_drv_maxlen; } ;
struct ifnet {scalar_t__ if_hw_tsomax; scalar_t__ if_hw_tsomaxsegcount; scalar_t__ if_hw_tsomaxsegsize; int if_flags; int if_capabilities; int if_hwassist; int if_capenable; scalar_t__ if_mtu; int if_hdrlen; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; TYPE_6__ if_snd; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_baudrate; struct hn_softc* if_softc; } ;
struct TYPE_9__ {TYPE_1__* ifm_cur; int /*<<< orphan*/  ifm_media; } ;
struct hn_softc {int hn_cpu; int hn_rx_ring_inuse; scalar_t__ hn_nvs_ver; scalar_t__ hn_rndis_agg_size; scalar_t__ hn_rndis_agg_pkts; scalar_t__ hn_rndis_agg_align; int hn_caps; int hn_flags; void* hn_ifnet_dethand; void* hn_ifnet_atthand; void* hn_ifnet_lnkhand; void* hn_ifaddr_evthand; void* hn_ifnet_evthand; void* hn_mgmt_taskq0; void* hn_mgmt_taskq; TYPE_5__* hn_tx_ring; TYPE_2__ hn_media; int /*<<< orphan*/  hn_rss_ind_size; int /*<<< orphan*/  hn_prichan; int /*<<< orphan*/ * hn_xact; struct ifnet* hn_ifp; int /*<<< orphan*/  hn_vf_init; void* hn_vf_taskq; int /*<<< orphan*/  hn_netchg_status; int /*<<< orphan*/  hn_netchg_init; int /*<<< orphan*/  hn_link_task; void** hn_tx_taskqs; int /*<<< orphan*/  hn_agg_pkts; int /*<<< orphan*/  hn_agg_size; int /*<<< orphan*/  hn_xvf_flags; int /*<<< orphan*/  hn_vf_lock; int /*<<< orphan*/  hn_dev; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_10__ {int hn_csum_assist; } ;
struct TYPE_8__ {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int CSUM_IP6_TSO ; 
 int CSUM_IP_TSO ; 
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_OPAQUE ; 
 int CTLTYPE_STRING ; 
 int CTLTYPE_UINT ; 
 int ENXIO ; 
 scalar_t__ ETHERMTU ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hn_softc*,int /*<<< orphan*/ ) ; 
 int HN_CAP_TSO4 ; 
 int HN_CAP_TSO6 ; 
 int HN_CAP_VLAN ; 
 int HN_CSUM_IP6_MASK ; 
 int HN_CSUM_IP_MASK ; 
 int HN_FLAG_SYNTH_ATTACHED ; 
 int /*<<< orphan*/  HN_LOCK (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_LOCK_INIT (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_LRO_LENLIM_MULTIRX_DEF ; 
 int HN_RING_CNT_DEF_MAX ; 
 scalar_t__ HN_TX_DATA_SEGCNT_MAX ; 
 scalar_t__ HN_TX_TASKQ_M_GLOBAL ; 
 scalar_t__ HN_TX_TASKQ_M_INDEP ; 
 int /*<<< orphan*/  HN_UNLOCK (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_XACT_REQ_SIZE ; 
 int /*<<< orphan*/  HN_XACT_RESP_SIZE ; 
 int /*<<< orphan*/  HN_XVFFLAG_ACCBPF ; 
 int IFCAP_LINKSTATE ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_6__*,int) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_6__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  IF_Gbps (int) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OID_AUTO ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct hn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,scalar_t__*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hn_softc*) ; 
 int /*<<< orphan*/  TIMEOUT_TASK_INIT (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hn_softc*) ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct hn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifattach_event ; 
 int /*<<< orphan*/  hn_caps_sysctl ; 
 int hn_chan_cnt ; 
 int /*<<< orphan*/  hn_cpu_index ; 
 int hn_create_rx_data (struct hn_softc*,int) ; 
 int hn_create_tx_data (struct hn_softc*,int) ; 
 int /*<<< orphan*/  hn_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_fixup_rx_data (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_fixup_tx_data (struct hn_softc*) ; 
 int hn_get_txswq_depth (TYPE_5__*) ; 
 int /*<<< orphan*/  hn_hwassist_sysctl ; 
 int /*<<< orphan*/  hn_ifaddr_event ; 
 int /*<<< orphan*/  hn_ifmedia_sts ; 
 int /*<<< orphan*/  hn_ifmedia_upd ; 
 int /*<<< orphan*/  hn_ifnet_attevent ; 
 int /*<<< orphan*/  hn_ifnet_detevent ; 
 int /*<<< orphan*/  hn_ifnet_event ; 
 int /*<<< orphan*/  hn_ifnet_lnkevent ; 
 int /*<<< orphan*/  hn_init ; 
 int /*<<< orphan*/  hn_ioctl ; 
 int /*<<< orphan*/  hn_link_taskfunc ; 
 int /*<<< orphan*/  hn_ndis_version_sysctl ; 
 int /*<<< orphan*/  hn_netchg_init_taskfunc ; 
 int /*<<< orphan*/  hn_netchg_status_taskfunc ; 
 int /*<<< orphan*/  hn_polling_sysctl ; 
 int hn_rndis_get_eaddr (struct hn_softc*,int /*<<< orphan*/ *) ; 
 int hn_rndis_get_mtu (struct hn_softc*,scalar_t__*) ; 
 int /*<<< orphan*/  hn_rss_hash_sysctl ; 
 int /*<<< orphan*/  hn_rss_hcap_sysctl ; 
 int /*<<< orphan*/  hn_rss_ind_sysctl ; 
 int /*<<< orphan*/  hn_rss_key_sysctl ; 
 int /*<<< orphan*/  hn_rss_mbuf_sysctl ; 
 int /*<<< orphan*/  hn_rxfilter_sysctl ; 
 int /*<<< orphan*/  hn_rxvf_sysctl ; 
 int /*<<< orphan*/  hn_set_lro_lenlim (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_set_tso_maxsize (struct hn_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hn_start ; 
 int hn_synth_attach (struct hn_softc*,scalar_t__) ; 
 int /*<<< orphan*/  hn_synth_detach (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_transmit ; 
 int /*<<< orphan*/  hn_tso_maxlen ; 
 int /*<<< orphan*/  hn_tx_agg_pkts ; 
 int /*<<< orphan*/  hn_tx_agg_size ; 
 int hn_tx_ring_cnt ; 
 int hn_tx_taskq_cnt ; 
 scalar_t__ hn_tx_taskq_mode ; 
 void** hn_tx_taskque ; 
 int /*<<< orphan*/  hn_txagg_pkts_sysctl ; 
 int /*<<< orphan*/  hn_txagg_size_sysctl ; 
 int /*<<< orphan*/  hn_update_link_status (struct hn_softc*) ; 
 scalar_t__ hn_use_if_start ; 
 int /*<<< orphan*/  hn_vf_sysctl ; 
 int /*<<< orphan*/  hn_xmit_qflush ; 
 scalar_t__ hn_xpnt_vf ; 
 scalar_t__ hn_xpnt_vf_accbpf ; 
 int /*<<< orphan*/  hn_xpnt_vf_accbpf_sysctl ; 
 int /*<<< orphan*/  hn_xpnt_vf_enabled_sysctl ; 
 int /*<<< orphan*/  hn_xpnt_vf_init_taskfunc ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ifaddr_event ; 
 int /*<<< orphan*/  ifmedia_add (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ifnet_departure_event ; 
 int /*<<< orphan*/  ifnet_event ; 
 int /*<<< orphan*/  ifnet_link_event ; 
 void** malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  rm_init (int /*<<< orphan*/ *,char*) ; 
 int rss_getnumbuckets () ; 
 void* taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  taskqueue_start_threads (void**,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 scalar_t__ vmbus_chan_is_revoked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_chan_set_orphan (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_get_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmbus_xact_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hn_attach(device_t dev)
{
	struct hn_softc *sc = device_get_softc(dev);
	struct sysctl_oid_list *child;
	struct sysctl_ctx_list *ctx;
	uint8_t eaddr[ETHER_ADDR_LEN];
	struct ifnet *ifp = NULL;
	int error, ring_cnt, tx_ring_cnt;
	uint32_t mtu;

	sc->hn_dev = dev;
	sc->hn_prichan = vmbus_get_channel(dev);
	HN_LOCK_INIT(sc);
	rm_init(&sc->hn_vf_lock, "hnvf");
	if (hn_xpnt_vf && hn_xpnt_vf_accbpf)
		sc->hn_xvf_flags |= HN_XVFFLAG_ACCBPF;

	/*
	 * Initialize these tunables once.
	 */
	sc->hn_agg_size = hn_tx_agg_size;
	sc->hn_agg_pkts = hn_tx_agg_pkts;

	/*
	 * Setup taskqueue for transmission.
	 */
	if (hn_tx_taskq_mode == HN_TX_TASKQ_M_INDEP) {
		int i;

		sc->hn_tx_taskqs =
		    malloc(hn_tx_taskq_cnt * sizeof(struct taskqueue *),
		    M_DEVBUF, M_WAITOK);
		for (i = 0; i < hn_tx_taskq_cnt; ++i) {
			sc->hn_tx_taskqs[i] = taskqueue_create("hn_tx",
			    M_WAITOK, taskqueue_thread_enqueue,
			    &sc->hn_tx_taskqs[i]);
			taskqueue_start_threads(&sc->hn_tx_taskqs[i], 1, PI_NET,
			    "%s tx%d", device_get_nameunit(dev), i);
		}
	} else if (hn_tx_taskq_mode == HN_TX_TASKQ_M_GLOBAL) {
		sc->hn_tx_taskqs = hn_tx_taskque;
	}

	/*
	 * Setup taskqueue for mangement tasks, e.g. link status.
	 */
	sc->hn_mgmt_taskq0 = taskqueue_create("hn_mgmt", M_WAITOK,
	    taskqueue_thread_enqueue, &sc->hn_mgmt_taskq0);
	taskqueue_start_threads(&sc->hn_mgmt_taskq0, 1, PI_NET, "%s mgmt",
	    device_get_nameunit(dev));
	TASK_INIT(&sc->hn_link_task, 0, hn_link_taskfunc, sc);
	TASK_INIT(&sc->hn_netchg_init, 0, hn_netchg_init_taskfunc, sc);
	TIMEOUT_TASK_INIT(sc->hn_mgmt_taskq0, &sc->hn_netchg_status, 0,
	    hn_netchg_status_taskfunc, sc);

	if (hn_xpnt_vf) {
		/*
		 * Setup taskqueue for VF tasks, e.g. delayed VF bringing up.
		 */
		sc->hn_vf_taskq = taskqueue_create("hn_vf", M_WAITOK,
		    taskqueue_thread_enqueue, &sc->hn_vf_taskq);
		taskqueue_start_threads(&sc->hn_vf_taskq, 1, PI_NET, "%s vf",
		    device_get_nameunit(dev));
		TIMEOUT_TASK_INIT(sc->hn_vf_taskq, &sc->hn_vf_init, 0,
		    hn_xpnt_vf_init_taskfunc, sc);
	}

	/*
	 * Allocate ifnet and setup its name earlier, so that if_printf
	 * can be used by functions, which will be called after
	 * ether_ifattach().
	 */
	ifp = sc->hn_ifp = if_alloc(IFT_ETHER);
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));

	/*
	 * Initialize ifmedia earlier so that it can be unconditionally
	 * destroyed, if error happened later on.
	 */
	ifmedia_init(&sc->hn_media, 0, hn_ifmedia_upd, hn_ifmedia_sts);

	/*
	 * Figure out the # of RX rings (ring_cnt) and the # of TX rings
	 * to use (tx_ring_cnt).
	 *
	 * NOTE:
	 * The # of RX rings to use is same as the # of channels to use.
	 */
	ring_cnt = hn_chan_cnt;
	if (ring_cnt <= 0) {
		/* Default */
		ring_cnt = mp_ncpus;
		if (ring_cnt > HN_RING_CNT_DEF_MAX)
			ring_cnt = HN_RING_CNT_DEF_MAX;
	} else if (ring_cnt > mp_ncpus) {
		ring_cnt = mp_ncpus;
	}
#ifdef RSS
	if (ring_cnt > rss_getnumbuckets())
		ring_cnt = rss_getnumbuckets();
#endif

	tx_ring_cnt = hn_tx_ring_cnt;
	if (tx_ring_cnt <= 0 || tx_ring_cnt > ring_cnt)
		tx_ring_cnt = ring_cnt;
#ifdef HN_IFSTART_SUPPORT
	if (hn_use_if_start) {
		/* ifnet.if_start only needs one TX ring. */
		tx_ring_cnt = 1;
	}
#endif

	/*
	 * Set the leader CPU for channels.
	 */
	sc->hn_cpu = atomic_fetchadd_int(&hn_cpu_index, ring_cnt) % mp_ncpus;

	/*
	 * Create enough TX/RX rings, even if only limited number of
	 * channels can be allocated.
	 */
	error = hn_create_tx_data(sc, tx_ring_cnt);
	if (error)
		goto failed;
	error = hn_create_rx_data(sc, ring_cnt);
	if (error)
		goto failed;

	/*
	 * Create transaction context for NVS and RNDIS transactions.
	 */
	sc->hn_xact = vmbus_xact_ctx_create(bus_get_dma_tag(dev),
	    HN_XACT_REQ_SIZE, HN_XACT_RESP_SIZE, 0);
	if (sc->hn_xact == NULL) {
		error = ENXIO;
		goto failed;
	}

	/*
	 * Install orphan handler for the revocation of this device's
	 * primary channel.
	 *
	 * NOTE:
	 * The processing order is critical here:
	 * Install the orphan handler, _before_ testing whether this
	 * device's primary channel has been revoked or not.
	 */
	vmbus_chan_set_orphan(sc->hn_prichan, sc->hn_xact);
	if (vmbus_chan_is_revoked(sc->hn_prichan)) {
		error = ENXIO;
		goto failed;
	}

	/*
	 * Attach the synthetic parts, i.e. NVS and RNDIS.
	 */
	error = hn_synth_attach(sc, ETHERMTU);
	if (error)
		goto failed;

	error = hn_rndis_get_eaddr(sc, eaddr);
	if (error)
		goto failed;

	error = hn_rndis_get_mtu(sc, &mtu);
	if (error)
		mtu = ETHERMTU;
	else if (bootverbose)
		device_printf(dev, "RNDIS mtu %u\n", mtu);

#if __FreeBSD_version >= 1100099
	if (sc->hn_rx_ring_inuse > 1) {
		/*
		 * Reduce TCP segment aggregation limit for multiple
		 * RX rings to increase ACK timeliness.
		 */
		hn_set_lro_lenlim(sc, HN_LRO_LENLIM_MULTIRX_DEF);
	}
#endif

	/*
	 * Fixup TX/RX stuffs after synthetic parts are attached.
	 */
	hn_fixup_tx_data(sc);
	hn_fixup_rx_data(sc);

	ctx = device_get_sysctl_ctx(dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "nvs_version", CTLFLAG_RD,
	    &sc->hn_nvs_ver, 0, "NVS version");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "ndis_version",
	    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    hn_ndis_version_sysctl, "A", "NDIS version");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "caps",
	    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    hn_caps_sysctl, "A", "capabilities");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "hwassist",
	    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    hn_hwassist_sysctl, "A", "hwassist");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tso_max",
	    CTLFLAG_RD, &ifp->if_hw_tsomax, 0, "max TSO size");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tso_maxsegcnt",
	    CTLFLAG_RD, &ifp->if_hw_tsomaxsegcount, 0,
	    "max # of TSO segments");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "tso_maxsegsz",
	    CTLFLAG_RD, &ifp->if_hw_tsomaxsegsize, 0,
	    "max size of TSO segment");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "rxfilter",
	    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    hn_rxfilter_sysctl, "A", "rxfilter");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "rss_hash",
	    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    hn_rss_hash_sysctl, "A", "RSS hash");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "rss_hashcap",
	    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    hn_rss_hcap_sysctl, "A", "RSS hash capabilities");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "mbuf_hash",
	    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    hn_rss_mbuf_sysctl, "A", "RSS hash for mbufs");
	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "rss_ind_size",
	    CTLFLAG_RD, &sc->hn_rss_ind_size, 0, "RSS indirect entry count");
#ifndef RSS
	/*
	 * Don't allow RSS key/indirect table changes, if RSS is defined.
	 */
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "rss_key",
	    CTLTYPE_OPAQUE | CTLFLAG_RW | CTLFLAG_MPSAFE, sc, 0,
	    hn_rss_key_sysctl, "IU", "RSS key");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "rss_ind",
	    CTLTYPE_OPAQUE | CTLFLAG_RW | CTLFLAG_MPSAFE, sc, 0,
	    hn_rss_ind_sysctl, "IU", "RSS indirect table");
#endif
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rndis_agg_size",
	    CTLFLAG_RD, &sc->hn_rndis_agg_size, 0,
	    "RNDIS offered packet transmission aggregation size limit");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rndis_agg_pkts",
	    CTLFLAG_RD, &sc->hn_rndis_agg_pkts, 0,
	    "RNDIS offered packet transmission aggregation count limit");
	SYSCTL_ADD_UINT(ctx, child, OID_AUTO, "rndis_agg_align",
	    CTLFLAG_RD, &sc->hn_rndis_agg_align, 0,
	    "RNDIS packet transmission aggregation alignment");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "agg_size",
	    CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_MPSAFE, sc, 0,
	    hn_txagg_size_sysctl, "I",
	    "Packet transmission aggregation size, 0 -- disable, -1 -- auto");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "agg_pkts",
	    CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_MPSAFE, sc, 0,
	    hn_txagg_pkts_sysctl, "I",
	    "Packet transmission aggregation packets, "
	    "0 -- disable, -1 -- auto");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "polling",
	    CTLTYPE_UINT | CTLFLAG_RW | CTLFLAG_MPSAFE, sc, 0,
	    hn_polling_sysctl, "I",
	    "Polling frequency: [100,1000000], 0 disable polling");
	SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "vf",
	    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
	    hn_vf_sysctl, "A", "Virtual Function's name");
	if (!hn_xpnt_vf) {
		SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "rxvf",
		    CTLTYPE_STRING | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
		    hn_rxvf_sysctl, "A", "activated Virtual Function's name");
	} else {
		SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "vf_xpnt_enabled",
		    CTLTYPE_INT | CTLFLAG_RD | CTLFLAG_MPSAFE, sc, 0,
		    hn_xpnt_vf_enabled_sysctl, "I",
		    "Transparent VF enabled");
		SYSCTL_ADD_PROC(ctx, child, OID_AUTO, "vf_xpnt_accbpf",
		    CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_MPSAFE, sc, 0,
		    hn_xpnt_vf_accbpf_sysctl, "I",
		    "Accurate BPF for transparent VF");
	}

	/*
	 * Setup the ifmedia, which has been initialized earlier.
	 */
	ifmedia_add(&sc->hn_media, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(&sc->hn_media, IFM_ETHER | IFM_AUTO);
	/* XXX ifmedia_set really should do this for us */
	sc->hn_media.ifm_media = sc->hn_media.ifm_cur->ifm_media;

	/*
	 * Setup the ifnet for this interface.
	 */

	ifp->if_baudrate = IF_Gbps(10);
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = hn_ioctl;
	ifp->if_init = hn_init;
#ifdef HN_IFSTART_SUPPORT
	if (hn_use_if_start) {
		int qdepth = hn_get_txswq_depth(&sc->hn_tx_ring[0]);

		ifp->if_start = hn_start;
		IFQ_SET_MAXLEN(&ifp->if_snd, qdepth);
		ifp->if_snd.ifq_drv_maxlen = qdepth - 1;
		IFQ_SET_READY(&ifp->if_snd);
	} else
#endif
	{
		ifp->if_transmit = hn_transmit;
		ifp->if_qflush = hn_xmit_qflush;
	}

	ifp->if_capabilities |= IFCAP_RXCSUM | IFCAP_LRO | IFCAP_LINKSTATE;
#ifdef foo
	/* We can't diff IPv6 packets from IPv4 packets on RX path. */
	ifp->if_capabilities |= IFCAP_RXCSUM_IPV6;
#endif
	if (sc->hn_caps & HN_CAP_VLAN) {
		/* XXX not sure about VLAN_MTU. */
		ifp->if_capabilities |= IFCAP_VLAN_HWTAGGING | IFCAP_VLAN_MTU;
	}

	ifp->if_hwassist = sc->hn_tx_ring[0].hn_csum_assist;
	if (ifp->if_hwassist & HN_CSUM_IP_MASK)
		ifp->if_capabilities |= IFCAP_TXCSUM;
	if (ifp->if_hwassist & HN_CSUM_IP6_MASK)
		ifp->if_capabilities |= IFCAP_TXCSUM_IPV6;
	if (sc->hn_caps & HN_CAP_TSO4) {
		ifp->if_capabilities |= IFCAP_TSO4;
		ifp->if_hwassist |= CSUM_IP_TSO;
	}
	if (sc->hn_caps & HN_CAP_TSO6) {
		ifp->if_capabilities |= IFCAP_TSO6;
		ifp->if_hwassist |= CSUM_IP6_TSO;
	}

	/* Enable all available capabilities by default. */
	ifp->if_capenable = ifp->if_capabilities;

	/*
	 * Disable IPv6 TSO and TXCSUM by default, they still can
	 * be enabled through SIOCSIFCAP.
	 */
	ifp->if_capenable &= ~(IFCAP_TXCSUM_IPV6 | IFCAP_TSO6);
	ifp->if_hwassist &= ~(HN_CSUM_IP6_MASK | CSUM_IP6_TSO);

	if (ifp->if_capabilities & (IFCAP_TSO6 | IFCAP_TSO4)) {
		/*
		 * Lock hn_set_tso_maxsize() to simplify its
		 * internal logic.
		 */
		HN_LOCK(sc);
		hn_set_tso_maxsize(sc, hn_tso_maxlen, ETHERMTU);
		HN_UNLOCK(sc);
		ifp->if_hw_tsomaxsegcount = HN_TX_DATA_SEGCNT_MAX;
		ifp->if_hw_tsomaxsegsize = PAGE_SIZE;
	}

	ether_ifattach(ifp, eaddr);

	if ((ifp->if_capabilities & (IFCAP_TSO6 | IFCAP_TSO4)) && bootverbose) {
		if_printf(ifp, "TSO segcnt %u segsz %u\n",
		    ifp->if_hw_tsomaxsegcount, ifp->if_hw_tsomaxsegsize);
	}
	if (mtu < ETHERMTU) {
		if_printf(ifp, "fixup mtu %u -> %u\n", ifp->if_mtu, mtu);
		ifp->if_mtu = mtu;
	}

	/* Inform the upper layer about the long frame support. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	/*
	 * Kick off link status check.
	 */
	sc->hn_mgmt_taskq = sc->hn_mgmt_taskq0;
	hn_update_link_status(sc);

	if (!hn_xpnt_vf) {
		sc->hn_ifnet_evthand = EVENTHANDLER_REGISTER(ifnet_event,
		    hn_ifnet_event, sc, EVENTHANDLER_PRI_ANY);
		sc->hn_ifaddr_evthand = EVENTHANDLER_REGISTER(ifaddr_event,
		    hn_ifaddr_event, sc, EVENTHANDLER_PRI_ANY);
	} else {
		sc->hn_ifnet_lnkhand = EVENTHANDLER_REGISTER(ifnet_link_event,
		    hn_ifnet_lnkevent, sc, EVENTHANDLER_PRI_ANY);
	}

	/*
	 * NOTE:
	 * Subscribe ether_ifattach event, instead of ifnet_arrival event,
	 * since interface's LLADDR is needed; interface LLADDR is not
	 * available when ifnet_arrival event is triggered.
	 */
	sc->hn_ifnet_atthand = EVENTHANDLER_REGISTER(ether_ifattach_event,
	    hn_ifnet_attevent, sc, EVENTHANDLER_PRI_ANY);
	sc->hn_ifnet_dethand = EVENTHANDLER_REGISTER(ifnet_departure_event,
	    hn_ifnet_detevent, sc, EVENTHANDLER_PRI_ANY);

	return (0);
failed:
	if (sc->hn_flags & HN_FLAG_SYNTH_ATTACHED)
		hn_synth_detach(sc);
	hn_detach(dev);
	return (error);
}