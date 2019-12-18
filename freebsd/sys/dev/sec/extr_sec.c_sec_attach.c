#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ dma_paddr; scalar_t__ dma_vaddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  bst; int /*<<< orphan*/  bsh; } ;
struct sec_softc {scalar_t__ sc_cid; int sc_pri_irid; int sc_version; int sc_sec_irid; unsigned long long sc_int_error_mask; int sc_channel_idle_mask; int /*<<< orphan*/  sc_descriptors_lock; int /*<<< orphan*/  sc_controller_lock; int /*<<< orphan*/ * sc_rres; scalar_t__ sc_rrid; int /*<<< orphan*/  sc_pri_ihand; int /*<<< orphan*/  sc_pri_ires; int /*<<< orphan*/  sc_sec_ihand; int /*<<< orphan*/  sc_sec_ires; TYPE_4__ sc_desc_dmem; TYPE_4__ sc_lt_dmem; TYPE_3__* sc_lt; TYPE_2__* sc_desc; TYPE_1__ sc_bas; scalar_t__ sc_shutdown; scalar_t__ sc_blocked; int /*<<< orphan*/  sc_dev; } ;
struct sec_session {int dummy; } ;
struct sec_hw_lt {int shl_n; scalar_t__ shl_ptr; scalar_t__ shl_r; scalar_t__ shl_length; } ;
struct sec_hw_desc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {scalar_t__ sl_lt_paddr; struct sec_hw_lt* sl_lt; } ;
struct TYPE_7__ {scalar_t__ sd_desc_paddr; struct sec_hw_desc* sd_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCAP_F_HARDWARE ; 
 int /*<<< orphan*/  CRYPTO_3DES_CBC ; 
 int /*<<< orphan*/  CRYPTO_AES_CBC ; 
 int /*<<< orphan*/  CRYPTO_DES_CBC ; 
 int /*<<< orphan*/  CRYPTO_MD5 ; 
 int /*<<< orphan*/  CRYPTO_MD5_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA1 ; 
 int /*<<< orphan*/  CRYPTO_SHA1_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_256_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_384_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_512_HMAC ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SEC_CHANNELS ; 
 int SEC_CHAN_CSR2_FFLVL_M ; 
 int SEC_CHAN_CSR2_FFLVL_S ; 
 int SEC_CHAN_CSR2_GSTATE_M ; 
 int SEC_CHAN_CSR2_GSTATE_S ; 
 int SEC_CHAN_CSR2_MSTATE_M ; 
 int SEC_CHAN_CSR2_MSTATE_S ; 
 int SEC_CHAN_CSR2_PSTATE_M ; 
 int SEC_CHAN_CSR2_PSTATE_S ; 
 int SEC_CHAN_CSR3_FFLVL_M ; 
 int SEC_CHAN_CSR3_FFLVL_S ; 
 int SEC_CHAN_CSR3_GSTATE_M ; 
 int SEC_CHAN_CSR3_GSTATE_S ; 
 int SEC_CHAN_CSR3_MSTATE_M ; 
 int SEC_CHAN_CSR3_MSTATE_S ; 
 int SEC_CHAN_CSR3_PSTATE_M ; 
 int SEC_CHAN_CSR3_PSTATE_S ; 
 int /*<<< orphan*/  SEC_CNT_INIT (struct sec_softc*,int /*<<< orphan*/ ,int) ; 
 int SEC_DESCRIPTORS ; 
 unsigned long long SEC_INT_CH_ERR (int) ; 
 int SEC_LT_ENTRIES ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_get_driverid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_register (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct sec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_free_desc_get_cnt ; 
 int /*<<< orphan*/  sc_free_desc_put_cnt ; 
 int /*<<< orphan*/  sc_lt_alloc_cnt ; 
 int /*<<< orphan*/  sc_lt_free_cnt ; 
 int /*<<< orphan*/  sc_queued_desc_get_cnt ; 
 int /*<<< orphan*/  sc_queued_desc_put_cnt ; 
 int /*<<< orphan*/  sc_ready_desc_get_cnt ; 
 int /*<<< orphan*/  sc_ready_desc_put_cnt ; 
 int sec_alloc_dma_mem (struct sec_softc*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  sec_free_dma_mem (TYPE_4__*) ; 
 int sec_init (struct sec_softc*) ; 
 int /*<<< orphan*/  sec_primary_intr ; 
 int /*<<< orphan*/  sec_release_intr (struct sec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  sec_secondary_intr ; 
 int sec_setup_intr (struct sec_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
sec_attach(device_t dev)
{
	struct sec_softc *sc;
	struct sec_hw_lt *lt;
	int error = 0;
	int i;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_blocked = 0;
	sc->sc_shutdown = 0;

	sc->sc_cid = crypto_get_driverid(dev, sizeof(struct sec_session),
	    CRYPTOCAP_F_HARDWARE);
	if (sc->sc_cid < 0) {
		device_printf(dev, "could not get crypto driver ID!\n");
		return (ENXIO);
	}

	/* Init locks */
	mtx_init(&sc->sc_controller_lock, device_get_nameunit(dev),
	    "SEC Controller lock", MTX_DEF);
	mtx_init(&sc->sc_descriptors_lock, device_get_nameunit(dev),
	    "SEC Descriptors lock", MTX_DEF);

	/* Allocate I/O memory for SEC registers */
	sc->sc_rrid = 0;
	sc->sc_rres = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->sc_rrid,
	    RF_ACTIVE);

	if (sc->sc_rres == NULL) {
		device_printf(dev, "could not allocate I/O memory!\n");
		goto fail1;
	}

	sc->sc_bas.bsh = rman_get_bushandle(sc->sc_rres);
	sc->sc_bas.bst = rman_get_bustag(sc->sc_rres);

	/* Setup interrupts */
	sc->sc_pri_irid = 0;
	error = sec_setup_intr(sc, &sc->sc_pri_ires, &sc->sc_pri_ihand,
	    &sc->sc_pri_irid, sec_primary_intr, "primary");

	if (error)
		goto fail2;


	if (sc->sc_version == 3) {
		sc->sc_sec_irid = 1;
		error = sec_setup_intr(sc, &sc->sc_sec_ires, &sc->sc_sec_ihand,
		    &sc->sc_sec_irid, sec_secondary_intr, "secondary");

		if (error)
			goto fail3;
	}

	/* Alloc DMA memory for descriptors and link tables */
	error = sec_alloc_dma_mem(sc, &(sc->sc_desc_dmem),
	    SEC_DESCRIPTORS * sizeof(struct sec_hw_desc));

	if (error)
		goto fail4;

	error = sec_alloc_dma_mem(sc, &(sc->sc_lt_dmem),
	    (SEC_LT_ENTRIES + 1) * sizeof(struct sec_hw_lt));

	if (error)
		goto fail5;

	/* Fill in descriptors and link tables */
	for (i = 0; i < SEC_DESCRIPTORS; i++) {
		sc->sc_desc[i].sd_desc =
		    (struct sec_hw_desc*)(sc->sc_desc_dmem.dma_vaddr) + i;
		sc->sc_desc[i].sd_desc_paddr = sc->sc_desc_dmem.dma_paddr +
		    (i * sizeof(struct sec_hw_desc));
	}

	for (i = 0; i < SEC_LT_ENTRIES + 1; i++) {
		sc->sc_lt[i].sl_lt =
		    (struct sec_hw_lt*)(sc->sc_lt_dmem.dma_vaddr) + i;
		sc->sc_lt[i].sl_lt_paddr = sc->sc_lt_dmem.dma_paddr +
		    (i * sizeof(struct sec_hw_lt));
	}

	/* Last entry in link table is used to create a circle */
	lt = sc->sc_lt[SEC_LT_ENTRIES].sl_lt;
	lt->shl_length = 0;
	lt->shl_r = 0;
	lt->shl_n = 1;
	lt->shl_ptr = sc->sc_lt[0].sl_lt_paddr;

	/* Init descriptor and link table queues pointers */
	SEC_CNT_INIT(sc, sc_free_desc_get_cnt, SEC_DESCRIPTORS);
	SEC_CNT_INIT(sc, sc_free_desc_put_cnt, SEC_DESCRIPTORS);
	SEC_CNT_INIT(sc, sc_ready_desc_get_cnt, SEC_DESCRIPTORS);
	SEC_CNT_INIT(sc, sc_ready_desc_put_cnt, SEC_DESCRIPTORS);
	SEC_CNT_INIT(sc, sc_queued_desc_get_cnt, SEC_DESCRIPTORS);
	SEC_CNT_INIT(sc, sc_queued_desc_put_cnt, SEC_DESCRIPTORS);
	SEC_CNT_INIT(sc, sc_lt_alloc_cnt, SEC_LT_ENTRIES);
	SEC_CNT_INIT(sc, sc_lt_free_cnt, SEC_LT_ENTRIES);

	/* Create masks for fast checks */
	sc->sc_int_error_mask = 0;
	for (i = 0; i < SEC_CHANNELS; i++)
		sc->sc_int_error_mask |= (~0ULL & SEC_INT_CH_ERR(i));

	switch (sc->sc_version) {
	case 2:
		sc->sc_channel_idle_mask =
		    (SEC_CHAN_CSR2_FFLVL_M << SEC_CHAN_CSR2_FFLVL_S) |
		    (SEC_CHAN_CSR2_MSTATE_M << SEC_CHAN_CSR2_MSTATE_S) |
		    (SEC_CHAN_CSR2_PSTATE_M << SEC_CHAN_CSR2_PSTATE_S) |
		    (SEC_CHAN_CSR2_GSTATE_M << SEC_CHAN_CSR2_GSTATE_S);
		break;
	case 3:
		sc->sc_channel_idle_mask =
		    (SEC_CHAN_CSR3_FFLVL_M << SEC_CHAN_CSR3_FFLVL_S) |
		    (SEC_CHAN_CSR3_MSTATE_M << SEC_CHAN_CSR3_MSTATE_S) |
		    (SEC_CHAN_CSR3_PSTATE_M << SEC_CHAN_CSR3_PSTATE_S) |
		    (SEC_CHAN_CSR3_GSTATE_M << SEC_CHAN_CSR3_GSTATE_S);
		break;
	}

	/* Init hardware */
	error = sec_init(sc);

	if (error)
		goto fail6;

	/* Register in OCF (AESU) */
	crypto_register(sc->sc_cid, CRYPTO_AES_CBC, 0, 0);

	/* Register in OCF (DEU) */
	crypto_register(sc->sc_cid, CRYPTO_DES_CBC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_3DES_CBC, 0, 0);

	/* Register in OCF (MDEU) */
	crypto_register(sc->sc_cid, CRYPTO_MD5, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_MD5_HMAC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_SHA1, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_SHA1_HMAC, 0, 0);
	crypto_register(sc->sc_cid, CRYPTO_SHA2_256_HMAC, 0, 0);
	if (sc->sc_version >= 3) {
		crypto_register(sc->sc_cid, CRYPTO_SHA2_384_HMAC, 0, 0);
		crypto_register(sc->sc_cid, CRYPTO_SHA2_512_HMAC, 0, 0);
	}

	return (0);

fail6:
	sec_free_dma_mem(&(sc->sc_lt_dmem));
fail5:
	sec_free_dma_mem(&(sc->sc_desc_dmem));
fail4:
	sec_release_intr(sc, sc->sc_sec_ires, sc->sc_sec_ihand,
	    sc->sc_sec_irid, "secondary");
fail3:
	sec_release_intr(sc, sc->sc_pri_ires, sc->sc_pri_ihand,
	    sc->sc_pri_irid, "primary");
fail2:
	bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_rrid, sc->sc_rres);
fail1:
	mtx_destroy(&sc->sc_controller_lock);
	mtx_destroy(&sc->sc_descriptors_lock);

	return (ENXIO);
}