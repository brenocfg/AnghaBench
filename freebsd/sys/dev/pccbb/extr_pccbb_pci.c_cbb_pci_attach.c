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
typedef  int uint32_t ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_4__ {int sec; int sub; } ;
struct cbb_softc {int domain; int pribus; int subbus; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * base_res; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  dev; int /*<<< orphan*/  sc_root_token; int /*<<< orphan*/  event_thread; TYPE_2__* exca; int /*<<< orphan*/  intrhand; int /*<<< orphan*/ * cbdev; TYPE_1__ bus; int /*<<< orphan*/  (* chipinit ) (struct cbb_softc*) ;int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  rl; int /*<<< orphan*/  chipset; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pccarddev; int /*<<< orphan*/  chipset; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_OFF ; 
 int CBBR_SOCKBASE ; 
 int /*<<< orphan*/  CBB_EXCA_OFFSET ; 
 int /*<<< orphan*/  CBB_SOCKET_EVENT ; 
 int /*<<< orphan*/  CBB_SOCKET_MASK ; 
 int /*<<< orphan*/  CBB_SOCKET_MASK_CD ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXCA_CARDBUS ; 
 int /*<<< orphan*/  EXCA_HAS_MEMREG_WIN ; 
 int /*<<< orphan*/  EXCA_INTR ; 
 int /*<<< orphan*/  EXCA_INTR_RESET ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_AV ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PCIR_PRIBUS_2 ; 
 int /*<<< orphan*/  PCIR_SECBUS_2 ; 
 int /*<<< orphan*/  PCIR_SUBBUS_2 ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cbb_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cbb_chipinit (struct cbb_softc*) ; 
 int /*<<< orphan*/  cbb_chipset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cbb_event_thread ; 
 int /*<<< orphan*/  cbb_get (struct cbb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_pci_filt ; 
 int /*<<< orphan*/  cbb_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_print_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_set (struct cbb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_setb (struct cbb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exca_clrb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kproc_create (int /*<<< orphan*/ ,struct cbb_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_domain (int /*<<< orphan*/ ) ; 
 void* pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int pcib_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcib_setup_secbus (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_mount_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cbb_softc*) ; 

__attribute__((used)) static int
cbb_pci_attach(device_t brdev)
{
#if !(defined(NEW_PCIB) && defined(PCI_RES_BUS))
	static int curr_bus_number = 2; /* XXX EVILE BAD (see below) */
	uint32_t pribus;
#endif
	struct cbb_softc *sc = (struct cbb_softc *)device_get_softc(brdev);
	struct sysctl_ctx_list *sctx;
	struct sysctl_oid *soid;
	int rid;
	device_t parent;

	parent = device_get_parent(brdev);
	mtx_init(&sc->mtx, device_get_nameunit(brdev), "cbb", MTX_DEF);
	sc->chipset = cbb_chipset(pci_get_devid(brdev), NULL);
	sc->dev = brdev;
	sc->cbdev = NULL;
	sc->exca[0].pccarddev = NULL;
	sc->domain = pci_get_domain(brdev);
	sc->pribus = pcib_get_bus(parent);
#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	pci_write_config(brdev, PCIR_PRIBUS_2, sc->pribus, 1);
	pcib_setup_secbus(brdev, &sc->bus, 1);
#else
	sc->bus.sec = pci_read_config(brdev, PCIR_SECBUS_2, 1);
	sc->bus.sub = pci_read_config(brdev, PCIR_SUBBUS_2, 1);
#endif
	SLIST_INIT(&sc->rl);

	rid = CBBR_SOCKBASE;
	sc->base_res = bus_alloc_resource_any(brdev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (!sc->base_res) {
		device_printf(brdev, "Could not map register memory\n");
		mtx_destroy(&sc->mtx);
		return (ENOMEM);
	} else {
		DEVPRINTF((brdev, "Found memory at %jx\n",
		    rman_get_start(sc->base_res)));
	}

	sc->bst = rman_get_bustag(sc->base_res);
	sc->bsh = rman_get_bushandle(sc->base_res);
	exca_init(&sc->exca[0], brdev, sc->bst, sc->bsh, CBB_EXCA_OFFSET);
	sc->exca[0].flags |= EXCA_HAS_MEMREG_WIN;
	sc->exca[0].chipset = EXCA_CARDBUS;
	sc->chipinit = cbb_chipinit;
	sc->chipinit(sc);

	/*Sysctls*/
	sctx = device_get_sysctl_ctx(brdev);
	soid = device_get_sysctl_tree(brdev);
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "domain",
	    CTLFLAG_RD, &sc->domain, 0, "Domain number");
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "pribus",
	    CTLFLAG_RD, &sc->pribus, 0, "Primary bus number");
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "secbus",
	    CTLFLAG_RD, &sc->bus.sec, 0, "Secondary bus number");
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "subbus",
	    CTLFLAG_RD, &sc->bus.sub, 0, "Subordinate bus number");
#if 0
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "memory",
	    CTLFLAG_RD, &sc->subbus, 0, "Memory window open");
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "premem",
	    CTLFLAG_RD, &sc->subbus, 0, "Prefetch memory window open");
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "io1",
	    CTLFLAG_RD, &sc->subbus, 0, "io range 1 open");
	SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "io2",
	    CTLFLAG_RD, &sc->subbus, 0, "io range 2 open");
