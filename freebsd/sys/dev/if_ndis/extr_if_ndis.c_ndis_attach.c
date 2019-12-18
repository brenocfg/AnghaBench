#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ndis_softc {scalar_t__ ndis_iftype; int ndis_maxpkts; int ndis_txpending; int ndis_oidcnt; scalar_t__* ndis_oids; int ndis_80211; scalar_t__ ndis_sc; int /*<<< orphan*/ * ndis_txpool; int /*<<< orphan*/  ndis_txarray; TYPE_2__* ndis_block; int /*<<< orphan*/  ndis_rxdpc; void* ndisusb_taskitem; void* ndisusb_xferdoneitem; void* ndis_inputitem; void* ndis_resetitem; void* ndis_startitem; void* ndis_tickitem; TYPE_1__* ndis_chars; int /*<<< orphan*/  ndis_dobj; int /*<<< orphan*/  ndis_rxqueue; int /*<<< orphan*/  ndis_stat_callout; int /*<<< orphan*/  ndisusb_xferdonelist; int /*<<< orphan*/  ndisusb_tasklist; int /*<<< orphan*/  ndis_shlist; int /*<<< orphan*/  ndisusb_xferdonelock; int /*<<< orphan*/  ndisusb_tasklock; int /*<<< orphan*/  ndis_rxlock; int /*<<< orphan*/  ndis_mtx; } ;
typedef  int /*<<< orphan*/  ndis_packet ;
typedef  int /*<<< orphan*/  driver_object ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  device_object ;
struct TYPE_5__ {int /*<<< orphan*/  nmb_deviceobj; int /*<<< orphan*/  nmb_statusdone_func; int /*<<< orphan*/  nmb_status_func; int /*<<< orphan*/  nmb_tdcond_func; int /*<<< orphan*/  nmb_ethrxdone_func; int /*<<< orphan*/  nmb_ethrxindicate_func; int /*<<< orphan*/  nmb_pktind_func; int /*<<< orphan*/  nmb_senddone_func; int /*<<< orphan*/ * nmb_rlist; } ;
struct TYPE_4__ {int /*<<< orphan*/  nmc_version_minor; int /*<<< orphan*/  nmc_version_major; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 void* IoAllocateWorkItem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeInitializeDpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  KeInitializeSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NDIS_SERIALIZED (TYPE_2__*) ; 
 int NDIS_STATUS_SUCCESS ; 
 int NDIS_TXPKTS ; 
 scalar_t__ NdisAddDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisAllocatePacketPool (int*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 scalar_t__ OID_802_11_CONFIGURATION ; 
 int /*<<< orphan*/  OID_GEN_MAXIMUM_SEND_PACKETS ; 
 scalar_t__ PCIBus ; 
 scalar_t__ PCMCIABus ; 
 scalar_t__ PNPBus ; 
 int /*<<< orphan*/  PROTOCOL_RESERVED_SIZE_IN_PACKET ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ndis_80211attach (struct ndis_softc*) ; 
 int /*<<< orphan*/  ndis_convert_res (struct ndis_softc*) ; 
 int /*<<< orphan*/  ndis_create_sysctls (struct ndis_softc*) ; 
 int /*<<< orphan*/  ndis_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ ndis_get_info (struct ndis_softc*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ndis_get_supported_oids (struct ndis_softc*,scalar_t__**,int*) ; 
 int /*<<< orphan*/  ndis_halt_nic (struct ndis_softc*) ; 
 int ndis_ifattach (struct ndis_softc*) ; 
 int /*<<< orphan*/  ndis_init_dma (struct ndis_softc*) ; 
 scalar_t__ ndis_init_nic (struct ndis_softc*) ; 
 int /*<<< orphan*/  ndis_linksts_done_wrap ; 
 int /*<<< orphan*/  ndis_linksts_wrap ; 
 int /*<<< orphan*/  ndis_rxeof_done_wrap ; 
 int /*<<< orphan*/  ndis_rxeof_eth_wrap ; 
 int /*<<< orphan*/  ndis_rxeof_wrap ; 
 int /*<<< orphan*/  ndis_rxeof_xfr_done_wrap ; 
 int /*<<< orphan*/  ndis_rxeof_xfr_wrap ; 
 int /*<<< orphan*/  ndis_txeof_wrap ; 
 scalar_t__ ndisusb_halt ; 
 int /*<<< orphan*/ * windrv_find_pdo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * windrv_lookup (int /*<<< orphan*/ ,char*) ; 

int
ndis_attach(device_t dev)
{
	struct ndis_softc	*sc;
	driver_object		*pdrv;
	device_object		*pdo;
	int			error = 0, len;
	int			i;

	sc = device_get_softc(dev);

	mtx_init(&sc->ndis_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	KeInitializeSpinLock(&sc->ndis_rxlock);
	KeInitializeSpinLock(&sc->ndisusb_tasklock);
	KeInitializeSpinLock(&sc->ndisusb_xferdonelock);
	InitializeListHead(&sc->ndis_shlist);
	InitializeListHead(&sc->ndisusb_tasklist);
	InitializeListHead(&sc->ndisusb_xferdonelist);
	callout_init(&sc->ndis_stat_callout, 1);
	mbufq_init(&sc->ndis_rxqueue, INT_MAX);	/* XXXGL: sane maximum */

	/* Create sysctl registry nodes */
	ndis_create_sysctls(sc);

	/* Find the PDO for this device instance. */

	if (sc->ndis_iftype == PCIBus)
		pdrv = windrv_lookup(0, "PCI Bus");
	else if (sc->ndis_iftype == PCMCIABus)
		pdrv = windrv_lookup(0, "PCCARD Bus");
	else
		pdrv = windrv_lookup(0, "USB Bus");
	pdo = windrv_find_pdo(pdrv, dev);

	/*
	 * Create a new functional device object for this
	 * device. This is what creates the miniport block
	 * for this device instance.
	 */

	if (NdisAddDevice(sc->ndis_dobj, pdo) != STATUS_SUCCESS) {
		device_printf(dev, "failed to create FDO!\n");
		error = ENXIO;
		goto fail;
	}

	/* Tell the user what version of the API the driver is using. */
	device_printf(dev, "NDIS API version: %d.%d\n",
	    sc->ndis_chars->nmc_version_major,
	    sc->ndis_chars->nmc_version_minor);

	/* Do resource conversion. */
	if (sc->ndis_iftype == PCMCIABus || sc->ndis_iftype == PCIBus)
		ndis_convert_res(sc);
	else
		sc->ndis_block->nmb_rlist = NULL;

	/* Install our RX and TX interrupt handlers. */
	sc->ndis_block->nmb_senddone_func = ndis_txeof_wrap;
	sc->ndis_block->nmb_pktind_func = ndis_rxeof_wrap;
	sc->ndis_block->nmb_ethrxindicate_func = ndis_rxeof_eth_wrap;
	sc->ndis_block->nmb_ethrxdone_func = ndis_rxeof_done_wrap;
	sc->ndis_block->nmb_tdcond_func = ndis_rxeof_xfr_done_wrap;

	/* Override the status handler so we can detect link changes. */
	sc->ndis_block->nmb_status_func = ndis_linksts_wrap;
	sc->ndis_block->nmb_statusdone_func = ndis_linksts_done_wrap;

	/* Set up work item handlers. */
	sc->ndis_tickitem = IoAllocateWorkItem(sc->ndis_block->nmb_deviceobj);
	sc->ndis_startitem = IoAllocateWorkItem(sc->ndis_block->nmb_deviceobj);
	sc->ndis_resetitem = IoAllocateWorkItem(sc->ndis_block->nmb_deviceobj);
	sc->ndis_inputitem = IoAllocateWorkItem(sc->ndis_block->nmb_deviceobj);
	sc->ndisusb_xferdoneitem =
	    IoAllocateWorkItem(sc->ndis_block->nmb_deviceobj);
	sc->ndisusb_taskitem =
	    IoAllocateWorkItem(sc->ndis_block->nmb_deviceobj);
	KeInitializeDpc(&sc->ndis_rxdpc, ndis_rxeof_xfr_wrap, sc->ndis_block);

	/* Call driver's init routine. */
	if (ndis_init_nic(sc)) {
		device_printf(dev, "init handler failed\n");
		error = ENXIO;
		goto fail;
	}

	/*
	 * Figure out how big to make the TX buffer pool.
	 */
	len = sizeof(sc->ndis_maxpkts);
	if (ndis_get_info(sc, OID_GEN_MAXIMUM_SEND_PACKETS,
		    &sc->ndis_maxpkts, &len)) {
		device_printf(dev, "failed to get max TX packets\n");
		error = ENXIO;
		goto fail;
	}

	/*
	 * If this is a deserialized miniport, we don't have
	 * to honor the OID_GEN_MAXIMUM_SEND_PACKETS result.
	 */
	if (!NDIS_SERIALIZED(sc->ndis_block))
		sc->ndis_maxpkts = NDIS_TXPKTS;

	/* Enforce some sanity, just in case. */

	if (sc->ndis_maxpkts == 0)
		sc->ndis_maxpkts = 10;

	sc->ndis_txarray = malloc(sizeof(ndis_packet *) *
	    sc->ndis_maxpkts, M_DEVBUF, M_NOWAIT|M_ZERO);

	/* Allocate a pool of ndis_packets for TX encapsulation. */

	NdisAllocatePacketPool(&i, &sc->ndis_txpool,
	    sc->ndis_maxpkts, PROTOCOL_RESERVED_SIZE_IN_PACKET);

	if (i != NDIS_STATUS_SUCCESS) {
		sc->ndis_txpool = NULL;
		device_printf(dev, "failed to allocate TX packet pool");
		error = ENOMEM;
		goto fail;
	}

	sc->ndis_txpending = sc->ndis_maxpkts;

	sc->ndis_oidcnt = 0;
	/* Get supported oid list. */
	ndis_get_supported_oids(sc, &sc->ndis_oids, &sc->ndis_oidcnt);

	/* If the NDIS module requested scatter/gather, init maps. */
	if (sc->ndis_sc)
		ndis_init_dma(sc);

	/*
	 * See if the OID_802_11_CONFIGURATION OID is
	 * supported by this driver. If it is, then this an 802.11
	 * wireless driver, and we should set up media for wireless.
	 */
	for (i = 0; i < sc->ndis_oidcnt; i++)
		if (sc->ndis_oids[i] == OID_802_11_CONFIGURATION) {
			sc->ndis_80211 = 1;
			break;
		}

	if (sc->ndis_80211)
		error = ndis_80211attach(sc);
	else
		error = ndis_ifattach(sc);

fail:
	if (error) {
		ndis_detach(dev);
		return (error);
	}

	if (sc->ndis_iftype == PNPBus && ndisusb_halt == 0)
		return (error);

	DPRINTF(("attach done.\n"));
	/* We're done talking to the NIC for now; halt it. */
	ndis_halt_nic(sc);
	DPRINTF(("halting done.\n"));

	return (error);
}