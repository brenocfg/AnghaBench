#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct TYPE_7__ {scalar_t__ dma_vaddr; } ;
struct TYPE_5__ {TYPE_3__ q_mcr; TYPE_3__ q_ctx; } ;
struct TYPE_6__ {TYPE_1__ rng_q; TYPE_3__ rng_buf; } ;
struct ubsec_softc {int sc_statmask; int sc_flags; scalar_t__ sc_cid; int sc_rnghz; int /*<<< orphan*/ * sc_sr; int /*<<< orphan*/ * sc_irq; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/  sc_mcr2lock; int /*<<< orphan*/  sc_rngto; TYPE_2__ sc_rng; void* sc_harvest; scalar_t__ sc_rndtest; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_freeqlock; int /*<<< orphan*/  sc_mcr1lock; int /*<<< orphan*/  sc_freequeue; struct ubsec_q** sc_queuea; struct ubsec_dma* sc_dmaa; int /*<<< orphan*/  sc_dmat; int /*<<< orphan*/  sc_sh; int /*<<< orphan*/  sc_st; int /*<<< orphan*/  sc_q2free; int /*<<< orphan*/  sc_qchip2; int /*<<< orphan*/  sc_queue2; int /*<<< orphan*/  sc_qchip; int /*<<< orphan*/  sc_queue; } ;
struct ubsec_session {int dummy; } ;
struct ubsec_q {struct ubsec_dma* q_dma; } ;
struct ubsec_mcr {int dummy; } ;
struct ubsec_dmachunk {int dummy; } ;
struct ubsec_dma {TYPE_3__ d_alloc; struct ubsec_dmachunk* d_dma; } ;
struct ubsec_ctx_rngbypass {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BS_BAR ; 
 int BS_STAT_DMAERR ; 
 int BS_STAT_MCR1_ALLEMPTY ; 
 int BS_STAT_MCR1_DONE ; 
 int BS_STAT_MCR2_ALLEMPTY ; 
 int BS_STAT_MCR2_DONE ; 
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CRK_MOD_EXP ; 
 int /*<<< orphan*/  CRK_MOD_EXP_CRT ; 
 int /*<<< orphan*/  CRYPTOCAP_F_HARDWARE ; 
 int /*<<< orphan*/  CRYPTO_3DES_CBC ; 
 int /*<<< orphan*/  CRYPTO_DES_CBC ; 
 int /*<<< orphan*/  CRYPTO_MD5_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA1_HMAC ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ PCI_PRODUCT_BLUESTEEL_5601 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5802 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5805 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5820 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5821 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5822 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5823 ; 
 scalar_t__ PCI_PRODUCT_BROADCOM_5825 ; 
 scalar_t__ PCI_PRODUCT_SUN_5821 ; 
 scalar_t__ PCI_PRODUCT_SUN_SCA1K ; 
 scalar_t__ PCI_VENDOR_BLUESTEEL ; 
 scalar_t__ PCI_VENDOR_BROADCOM ; 
 scalar_t__ PCI_VENDOR_SUN ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SIMPLEQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIMPLEQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ubsec_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int UBSEC_RNG_BUFSIZ ; 
 int UBS_FLAGS_BIGKEY ; 
 int UBS_FLAGS_HWNORM ; 
 int UBS_FLAGS_KEY ; 
 int UBS_FLAGS_LONGCTX ; 
 int UBS_FLAGS_RNG ; 
 scalar_t__ UBS_MAX_NQUEUE ; 
 int /*<<< orphan*/  UBS_MAX_SCATTER ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ubsec_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct ubsec_softc*,int) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ubsec_softc*) ; 
 scalar_t__ crypto_get_driverid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_kregister (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_register (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_all (scalar_t__) ; 
 void* default_harvest ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ubsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct ubsec_q*,int /*<<< orphan*/ ) ; 
 int hz ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_next ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 scalar_t__ rndtest_attach (int /*<<< orphan*/ ) ; 
 void* rndtest_harvest ; 
 int /*<<< orphan*/  ubsec_dma_free (struct ubsec_softc*,TYPE_3__*) ; 
 scalar_t__ ubsec_dma_malloc (struct ubsec_softc*,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubsec_init_board (struct ubsec_softc*) ; 
 int /*<<< orphan*/  ubsec_init_pciregs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubsec_intr ; 
 int /*<<< orphan*/  ubsec_partname (struct ubsec_softc*) ; 
 int /*<<< orphan*/  ubsec_reset_board (struct ubsec_softc*) ; 
 int /*<<< orphan*/  ubsec_rng ; 

__attribute__((used)) static int
ubsec_attach(device_t dev)
{
	struct ubsec_softc *sc = device_get_softc(dev);
	struct ubsec_dma *dmap;
	u_int32_t i;
	int rid;

	bzero(sc, sizeof (*sc));
	sc->sc_dev = dev;

	SIMPLEQ_INIT(&sc->sc_queue);
	SIMPLEQ_INIT(&sc->sc_qchip);
	SIMPLEQ_INIT(&sc->sc_queue2);
	SIMPLEQ_INIT(&sc->sc_qchip2);
	SIMPLEQ_INIT(&sc->sc_q2free);

	/* XXX handle power management */

	sc->sc_statmask = BS_STAT_MCR1_DONE | BS_STAT_DMAERR;

	if (pci_get_vendor(dev) == PCI_VENDOR_BLUESTEEL &&
	    pci_get_device(dev) == PCI_PRODUCT_BLUESTEEL_5601)
		sc->sc_flags |= UBS_FLAGS_KEY | UBS_FLAGS_RNG;

	if (pci_get_vendor(dev) == PCI_VENDOR_BROADCOM &&
	    (pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5802 ||
	     pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5805))
		sc->sc_flags |= UBS_FLAGS_KEY | UBS_FLAGS_RNG;

	if (pci_get_vendor(dev) == PCI_VENDOR_BROADCOM &&
	    pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5820)
		sc->sc_flags |= UBS_FLAGS_KEY | UBS_FLAGS_RNG |
		    UBS_FLAGS_LONGCTX | UBS_FLAGS_HWNORM | UBS_FLAGS_BIGKEY;

	if ((pci_get_vendor(dev) == PCI_VENDOR_BROADCOM &&
	     (pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5821 ||
	      pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5822 ||
	      pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5823 ||
	      pci_get_device(dev) == PCI_PRODUCT_BROADCOM_5825)) ||
	    (pci_get_vendor(dev) == PCI_VENDOR_SUN &&
	     (pci_get_device(dev) == PCI_PRODUCT_SUN_SCA1K ||
	      pci_get_device(dev) == PCI_PRODUCT_SUN_5821))) {
		/* NB: the 5821/5822 defines some additional status bits */
		sc->sc_statmask |= BS_STAT_MCR1_ALLEMPTY |
		    BS_STAT_MCR2_ALLEMPTY;
		sc->sc_flags |= UBS_FLAGS_KEY | UBS_FLAGS_RNG |
		    UBS_FLAGS_LONGCTX | UBS_FLAGS_HWNORM | UBS_FLAGS_BIGKEY;
	}

	pci_enable_busmaster(dev);

	/*
	 * Setup memory-mapping of PCI registers.
	 */
	rid = BS_BAR;
	sc->sc_sr = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
					   RF_ACTIVE);
	if (sc->sc_sr == NULL) {
		device_printf(dev, "cannot map register space\n");
		goto bad;
	}
	sc->sc_st = rman_get_bustag(sc->sc_sr);
	sc->sc_sh = rman_get_bushandle(sc->sc_sr);

	/*
	 * Arrange interrupt line.
	 */
	rid = 0;
	sc->sc_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
					    RF_SHAREABLE|RF_ACTIVE);
	if (sc->sc_irq == NULL) {
		device_printf(dev, "could not map interrupt\n");
		goto bad1;
	}
	/*
	 * NB: Network code assumes we are blocked with splimp()
	 *     so make sure the IRQ is mapped appropriately.
	 */
	if (bus_setup_intr(dev, sc->sc_irq, INTR_TYPE_NET | INTR_MPSAFE,
			   NULL, ubsec_intr, sc, &sc->sc_ih)) {
		device_printf(dev, "could not establish interrupt\n");
		goto bad2;
	}

	sc->sc_cid = crypto_get_driverid(dev, sizeof(struct ubsec_session),
	    CRYPTOCAP_F_HARDWARE);
	if (sc->sc_cid < 0) {
		device_printf(dev, "could not get crypto driver id\n");
		goto bad3;
	}

	/*
	 * Setup DMA descriptor area.
	 */
	if (bus_dma_tag_create(bus_get_dma_tag(dev),	/* parent */
			       1, 0,			/* alignment, bounds */
			       BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			       BUS_SPACE_MAXADDR,	/* highaddr */
			       NULL, NULL,		/* filter, filterarg */
			       0x3ffff,			/* maxsize */
			       UBS_MAX_SCATTER,		/* nsegments */
			       0xffff,			/* maxsegsize */
			       BUS_DMA_ALLOCNOW,	/* flags */
			       NULL, NULL,		/* lockfunc, lockarg */
			       &sc->sc_dmat)) {
		device_printf(dev, "cannot allocate DMA tag\n");
		goto bad4;
	}
	SIMPLEQ_INIT(&sc->sc_freequeue);
	dmap = sc->sc_dmaa;
	for (i = 0; i < UBS_MAX_NQUEUE; i++, dmap++) {
		struct ubsec_q *q;

		q = (struct ubsec_q *)malloc(sizeof(struct ubsec_q),
		    M_DEVBUF, M_NOWAIT);
		if (q == NULL) {
			device_printf(dev, "cannot allocate queue buffers\n");
			break;
		}

		if (ubsec_dma_malloc(sc, sizeof(struct ubsec_dmachunk),
		    &dmap->d_alloc, 0)) {
			device_printf(dev, "cannot allocate dma buffers\n");
			free(q, M_DEVBUF);
			break;
		}
		dmap->d_dma = (struct ubsec_dmachunk *)dmap->d_alloc.dma_vaddr;

		q->q_dma = dmap;
		sc->sc_queuea[i] = q;

		SIMPLEQ_INSERT_TAIL(&sc->sc_freequeue, q, q_next);
	}
	mtx_init(&sc->sc_mcr1lock, device_get_nameunit(dev),
		"mcr1 operations", MTX_DEF);
	mtx_init(&sc->sc_freeqlock, device_get_nameunit(dev),
		"mcr1 free q", MTX_DEF);

	device_printf(sc->sc_dev, "%s\n", ubsec_partname(sc));

	crypto_register(sc->sc_cid, CRYPTO_3DES_CBC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_DES_CBC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_MD5_HMAC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_SHA1_HMAC, 0, 0);

	/*
	 * Reset Broadcom chip
	 */
	ubsec_reset_board(sc);

	/*
	 * Init Broadcom specific PCI settings
	 */
	ubsec_init_pciregs(dev);

	/*
	 * Init Broadcom chip
	 */
	ubsec_init_board(sc);

#ifndef UBSEC_NO_RNG
	if (sc->sc_flags & UBS_FLAGS_RNG) {
		sc->sc_statmask |= BS_STAT_MCR2_DONE;
#ifdef UBSEC_RNDTEST
		sc->sc_rndtest = rndtest_attach(dev);
		if (sc->sc_rndtest)
			sc->sc_harvest = rndtest_harvest;
		else
			sc->sc_harvest = default_harvest;
#else
		sc->sc_harvest = default_harvest;
#endif

		if (ubsec_dma_malloc(sc, sizeof(struct ubsec_mcr),
		    &sc->sc_rng.rng_q.q_mcr, 0))
			goto skip_rng;

		if (ubsec_dma_malloc(sc, sizeof(struct ubsec_ctx_rngbypass),
		    &sc->sc_rng.rng_q.q_ctx, 0)) {
			ubsec_dma_free(sc, &sc->sc_rng.rng_q.q_mcr);
			goto skip_rng;
		}

		if (ubsec_dma_malloc(sc, sizeof(u_int32_t) *
		    UBSEC_RNG_BUFSIZ, &sc->sc_rng.rng_buf, 0)) {
			ubsec_dma_free(sc, &sc->sc_rng.rng_q.q_ctx);
			ubsec_dma_free(sc, &sc->sc_rng.rng_q.q_mcr);
			goto skip_rng;
		}

		if (hz >= 100)
			sc->sc_rnghz = hz / 100;
		else
			sc->sc_rnghz = 1;
		callout_init(&sc->sc_rngto, 1);
		callout_reset(&sc->sc_rngto, sc->sc_rnghz, ubsec_rng, sc);
skip_rng:
	;
	}
#endif /* UBSEC_NO_RNG */
	mtx_init(&sc->sc_mcr2lock, device_get_nameunit(dev),
		"mcr2 operations", MTX_DEF);

	if (sc->sc_flags & UBS_FLAGS_KEY) {
		sc->sc_statmask |= BS_STAT_MCR2_DONE;

		crypto_kregister(sc->sc_cid, CRK_MOD_EXP, 0);
#if 0
		crypto_kregister(sc->sc_cid, CRK_MOD_EXP_CRT, 0);
#endif
	}
	return (0);
bad4:
	crypto_unregister_all(sc->sc_cid);
bad3:
	bus_teardown_intr(dev, sc->sc_irq, sc->sc_ih);
bad2:
	bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq);
bad1:
	bus_release_resource(dev, SYS_RES_MEMORY, BS_BAR, sc->sc_sr);
bad:
	return (ENXIO);
}