#endif

#if !(defined(NEW_PCIB) && defined(PCI_RES_BUS))
	/*
	 * This is a gross hack.  We should be scanning the entire pci
	 * tree, assigning bus numbers in a way such that we (1) can
	 * reserve 1 extra bus just in case and (2) all sub buses
	 * are in an appropriate range.
	 */
	DEVPRINTF((brdev, "Secondary bus is %d\n", sc->bus.sec));
	pribus = pci_read_config(brdev, PCIR_PRIBUS_2, 1);
	if (sc->bus.sec == 0 || sc->pribus != pribus) {
		if (curr_bus_number <= sc->pribus)
			curr_bus_number = sc->pribus + 1;
		if (pribus != sc->pribus) {
			DEVPRINTF((brdev, "Setting primary bus to %d\n",
			    sc->pribus));
			pci_write_config(brdev, PCIR_PRIBUS_2, sc->pribus, 1);
		}
		sc->bus.sec = curr_bus_number++;
		sc->bus.sub = curr_bus_number++;
		DEVPRINTF((brdev, "Secondary bus set to %d subbus %d\n",
		    sc->bus.sec, sc->bus.sub));
		pci_write_config(brdev, PCIR_SECBUS_2, sc->bus.sec, 1);
		pci_write_config(brdev, PCIR_SUBBUS_2, sc->bus.sub, 1);
	}
#endif

	/* attach children */
	sc->cbdev = device_add_child(brdev, "cardbus", -1);
	if (sc->cbdev == NULL)
		DEVPRINTF((brdev, "WARNING: cannot add cardbus bus.\n"));
	else if (device_probe_and_attach(sc->cbdev) != 0)
		DEVPRINTF((brdev, "WARNING: cannot attach cardbus bus!\n"));

	sc->exca[0].pccarddev = device_add_child(brdev, "pccard", -1);
	if (sc->exca[0].pccarddev == NULL)
		DEVPRINTF((brdev, "WARNING: cannot add pccard bus.\n"));
	else if (device_probe_and_attach(sc->exca[0].pccarddev) != 0)
		DEVPRINTF((brdev, "WARNING: cannot attach pccard bus.\n"));

	/* Map and establish the interrupt. */
	rid = 0;
	sc->irq_res = bus_alloc_resource_any(brdev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(brdev, "Unable to map IRQ...\n");
		goto err;
	}

	if (bus_setup_intr(brdev, sc->irq_res, INTR_TYPE_AV | INTR_MPSAFE,
	    cbb_pci_filt, NULL, sc, &sc->intrhand)) {
		device_printf(brdev, "couldn't establish interrupt\n");
		goto err;
	}

	/* reset 16-bit pcmcia bus */
	exca_clrb(&sc->exca[0], EXCA_INTR, EXCA_INTR_RESET);

	/* turn off power */
	cbb_power(brdev, CARD_OFF);

	/* CSC Interrupt: Card detect interrupt on */
	cbb_setb(sc, CBB_SOCKET_MASK, CBB_SOCKET_MASK_CD);

	/* reset interrupt */
	cbb_set(sc, CBB_SOCKET_EVENT, cbb_get(sc, CBB_SOCKET_EVENT));

	if (bootverbose)
		cbb_print_config(brdev);

	/* Start the thread */
	if (kproc_create(cbb_event_thread, sc, &sc->event_thread, 0, 0,
	    "%s event thread", device_get_nameunit(brdev))) {
		device_printf(brdev, "unable to create event thread.\n");
		panic("cbb_create_event_thread");
	}
	sc->sc_root_token = root_mount_hold(device_get_nameunit(sc->dev));
	return (0);
err:
	if (sc->irq_res)
		bus_release_resource(brdev, SYS_RES_IRQ, 0, sc->irq_res);
	if (sc->base_res) {
		bus_release_resource(brdev, SYS_RES_MEMORY, CBBR_SOCKBASE,
		    sc->base_res);
	}
	mtx_destroy(&sc->mtx);
	return (ENOMEM);
}