#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_8__ ;
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct ether_vlan_header {int dummy; } ;
typedef  TYPE_4__* kobjop_desc_t ;
typedef  TYPE_5__* kobj_t ;
typedef  int /*<<< orphan*/  kobj_method_t ;
typedef  int /*<<< orphan*/  if_t ;
typedef  TYPE_6__* if_softc_ctx_t ;
typedef  TYPE_7__* if_shared_ctx_t ;
typedef  TYPE_8__* if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_43__ {int /*<<< orphan*/  octet; } ;
struct TYPE_47__ {int isc_capabilities; int isc_tx_csum_flags; int isc_capenable; int isc_ntxqsets; int isc_ntxqsets_max; int isc_nrxqsets; int isc_nrxqsets_max; int* isc_ntxd; int isc_tx_nsegments; int isc_tx_tso_segments_max; int isc_rss_table_size; int isc_rss_table_mask; int isc_vectors; scalar_t__ isc_msix_bar; scalar_t__ isc_intr; int /*<<< orphan*/  isc_tx_tso_segsize_max; int /*<<< orphan*/  isc_tx_tso_size_max; int /*<<< orphan*/ * isc_nrxd; int /*<<< orphan*/  isc_media; int /*<<< orphan*/ * isc_txrx; } ;
struct TYPE_49__ {int ifc_flags; struct TYPE_49__* ifc_softc; int /*<<< orphan*/  ifc_dev; int /*<<< orphan*/  ifc_admin_task; int /*<<< orphan*/  ifc_ifp; TYPE_2__ ifc_mac; int /*<<< orphan*/  isc_legacy_intr; int /*<<< orphan*/  ifc_sysctl_core_offset; int /*<<< orphan*/  ifc_cpus; int /*<<< orphan*/  ifc_mediap; int /*<<< orphan*/  ifc_txrx; TYPE_6__ ifc_softc_ctx; TYPE_7__* ifc_sctx; } ;
struct TYPE_48__ {int isc_flags; TYPE_3__* isc_driver; } ;
struct TYPE_46__ {TYPE_1__* ops; } ;
struct TYPE_45__ {int /*<<< orphan*/  deflt; } ;
struct TYPE_44__ {int size; } ;
struct TYPE_42__ {int /*<<< orphan*/  cls; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_COUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CTX_LOCK (TYPE_8__*) ; 
 int /*<<< orphan*/  CTX_UNLOCK (TYPE_8__*) ; 
 int /*<<< orphan*/  DEBUGNET_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GROUPTASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int IFCAP_HWSTATS ; 
 int IFCAP_NOMAP ; 
 int IFCAP_TSO ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_MTU ; 
 int IFC_INIT_DONE ; 
 int IFC_SC_ALLOCATED ; 
 int IFDI_ATTACH_POST (TYPE_8__*) ; 
 int IFDI_ATTACH_PRE (TYPE_8__*) ; 
 int /*<<< orphan*/  IFDI_DETACH (TYPE_8__*) ; 
 int /*<<< orphan*/  IFDI_INTR_DISABLE (TYPE_8__*) ; 
 int IFDI_MSIX_INTR_ASSIGN (TYPE_8__*,int) ; 
 int IFLIB_DRIVER_MEDIA ; 
 int IFLIB_HAS_RXCQ ; 
 int IFLIB_HAS_TXCQ ; 
 scalar_t__ IFLIB_INTR_LEGACY ; 
 scalar_t__ IFLIB_INTR_MSI ; 
 scalar_t__ IFLIB_INTR_MSIX ; 
 int IFLIB_SKIP_MSIX ; 
 int /*<<< orphan*/  INTR_CPUS ; 
 int /*<<< orphan*/  IP_MAXPACKET ; 
 int MAX_SINGLE_PACKET_FRACTION ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_IFLIB ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  _iflib_pre_assert (TYPE_6__*) ; 
 int /*<<< orphan*/  _task_fn_admin ; 
 int /*<<< orphan*/  all_cpus ; 
 scalar_t__ bus_get_cpus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  ether_ifattach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ctx_core_offset (TYPE_8__*) ; 
 int if_getcapabilities (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapabilities (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_setcapenable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_setgetcounterfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sethwtsomax (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sethwtsomaxsegcount (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_sethwtsomaxsegsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setifheaderlen (int /*<<< orphan*/ ,int) ; 
 TYPE_4__ ifdi_rx_queue_intr_enable_desc ; 
 TYPE_4__ ifdi_tx_queue_intr_enable_desc ; 
 int /*<<< orphan*/  iflib ; 
 int /*<<< orphan*/  iflib_add_device_sysctl_post (TYPE_8__*) ; 
 int /*<<< orphan*/  iflib_add_device_sysctl_pre (TYPE_8__*) ; 
 int /*<<< orphan*/  iflib_add_pfil (TYPE_8__*) ; 
 int /*<<< orphan*/  iflib_deregister (TYPE_8__*) ; 
 int /*<<< orphan*/  iflib_free_intr_mem (TYPE_8__*) ; 
 int /*<<< orphan*/  iflib_if_get_counter ; 
 int iflib_legacy_setup (TYPE_8__*,int /*<<< orphan*/ ,TYPE_8__*,int*,char*) ; 
 int iflib_msix_init (TYPE_8__*) ; 
 int iflib_netmap_attach (TYPE_8__*) ; 
 int iflib_qset_structures_setup (TYPE_8__*) ; 
 int iflib_queues_alloc (TYPE_8__*) ; 
 int iflib_register (TYPE_8__*) ; 
 int /*<<< orphan*/  iflib_reset_qvalues (TYPE_8__*) ; 
 int /*<<< orphan*/  iflib_rx_structures_free (TYPE_8__*) ; 
 int /*<<< orphan*/  iflib_tx_structures_free (TYPE_8__*) ; 
 int /*<<< orphan*/ * kobj_lookup_method (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 void* max (int,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qgroup_if_config_tqg ; 
 int /*<<< orphan*/  taskqgroup_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  taskqgroup_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
iflib_device_register(device_t dev, void *sc, if_shared_ctx_t sctx, if_ctx_t *ctxp)
{
	if_ctx_t ctx;
	if_t ifp;
	if_softc_ctx_t scctx;
	kobjop_desc_t kobj_desc;
	kobj_method_t *kobj_method;
	int err, msix, rid;
	uint16_t main_rxq, main_txq;

	ctx = malloc(sizeof(* ctx), M_IFLIB, M_WAITOK|M_ZERO);

	if (sc == NULL) {
		sc = malloc(sctx->isc_driver->size, M_IFLIB, M_WAITOK|M_ZERO);
		device_set_softc(dev, ctx);
		ctx->ifc_flags |= IFC_SC_ALLOCATED;
	}

	ctx->ifc_sctx = sctx;
	ctx->ifc_dev = dev;
	ctx->ifc_softc = sc;

	if ((err = iflib_register(ctx)) != 0) {
		device_printf(dev, "iflib_register failed %d\n", err);
		goto fail_ctx_free;
	}
	iflib_add_device_sysctl_pre(ctx);

	scctx = &ctx->ifc_softc_ctx;
	ifp = ctx->ifc_ifp;

	iflib_reset_qvalues(ctx);
	CTX_LOCK(ctx);
	if ((err = IFDI_ATTACH_PRE(ctx)) != 0) {
		device_printf(dev, "IFDI_ATTACH_PRE failed %d\n", err);
		goto fail_unlock;
	}
	_iflib_pre_assert(scctx);
	ctx->ifc_txrx = *scctx->isc_txrx;

	if (sctx->isc_flags & IFLIB_DRIVER_MEDIA)
		ctx->ifc_mediap = scctx->isc_media;

#ifdef INVARIANTS
	if (scctx->isc_capabilities & IFCAP_TXCSUM)
		MPASS(scctx->isc_tx_csum_flags);
#endif

	if_setcapabilities(ifp,
	    scctx->isc_capabilities | IFCAP_HWSTATS | IFCAP_NOMAP);
	if_setcapenable(ifp,
	    scctx->isc_capenable | IFCAP_HWSTATS | IFCAP_NOMAP);

	if (scctx->isc_ntxqsets == 0 || (scctx->isc_ntxqsets_max && scctx->isc_ntxqsets_max < scctx->isc_ntxqsets))
		scctx->isc_ntxqsets = scctx->isc_ntxqsets_max;
	if (scctx->isc_nrxqsets == 0 || (scctx->isc_nrxqsets_max && scctx->isc_nrxqsets_max < scctx->isc_nrxqsets))
		scctx->isc_nrxqsets = scctx->isc_nrxqsets_max;

	main_txq = (sctx->isc_flags & IFLIB_HAS_TXCQ) ? 1 : 0;
	main_rxq = (sctx->isc_flags & IFLIB_HAS_RXCQ) ? 1 : 0;

	/* XXX change for per-queue sizes */
	device_printf(dev, "Using %d TX descriptors and %d RX descriptors\n",
	    scctx->isc_ntxd[main_txq], scctx->isc_nrxd[main_rxq]);

	if (scctx->isc_tx_nsegments > scctx->isc_ntxd[main_txq] /
	    MAX_SINGLE_PACKET_FRACTION)
		scctx->isc_tx_nsegments = max(1, scctx->isc_ntxd[main_txq] /
		    MAX_SINGLE_PACKET_FRACTION);
	if (scctx->isc_tx_tso_segments_max > scctx->isc_ntxd[main_txq] /
	    MAX_SINGLE_PACKET_FRACTION)
		scctx->isc_tx_tso_segments_max = max(1,
		    scctx->isc_ntxd[main_txq] / MAX_SINGLE_PACKET_FRACTION);

	/* TSO parameters - dig these out of the data sheet - simply correspond to tag setup */
	if (if_getcapabilities(ifp) & IFCAP_TSO) {
		/*
		 * The stack can't handle a TSO size larger than IP_MAXPACKET,
		 * but some MACs do.
		 */
		if_sethwtsomax(ifp, min(scctx->isc_tx_tso_size_max,
		    IP_MAXPACKET));
		/*
		 * Take maximum number of m_pullup(9)'s in iflib_parse_header()
		 * into account.  In the worst case, each of these calls will
		 * add another mbuf and, thus, the requirement for another DMA
		 * segment.  So for best performance, it doesn't make sense to
		 * advertize a maximum of TSO segments that typically will
		 * require defragmentation in iflib_encap().
		 */
		if_sethwtsomaxsegcount(ifp, scctx->isc_tx_tso_segments_max - 3);
		if_sethwtsomaxsegsize(ifp, scctx->isc_tx_tso_segsize_max);
	}
	if (scctx->isc_rss_table_size == 0)
		scctx->isc_rss_table_size = 64;
	scctx->isc_rss_table_mask = scctx->isc_rss_table_size-1;

	GROUPTASK_INIT(&ctx->ifc_admin_task, 0, _task_fn_admin, ctx);
	/* XXX format name */
	taskqgroup_attach(qgroup_if_config_tqg, &ctx->ifc_admin_task, ctx,
	    NULL, NULL, "admin");

	/* Set up cpu set.  If it fails, use the set of all CPUs. */
	if (bus_get_cpus(dev, INTR_CPUS, sizeof(ctx->ifc_cpus), &ctx->ifc_cpus) != 0) {
		device_printf(dev, "Unable to fetch CPU list\n");
		CPU_COPY(&all_cpus, &ctx->ifc_cpus);
	}
	MPASS(CPU_COUNT(&ctx->ifc_cpus) > 0);

	/*
	** Now set up MSI or MSI-X, should return us the number of supported
	** vectors (will be 1 for a legacy interrupt and MSI).
	*/
	if (sctx->isc_flags & IFLIB_SKIP_MSIX) {
		msix = scctx->isc_vectors;
	} else if (scctx->isc_msix_bar != 0)
	       /*
		* The simple fact that isc_msix_bar is not 0 does not mean we
		* we have a good value there that is known to work.
		*/
		msix = iflib_msix_init(ctx);
	else {
		scctx->isc_vectors = 1;
		scctx->isc_ntxqsets = 1;
		scctx->isc_nrxqsets = 1;
		scctx->isc_intr = IFLIB_INTR_LEGACY;
		msix = 0;
	}
	/* Get memory for the station queues */
	if ((err = iflib_queues_alloc(ctx))) {
		device_printf(dev, "Unable to allocate queue memory\n");
		goto fail_intr_free;
	}

	if ((err = iflib_qset_structures_setup(ctx)))
		goto fail_queues;

	/*
	 * Now that we know how many queues there are, get the core offset.
	 */
	ctx->ifc_sysctl_core_offset = get_ctx_core_offset(ctx);

	/*
	 * Group taskqueues aren't properly set up until SMP is started,
	 * so we disable interrupts until we can handle them post
	 * SI_SUB_SMP.
	 *
	 * XXX: disabling interrupts doesn't actually work, at least for
	 * the non-MSI case.  When they occur before SI_SUB_SMP completes,
	 * we do null handling and depend on this not causing too large an
	 * interrupt storm.
	 */
	IFDI_INTR_DISABLE(ctx);

	if (msix > 1) {
		/*
		 * When using MSI-X, ensure that ifdi_{r,t}x_queue_intr_enable
		 * aren't the default NULL implementation.
		 */
		kobj_desc = &ifdi_rx_queue_intr_enable_desc;
		kobj_method = kobj_lookup_method(((kobj_t)ctx)->ops->cls, NULL,
		    kobj_desc);
		if (kobj_method == &kobj_desc->deflt) {
			device_printf(dev,
			    "MSI-X requires ifdi_rx_queue_intr_enable method");
			err = EOPNOTSUPP;
			goto fail_queues;
		}
		kobj_desc = &ifdi_tx_queue_intr_enable_desc;
		kobj_method = kobj_lookup_method(((kobj_t)ctx)->ops->cls, NULL,
		    kobj_desc);
		if (kobj_method == &kobj_desc->deflt) {
			device_printf(dev,
			    "MSI-X requires ifdi_tx_queue_intr_enable method");
			err = EOPNOTSUPP;
			goto fail_queues;
		}

		/*
		 * Assign the MSI-X vectors.
		 * Note that the default NULL ifdi_msix_intr_assign method will
		 * fail here, too.
		 */
		err = IFDI_MSIX_INTR_ASSIGN(ctx, msix);
		if (err != 0) {
			device_printf(dev, "IFDI_MSIX_INTR_ASSIGN failed %d\n",
			    err);
			goto fail_queues;
		}
	} else if (scctx->isc_intr != IFLIB_INTR_MSIX) {
		rid = 0;
		if (scctx->isc_intr == IFLIB_INTR_MSI) {
			MPASS(msix == 1);
			rid = 1;
		}
		if ((err = iflib_legacy_setup(ctx, ctx->isc_legacy_intr, ctx->ifc_softc, &rid, "irq0")) != 0) {
			device_printf(dev, "iflib_legacy_setup failed %d\n", err);
			goto fail_queues;
		}
	} else {
		device_printf(dev,
		    "Cannot use iflib with only 1 MSI-X interrupt!\n");
		err = ENODEV;
		goto fail_intr_free;
	}

	ether_ifattach(ctx->ifc_ifp, ctx->ifc_mac.octet);

	if ((err = IFDI_ATTACH_POST(ctx)) != 0) {
		device_printf(dev, "IFDI_ATTACH_POST failed %d\n", err);
		goto fail_detach;
	}

	/*
	 * Tell the upper layer(s) if IFCAP_VLAN_MTU is supported.
	 * This must appear after the call to ether_ifattach() because
	 * ether_ifattach() sets if_hdrlen to the default value.
	 */
	if (if_getcapabilities(ifp) & IFCAP_VLAN_MTU)
		if_setifheaderlen(ifp, sizeof(struct ether_vlan_header));

	if ((err = iflib_netmap_attach(ctx))) {
		device_printf(ctx->ifc_dev, "netmap attach failed: %d\n", err);
		goto fail_detach;
	}
	*ctxp = ctx;

	DEBUGNET_SET(ctx->ifc_ifp, iflib);

	if_setgetcounterfn(ctx->ifc_ifp, iflib_if_get_counter);
	iflib_add_device_sysctl_post(ctx);
	iflib_add_pfil(ctx);
	ctx->ifc_flags |= IFC_INIT_DONE;
	CTX_UNLOCK(ctx);

	return (0);

fail_detach:
	ether_ifdetach(ctx->ifc_ifp);
fail_intr_free:
	iflib_free_intr_mem(ctx);
fail_queues:
	iflib_tx_structures_free(ctx);
	iflib_rx_structures_free(ctx);
	taskqgroup_detach(qgroup_if_config_tqg, &ctx->ifc_admin_task);
	IFDI_DETACH(ctx);
fail_unlock:
	CTX_UNLOCK(ctx);
	iflib_deregister(ctx);
fail_ctx_free:
	device_set_softc(ctx->ifc_dev, NULL);
        if (ctx->ifc_flags & IFC_SC_ALLOCATED)
                free(ctx->ifc_softc, M_IFLIB);
        free(ctx, M_IFLIB);
	return (err);
}